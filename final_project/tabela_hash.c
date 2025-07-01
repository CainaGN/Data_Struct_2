#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

TabelaHash* criar_tabela_hash(int tamanho) 
{
    TabelaHash* th = (TabelaHash*) malloc(sizeof(TabelaHash));
    th->tamanho = tamanho;
    th->quantidade = 0;
    th->entradas = (HashEntry*) malloc(sizeof(HashEntry) * tamanho);
    for (int i = 0; i < tamanho; i++) 
    {
        th->entradas[i].produto = NULL;
        th->entradas[i].estado = LIVRE;
    }
    return th;
}

unsigned int funcao_hash(int id, int tamanho) 
{
    return id % tamanho;
}


void inserir_hash(TabelaHash* th, Produto* p) 
{

    unsigned int hash_inicial = funcao_hash(p->id, th->tamanho);
    unsigned int indice = hash_inicial;
    int i = 1;

    while (th->entradas[indice].estado == OCUPADO) 
    {
        indice = (hash_inicial + i * i) % th->tamanho;
        i++;
        if (i > th->tamanho) 
        {
            printf("\nErro: Tabela Hash cheia. Não foi possível inserir.\n");
            return;
        }
    }

    th->entradas[indice].produto = p;
    th->entradas[indice].estado = OCUPADO;
    th->quantidade++;
}


Produto* buscar_hash(TabelaHash* th, int id) 
{
    unsigned int hash_inicial = funcao_hash(id, th->tamanho);
    unsigned int indice = hash_inicial;
    int i = 1;

    while (th->entradas[indice].estado != LIVRE) 
    {
        if (th->entradas[indice].estado == OCUPADO && th->entradas[indice].produto->id == id) 
        {
            return th->entradas[indice].produto;
        }
        indice = (hash_inicial + i * i) % th->tamanho;
        i++;
        if (indice == hash_inicial) 
        {
            break;
        }
    }
    
    return NULL; 
}


void liberar_tabela_hash(TabelaHash* th) 
{
    free(th->entradas);
    free(th);
}

void remover_hash(TabelaHash* th, int id) 
{
    unsigned int hash_inicial = funcao_hash(id, th->tamanho);
    unsigned int indice = hash_inicial;
    int i = 1;

    while (th->entradas[indice].estado != LIVRE) 
    {
        if (th->entradas[indice].estado == OCUPADO && th->entradas[indice].produto->id == id) 
        {
            th->entradas[indice].estado = REMOVIDO;
            th->quantidade--;
            return;
        }
        indice = (hash_inicial + i * i) % th->tamanho;
        i++;

        if (indice == hash_inicial) 
        {
            return;
        }
    }
}

