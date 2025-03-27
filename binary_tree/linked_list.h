#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "tree.h"  

typedef struct _double_node {
    int val;
    struct _double_node *next;
    struct _double_node *prev;
} DoubleNode, Node;

typedef struct _double_linked_list {
    Node *begin;
    Node *end;
    size_t size;
} DoubleLinkedList, List;

List *List_create();
void List_Destroy(DoubleLinkedList **list);
bool List_is_empty(const DoubleLinkedList *list);
void List_add_first(DoubleLinkedList *list, int val);
void List_add_last(DoubleLinkedList *list, int val);
void print_LL(DoubleLinkedList *L);
void rev_print_LL(DoubleLinkedList *L);
void tree_to_list(node_tree *Node, DoubleLinkedList *list);  

#endif

