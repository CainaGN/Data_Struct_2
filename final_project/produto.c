#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "produto.h"

#define PRODUTOS_A_SIMULAR 10000

Produto** carregar_produtos_do_arquivo_json(const char* caminho, int* num_reais, int* num_total) 
{
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) 
    {
        perror("Erro ao abrir o arquivo JSON");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    char* conteudo = malloc(tamanho + 1);
    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    cJSON* json_array = cJSON_Parse(conteudo);
    if (!json_array) 
    {
        fprintf(stderr, "Erro ao fazer parse do JSON: %s\n", cJSON_GetErrorPtr());
        free(conteudo);
        return NULL;
    }

    int n = cJSON_GetArraySize(json_array);
    *num_reais = n;
    *num_total = PRODUTOS_A_SIMULAR;

    Produto** produtos_base = malloc(sizeof(Produto*) * n);
    Produto** produtos_finais = malloc(sizeof(Produto*) * PRODUTOS_A_SIMULAR);

    for (int i = 0; i < n; i++) 
    {
        cJSON* item = cJSON_GetArrayItem(json_array, i);
        Produto* p = malloc(sizeof(Produto));
        p->id = cJSON_GetObjectItem(item, "id")->valueint;
        p->titulo = strdup(cJSON_GetObjectItem(item, "title")->valuestring);
        p->preco = (float)cJSON_GetObjectItem(item, "price")->valuedouble;
        p->categoria = strdup(cJSON_GetObjectItem(item, "category")->valuestring);

        cJSON* rating = cJSON_GetObjectItem(item, "rating");
        p->avaliacao_nota = (float)cJSON_GetObjectItem(rating, "rate")->valuedouble;
        p->avaliacao_contagem = cJSON_GetObjectItem(rating, "count")->valueint;

        produtos_base[i] = p;
    }

    for (int i = 0; i < PRODUTOS_A_SIMULAR; i++) 
    {
        int idx = rand() % n;
        Produto* original = produtos_base[idx];
        Produto* copia = malloc(sizeof(Produto));

        copia->id = i + 1;
        copia->titulo = strdup(original->titulo);
        copia->preco = original->preco;
        copia->categoria = strdup(original->categoria);
        copia->avaliacao_nota = original->avaliacao_nota;
        copia->avaliacao_contagem = original->avaliacao_contagem;

        produtos_finais[i] = copia;
    }

    free(conteudo);
    cJSON_Delete(json_array);

    return produtos_finais;
}

void liberar_produto(Produto* p) 
{
    if (p != NULL) 
    {
        free(p->titulo);
        free(p->categoria);
        free(p);
    }
}
