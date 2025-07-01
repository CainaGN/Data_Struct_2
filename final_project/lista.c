#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

ListaDE* criar_lista(int capacidade) 
{
    ListaDE* lista = (ListaDE*) malloc(sizeof(ListaDE));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->tamanho = 0;
    lista->capacidade_max = capacidade;
    return lista;
}


void remover_fim_lista(ListaDE* lista)
 {
    if (lista->cauda == NULL) return;

    NoLista* no_removido = lista->cauda;
    lista->cauda = no_removido->anterior;

    if (lista->cauda != NULL) 
    {
        lista->cauda->proximo = NULL;
    } else {
        // A lista só tinha um elemento
        lista->cabeca = NULL;
    }

    free(no_removido); 
    lista->tamanho--;
}

void inserir_inicio_lista(ListaDE* lista, Produto* p) 
{
    if (lista == NULL || p == NULL) return;

    // Se a lista está cheia, remove o último elemento para dar espaço
    if (lista->tamanho >= lista->capacidade_max) 
    {
        remover_fim_lista(lista);
    }
    
    NoLista* novo_no = (NoLista*) malloc(sizeof(NoLista));
    novo_no->produto = p;
    novo_no->anterior = NULL;
    novo_no->proximo = lista->cabeca;

    if (lista->cabeca != NULL) 
    {
        lista->cabeca->anterior = novo_no;
    }
    
    lista->cabeca = novo_no;

    if (lista->cauda == NULL) 
    {
        lista->cauda = novo_no;
    }
    
    lista->tamanho++;
}

void imprimir_lista(ListaDE* lista) 
{
    if (lista->cabeca == NULL) 
    {
        printf("Nenhum produto visto recentemente.\n");
        return;
    }

    NoLista* atual = lista->cabeca;
    int i = 1;
    while (atual != NULL) 
    {
        printf("--- %d ---\n", i++);
        imprimir_produto(atual->produto);
        atual = atual->proximo;
    }
}

void liberar_lista(ListaDE* lista) 
{
    NoLista* atual = lista->cabeca;
    while (atual != NULL) 
    {
        NoLista* proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    free(lista);
}
