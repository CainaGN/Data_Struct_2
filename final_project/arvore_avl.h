#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "produto.h"

typedef struct NoAVL {
    Produto* produto; 
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
} NoAVL;


NoAVL* inserir_avl(NoAVL* no, Produto* p);
NoAVL* remover_avl(NoAVL* raiz, double preco, int id_a_remover);
void buscar_por_faixa_avl(NoAVL* raiz, double preco_min, double preco_max);
void imprimir_em_ordem_avl(NoAVL* raiz);
void liberar_avl(NoAVL* no);

#endif
