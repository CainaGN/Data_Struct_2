#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "produto.h"

typedef enum 
{
    LIVRE,
    OCUPADO,
    REMOVIDO
} EstadoSlot;


typedef struct 
{
    Produto* produto;
    EstadoSlot estado;
} HashEntry;


typedef struct 
{
    HashEntry* entradas;
    int tamanho;
    int quantidade;
} TabelaHash;


TabelaHash* criar_tabela_hash(int tamanho);
void inserir_hash(TabelaHash* th, Produto* p);
Produto* buscar_hash(TabelaHash* th, int id);
void remover_hash(TabelaHash* th, int id);
void liberar_tabela_hash(TabelaHash* th);

#endif 
