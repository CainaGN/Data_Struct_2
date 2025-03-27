#include <stdlib.h>
#include "queue.h"

queue *create_queue() 
{
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = q->last = NULL;
    q->qtd = 0;
    return q;
}

int is_empty(queue *q) 
{
    return (q->qtd == 0);
}

void enqueue(queue *q, node_tree *leaf) 
{
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->leaf = leaf;
    new_node->next = NULL;
    
    if (q->last == NULL) 
    {
        q->first = new_node;
    } else {
        q->last->next = new_node;
    }
    q->last = new_node;
    q->qtd++;
}

node_tree *dequeue(queue *q) 
{
    if (is_empty(q)) return NULL;
    queue_node *temp = q->first;
    node_tree *leaf = temp->leaf;
    q->first = q->first->next;
    if (q->first == NULL) 
    {
        q->last = NULL;
    }
    free(temp);
    q->qtd--;
    return leaf;
}

void destroy_queue(queue *q)
{
    while (!is_empty(q)) 
    {
        dequeue(q);
    }
    free(q);
}

