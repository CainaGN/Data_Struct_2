#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int altura_no(NoAVL* no) 
{
    if (no == NULL) return 0;
    return no->altura;
}

int max(int a, int b) 
{
    return (a > b) ? a : b;
}


int fator_balanceamento(NoAVL* no) 
{
    if (no == NULL) return 0;
    return altura_no(no->esquerda) - altura_no(no->direita);
}

NoAVL* criar_no_avl(Produto* p) 
{
    NoAVL* no = (NoAVL*) malloc(sizeof(NoAVL));
    no->produto = p;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; 
    return no;
}


NoAVL* rotacao_direita(NoAVL* y) 
{
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    
    x->direita = y;
    y->esquerda = T2;


    y->altura = max(altura_no(y->esquerda), altura_no(y->direita)) + 1;
    x->altura = max(altura_no(x->esquerda), altura_no(x->direita)) + 1;

    return x; 
}


NoAVL* rotacao_esquerda(NoAVL* x) 
{
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura_no(x->esquerda), altura_no(x->direita)) + 1;
    y->altura = max(altura_no(y->esquerda), altura_no(y->direita)) + 1;

    return y; 
}

NoAVL* inserir_avl(NoAVL* no, Produto* p) 
{
    
    if (no == NULL) 
    {
        return criar_no_avl(p);
    }

    //  insere à esquerda.
    if (p->preco < no->produto->preco) 
    {
        no->esquerda = inserir_avl(no->esquerda, p);
    } else 
    { 
        no->direita = inserir_avl(no->direita, p);
    }

    // Atualiza a altura deste nó ancestral
    no->altura = 1 + max(altura_no(no->esquerda), altura_no(no->direita));

    // Calcula o fator de balanceamento para verificar se o nó ficou desbalanceado
    int fb = fator_balanceamento(no);

    /*  Se o nó ficou desbalanceado, existem 4 casos de rotação.

     Caso Esquerda-Esquerda (Rotação Simples à Direita) Se o nó está pesado à esquerda (fb > 1)
     e o filho esquerdo também está
     pesado à esquerda ou balanceado.*/
    if (fb > 1 && fator_balanceamento(no->esquerda) >= 0) 
    {
        return rotacao_direita(no);
    }

    // Caso Direita-Direita (Rotação Simples à Esquerda)
    // Se o nó está pesado à direita (fb < -1) e o filho direito também está
    // pesado à direita ou balanceado.
    if (fb < -1 && fator_balanceamento(no->direita) <= 0) 
    {
        return rotacao_esquerda(no);
    }

    // Caso Esquerda-Direita (Rotação Dupla)
    // Se o nó está pesado à esquerda (fb > 1), mas o filho esquerdo está
    // pesado à direita.
    if (fb > 1 && fator_balanceamento(no->esquerda) < 0) 
    {
        no->esquerda = rotacao_esquerda(no->esquerda);
        return rotacao_direita(no);
    }

    // Caso Direita-Esquerda (Rotação Dupla)
    // Se o nó está pesado à direita (fb < -1), mas o filho direito está
    // pesado à esquerda.
    if (fb < -1 && fator_balanceamento(no->direita) > 0) 
    {
        no->direita = rotacao_direita(no->direita);
        return rotacao_esquerda(no);
    }

    return no;
}


void buscar_por_faixa_avl(NoAVL* raiz, double preco_min, double preco_max) 
{
    if (raiz == NULL) 
    {
        return;
    }
    // Se o preço do nó atual for maior que o mínimo, pode haver correspondências na sub-árvore esquerda
    if (preco_min < raiz->produto->preco) 
    {
        buscar_por_faixa_avl(raiz->esquerda, preco_min, preco_max);
    }
    // Se o preço do nó atual está dentro da faixa, imprima-o
    if (preco_min <= raiz->produto->preco && preco_max >= raiz->produto->preco) 
    {
        imprimir_produto(raiz->produto);
    }
    // Se o preço do nó atual for menor que o máximo, pode haver correspondências na sub-árvore direita
    if (preco_max > raiz->produto->preco) 
    {
        buscar_por_faixa_avl(raiz->direita, preco_min, preco_max);
    }
}

void imprimir_em_ordem_avl(NoAVL* raiz) 
{
    if (raiz != NULL) {
        imprimir_em_ordem_avl(raiz->esquerda);
        imprimir_produto(raiz->produto);
        imprimir_em_ordem_avl(raiz->direita);
    }
}


void liberar_avl(NoAVL* no) 
{
    if (no == NULL) return;
    liberar_avl(no->esquerda);
    liberar_avl(no->direita);
    free(no);
}

NoAVL* encontrar_menor_no(NoAVL* no) 
{
    NoAVL* atual = no;
    while (atual && atual->esquerda != NULL) 
    {
        atual = atual->esquerda;
    }
    return atual;
}

NoAVL* remover_avl(NoAVL* raiz, double preco, int id_a_remover)
{
    //  árvore está vazia ou o nó não foi encontrado
    if (raiz == NULL)
    {
        return raiz;
    }

    // Procura pelo nó a ser removido (com base no preço)
    if (preco < raiz->produto->preco)
    {
        raiz->esquerda = remover_avl(raiz->esquerda, preco, id_a_remover);
    }
    else if (preco > raiz->produto->preco)
    {
        raiz->direita = remover_avl(raiz->direita, preco, id_a_remover);
    }
    else // O preço do nó atual (raiz) é igual ao preço a ser removido
    {
        //  VERIFICAR O ID PARA GARANTIR QUE É O PRODUTO CORRETO 
        if (raiz->produto->id == id_a_remover)
        {
            // Este é o NÓ EXATO que queremos remover.
            // Nó com zero ou um filho
            if ((raiz->esquerda == NULL) || (raiz->direita == NULL))
            {
                NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

                // Caso de nenhum filho (raiz se torna NULL)
                if (temp == NULL)
                {
                    temp = raiz; // temp agora aponta para o nó a ser liberado
                    raiz = NULL; // O nó foi removido, então seu pai apontará para NULL
                }
                else // Caso de um filho (raiz é substituído pelo filho)
                {
                    *raiz = *temp; // Copia o conteúdo do filho não-nulo para o nó atual
                }
                free(temp); // Libera o nó que foi "removido" (ou o original ou o filho copiado)
            }
            else // Nó com dois filhos
            {
                // Pega o  o menor sucessor da subárvore direita)
                NoAVL* temp = encontrar_menor_no(raiz->direita);

                // Copia o produto do sucessor para este nó
                raiz->produto = temp->produto;

                // Remove o sucessor em ordem da subárvore direita.
 
                raiz->direita = remover_avl(raiz->direita, temp->produto->preco, temp->produto->id); // MODIFICADO AQUI
            }
        }
        else
        {
            // O PREÇO É IGUAL, MAS O ID NÃO É, vai para direita
            raiz->direita = remover_avl(raiz->direita, preco, id_a_remover); 
        }
    }

    // Se a árvore tinha apenas um nó e ele foi removido, retorna NULL
    if (raiz == NULL)
    {
        return raiz;
    }


    raiz->altura = 1 + max(altura_no(raiz->esquerda), altura_no(raiz->direita));

    //  fator de balanceamento para verificar se precisa rebalancear
    int fb = fator_balanceamento(raiz);


    // Caso Esquerda-Esquerda
    if (fb > 1 && fator_balanceamento(raiz->esquerda) >= 0)
    {
        return rotacao_direita(raiz);
    }

    // Caso Esquerda-Direita
    if (fb > 1 && fator_balanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    // Caso Direita-Direita
    if (fb < -1 && fator_balanceamento(raiz->direita) <= 0)
    {
        return rotacao_esquerda(raiz);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && fator_balanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}
