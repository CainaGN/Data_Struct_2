#ifndef LISTA_H
#define LISTA_H

#include "produto.h"


typedef struct NoLista 
{
    Produto* produto;
    struct NoLista* anterior;
    struct NoLista* proximo;
} NoLista;


typedef struct 
{
    NoLista* cabeca;
    NoLista* cauda;
    int tamanho;
    int capacidade_max;
} ListaDE;


ListaDE* criar_lista(int capacidade);
void inserir_inicio_lista(ListaDE* lista, Produto* p);
void imprimir_lista(ListaDE* lista);
void liberar_lista(ListaDE* lista);

#endif 
