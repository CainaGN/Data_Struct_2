#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct 
{
    int id;
    char* titulo;
    double preco;
    char* categoria;
    double avaliacao_nota;
    int avaliacao_contagem;
} Produto;

void imprimir_produto(Produto* p);
void liberar_produto(Produto* p);
Produto** carregar_produtos_do_arquivo_json(const char* caminho, int* num_reais, int* num_total);

#endif
