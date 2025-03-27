#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

List *List_create()
{
    List *list = (List *)calloc(1, sizeof(List));   
    return list;
}

void List_Destroy(DoubleLinkedList **list)
{
    Node *p = (*list)->begin;
    while (p != NULL)
    {
        Node *aux = p;
        p = p->next;
        free(aux);
    }
    free(*list);
    *list = NULL;
}

void List_add_last(DoubleLinkedList *list, int val)
{
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->val = val;
    novo->next = NULL;
    novo->prev = list->end;

    if (list->size == 0)
        list->begin = novo;
    else
        list->end->next = novo;

    list->end = novo;
    list->size++;
}

void tree_to_list(node_tree *Node, DoubleLinkedList *list)
{
    if (Node == NULL) return;
    tree_to_list(Node->left, list);
    List_add_last(list, Node->data);
    tree_to_list(Node->right, list);
}

void print_LL(DoubleLinkedList *L)
{
    Node *p = L->begin;
    printf("\nL -> ");
    while (p != NULL)
    {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");
}


