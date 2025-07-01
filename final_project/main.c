#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "produto.h"
#include "tabela_hash.h"
#include "arvore_avl.h"
#include "lista.h"


void imprimir_produto(Produto* p) 
{
    if (p == NULL) 
    {
        printf("Produto não encontrado.\n");
        return;
    }
    printf("========================================\n");
    printf("ID: %d\n", p->id);
    printf("Título: %s\n", p->titulo);
    printf("Preço: R$ %.2f\n", p->preco);
    printf("Categoria: %s\n", p->categoria);
    printf("Avaliação: %.1f/5.0 (%d avaliações)\n", p->avaliacao_nota, p->avaliacao_contagem);
    printf("========================================\n\n");
}


void mostrar_menu() 
{
    printf("\n--- MENU - Catálogo de Produtos ---\n");
    printf("1. Buscar produto por ID\n");
    printf("2. Listar todos os produtos (ordenado por preço)\n");
    printf("3. Buscar produtos por faixa de preço\n");
    printf("4. Ver produtos vistos recentemente\n");
    printf("5. Inserir produto individual\n");
    printf("6. Remover produto por ID\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int buscar_maior_id(NoAVL* raiz) 
{
    if (raiz == NULL) return 0;

    int maior = raiz->produto->id;

    int maior_esq = buscar_maior_id(raiz->esquerda);
    int maior_dir = buscar_maior_id(raiz->direita);

    if (maior_esq > maior) maior = maior_esq;
    if (maior_dir > maior) maior = maior_dir;

    return maior;
}


int proximo_id_disponivel(NoAVL* raiz) 
{
    int maior = buscar_maior_id(raiz);
   // printf("\nmaior: %d\n", maior + 1);
    return maior + 1;
}


int main() 
{
    int num_produtos_reais, num_produtos_total;
    clock_t inicio, fim;
    double tempo_carregamento;

    inicio = clock();
    Produto** todos_os_produtos = carregar_produtos_do_arquivo_json("produtos_1k.json", &num_produtos_reais, &num_produtos_total);

    if (todos_os_produtos == NULL) 
    {
        fprintf(stderr, "Falha crítica: não foi possível carregar os produtos. Encerrando.\n");
        return 1;
    }

    int tamanho_tabela = 14303; // Primo mais próximo do fator de carga 0.7 é 14303. 142871 para 100k
    TabelaHash* th = criar_tabela_hash(tamanho_tabela);
    NoAVL* raiz_avl = NULL;
    ListaDE* vistos_recentemente = criar_lista(5); 

    for (int i = 0; i < num_produtos_total; i++) 
    {
        inserir_hash(th, todos_os_produtos[i]);
        raiz_avl = inserir_avl(raiz_avl, todos_os_produtos[i]);
    }
    fim = clock();
    tempo_carregamento = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n>>> Análise de Tempo de Carga Inicial <<<\n");
    printf("Tempo para carregar e inserir %d produtos em ambas as estruturas: %f segundos\n", num_produtos_total, tempo_carregamento);
    

    int escolha;
    do 
    {
        mostrar_menu();
        scanf("%d", &escolha);

        switch (escolha) 
        {
            case 1: 
            {
                int id_busca;
                printf("Digite o ID do produto a buscar: ");
                scanf("%d", &id_busca);

                inicio = clock();
                Produto* p_encontrado = buscar_hash(th, id_busca);
                fim = clock();
                
                if (p_encontrado) 
                {
                    imprimir_produto(p_encontrado);
                    inserir_inicio_lista(vistos_recentemente, p_encontrado);
                } else 
                {
                    printf("Produto com ID %d não encontrado.\n", id_busca);
                }
                double tempo_busca = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("Tempo de busca na Tabela Hash: %e segundos\n", tempo_busca);
                break;
            }
            case 2:
            {
                printf("\n--- Listando todos os produtos (ordenado por preço via Árvore AVL) ---\n");
                imprimir_em_ordem_avl(raiz_avl);
                break;
            }
            case 3: 
            {
                double min, max;
                printf("Digite o preço mínimo: ");
                scanf("%lf", &min);
                printf("Digite o preço máximo: ");
                scanf("%lf", &max);
                printf("\n--- Produtos entre R$%.2f e R$%.2f ---\n", min, max);
                inicio = clock(); 
		        buscar_por_faixa_avl(raiz_avl, min, max);
		        fim = clock();   

		        double tempo_busca_faixa = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
		        printf("Tempo de busca por faixa na AVL: %e segundos\n", tempo_busca_faixa); 
		        break;
            }
            case 4: 
            {
                printf("\n--- Últimos 5 produtos visualizados ---\n");
                imprimir_lista(vistos_recentemente);
                break;
            }
            
            case 5: 
            {
                Produto* novo = (Produto*) malloc(sizeof(Produto));
                novo->id = proximo_id_disponivel(raiz_avl);

                char titulo_buffer[256];
                printf("Digite o Título do produto: ");
                scanf(" %255[^\n]%*c", titulo_buffer);
                novo->titulo = strdup(titulo_buffer);

                printf("Digite o Preço do produto: ");
                scanf("%lf", &novo->preco);

                char categoria_buffer[128];
                printf("Digite a Categoria do produto: ");
                scanf(" %127[^\n]%*c", categoria_buffer); // O espaço antes de %127 lê/ignora qualquer whitespace pendente.
                novo->categoria = strdup(categoria_buffer);                             
                
                novo->avaliacao_nota = 0;
                novo->avaliacao_contagem = 0;

                clock_t t_inicio = clock();
                raiz_avl = inserir_avl(raiz_avl, novo); 
                inserir_hash(th, novo);
                clock_t t_fim = clock();

                printf("Produto inserido com ID %d.\n", novo->id);
                printf("Tempo de inserção/balanceamento: %.6f segundos\n", ((double)(t_fim - t_inicio)) / CLOCKS_PER_SEC);
                break;
            }
            
            case 6: 
            {
                int id_remover;
                printf("Digite o ID do produto a ser removido: ");
                scanf("%d", &id_remover);

                // Primeiro, busca o produto na hash para pegar o preço
                Produto* p_para_remover = buscar_hash(th, id_remover);

                if (p_para_remover != NULL) 
                {
                    double preco_remover = p_para_remover->preco;

                    // Remove da Árvore AVL usando o preço
                    inicio = clock();
                    raiz_avl = remover_avl(raiz_avl, preco_remover, id_remover);
                    fim = clock();
                    double tempo_avl = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                    
                    // Remove da Tabela Hash usando o ID
                    inicio = clock();
                    remover_hash(th, id_remover);
                    fim = clock();
                    double tempo_hash = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                    printf("Produto com ID %d removido com sucesso.\n", id_remover);
                    printf("Tempo de remoção/balanceamento na AVL: %e segundos\n", tempo_avl);
                    printf("Tempo de remoção na Tabela Hash: %e segundos\n", tempo_hash);

                } else 
                {
                    printf("Produto com ID %d não encontrado para remoção.\n", id_remover);
                }
                break;
            }

            
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (escolha != 0);

    
    printf("Liberando toda a memória alocada...\n");
    
    for (int i = 0; i < num_produtos_total; i++) 
    {
        liberar_produto(todos_os_produtos[i]);
    }
    free(todos_os_produtos);
    liberar_tabela_hash(th);
    liberar_avl(raiz_avl);
    liberar_lista(vistos_recentemente);

    printf("Memória liberada. Programa encerrado com sucesso.\n");

    return 0;
}
