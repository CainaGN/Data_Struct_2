#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "queue.h"

node_tree *create_new_node(int n)
{
    node_tree *temp = (node_tree*)malloc(sizeof(node_tree));
    temp->data = n;
    temp->left = temp->right = NULL;
    temp->level = 0;
    return temp;
}

node_tree *insert_node(node_tree *Node, int n)
{
    if (Node == NULL)
    {
        return create_new_node(n);
    }
    if (n <= Node->data)
    {
        Node->left = insert_node(Node->left, n);
    }
    else
    {
        Node->right = insert_node(Node->right, n);
    }
    return Node;
}



void print_left_rr(node_tree *Node)
{
    if (Node == NULL)
    {
        return;
    }
    print_left_rr(Node->left);
    printf("%i\t", Node->data);
    print_left_rr(Node->right);

}

void print_root_lr(node_tree *Node)
{
    if (Node == NULL)
    {
        return;
    }

    printf("%i\t", Node->data);
    print_root_lr(Node->right);
    print_root_lr(Node->left);
}

void print_left_right_root(node_tree *Node)
{
    if (Node == NULL)
    {
        return;
    }
    print_left_right_root(Node->left);
    print_left_right_root(Node->right);
    printf("%i\t", Node->data);
}


void bfs_print_levels(node_tree *root, int height)
{
    if (root == NULL) return;

    queue *q = create_queue();
    enqueue(q, root);

    root->level = 0;
    int current_level = 0;

    while (!is_empty(q))
    {
        node_tree *current = dequeue(q);

        if (current->level > current_level)
        {
            current_level = current->level;
            printf("\n");
        }

        int spaces = (1 << (height - current_level)) - 1;
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }

        printf("%d", current->data);

        spaces = (1 << (height - current_level + 1)) - 1;
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }

        if (current->left)
        {
            current->left->level = current->level + 1;
            enqueue(q, current->left);
        }
        if (current->right)
        {
            current->right->level = current->level + 1;
            enqueue(q, current->right);
        }
    }

    destroy_queue(q);
}

void destroy_tree(node_tree *Node)
{
    if (Node == NULL) return;
    destroy_tree(Node->right);
    destroy_tree(Node->left);
    free(Node);
}

int get_height(node_tree *Node)
{
    if (Node == NULL)
    {
        return 0;
    }
    int left = get_height(Node->left);
    int right = get_height(Node->right);
    return (left > right ? left : right) + 1;
}

int node_height(node_tree *node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        return node->level;
    }
}

int balance_factor(node_tree *node)
{
    if (node == NULL) return 0;
    return node_height(node->left) - node_height(node->right);
}

int bigger(int x, int y)
{
    if(x > y)
        return  x;
    else
        return y;
}

void ll_rotation(node_tree **node)
{
    node_tree *temp = (*node)->left;  
    (*node)->left = temp->right;     
    temp->right = *node;            

   
    (*node)->level = bigger(node_height((*node)->left), node_height((*node)->right)) + 1;
    temp->level = bigger(node_height(temp->left), node_height(temp->right)) + 1;

    *node = temp;  
}

void rr_rotation(node_tree **node)
{
    node_tree *temp = (*node)->right;  
    (*node)->right = temp->left;       
    temp->left = *node;                

   
    (*node)->level = bigger(node_height((*node)->left), node_height((*node)->right)) + 1;
    temp->level = bigger(node_height(temp->left), node_height(temp->right)) + 1;

    *node = temp;  
}

void lr_rotation(node_tree **node)
{
    rr_rotation(&((*node)->left));
    ll_rotation(node);
}

void rl_rotation(node_tree **node)
{
    ll_rotation(&((*node)->right));
    rr_rotation(node);
}

int avl_insert(node_tree **node, int data)
{
    int res;
    if(*node == NULL)
    {
        node_tree *new_node = (node_tree *)malloc(sizeof(node_tree));

        new_node->data = data;
        new_node->level = 0;
        new_node->right = NULL;
        new_node->left = NULL;

        *node = new_node;
        return 1;
    }

    node_tree *current = *node;

    if(data < current->data)
    {
        if((res = avl_insert(&(current->left), data)) == 1)
        {
            if(balance_factor(current) >= 2)
            {
                if(data < (*node)->left->data)
                {
                    ll_rotation(node);
                }
                else
                {
                    lr_rotation(node);
                }
            }
        }
    }
    else
    {
        if(data > current->data)
        {
            if((res = avl_insert(&(current->right), data)) == 1)
            {
                if(balance_factor(current) <= -2)
                {
                    if(data > (*node)->right->data)
                    {
                        rr_rotation(node);
                    }
                    else
                    {
                        rl_rotation(node);
                    }
                }
            }
        }
    }
    (*node)->level = bigger(node_height((*node)->left), node_height((*node)->right)) + 1;
    return res; 
}