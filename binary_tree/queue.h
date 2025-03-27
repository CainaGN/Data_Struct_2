#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

typedef struct Queue_node 
{
    node_tree *leaf;
    struct Queue_node *next;
} queue_node;

typedef struct Queue 
{
    queue_node *first;
    queue_node *last;
    int qtd;
} queue;

queue *create_queue();
int is_empty(queue *q);
void enqueue(queue *q, node_tree *leaf);
node_tree *dequeue(queue *q);
void destroy_queue(queue *q);

#endif

