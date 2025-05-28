#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

#define RED 1
#define BLACK 0

struct Node 
{
    int data;
    struct Node *left, *right;
    int color;
};

int color(struct Node *H)
{
    if(H == NULL)
    {
        return BLACK;
    }
    else
    {
        return H->color;
    }
}

void change_color(struct Node *H)
{
    H->color = !H->color;
    if(H->left != NULL)
    {
        H->left->color = !H->left->color;
    }

    if(H->right != NULL)
    {
        H->right->color = !H->right->color;
    }
    
}

struct Node *left_rotation(struct Node *A)
{
    struct Node *B = A->right;
    A->right = B->left;
    B->left = A;
    B->color = A->color;
    A->color = RED;
    
    return B;
}

struct Node *right_rotation(struct Node *A)
{
    struct Node *B = A->left;
    A->left = B->right;
    B->right = A;
    B->color = A->color;
    A->color = RED;
    
    return B;
}

struct Node *move_to_left_red(struct Node *H)
{
    change_color(H);
    if(color(H->right->left) == RED)
    {
        H->right = right_rotation(H->right);
        H = left_rotation(H);
        change_color(H);
    }

    return H;
}

struct Node *move_to_right_red(struct Node *H)
{
    change_color(H);
    if(color(H->left->left) == RED)
    {
        H = right_rotation(H);
        change_color(H);
    }

    return H;
}

struct Node *balance(struct Node *H)
{
    //nó vermelho é sempre filho à esquerda
    if(color(H->right) == RED)
    {
        H = right_rotation(H);
    }

    //Filho da esquerda e neto da esquerda são vermelhos
    if(H->left != NULL && color(H->right) == RED && color(H->left->left) == RED)
    {
        H = right_rotation(H);
    }

    // 2 filhos vermelhos, troca a cor
    if(color(H->left) == RED && color(H->right) == RED)
    {
        change_color(H);
    }

    return H;
}

struct Node * insert_node(struct Node *H, int value, int *answer)
{
    if (H == NULL)
    {
        struct Node *new;
        new = (struct Node*)malloc(sizeof(struct Node));
        if (new == NULL)
        {
            *answer = 0;
            return NULL;
        }
        new->data = value;
        new->color = RED;
        new->right = NULL;
        new->left = NULL;
        *answer = 1;
        return new;
    }

    if(value == H->data)
    {
        *answer = 0; // valor duplicado
    }
    else
    {
        if(value < H->data)
        {
            H->left = insert_node(H->left, value, answer);
        }
        else
        {
            H->right = insert_node(H->right, value, answer);
        }
    }

    if(color(H->right) == RED && color(H->left) == BLACK)
    {
        H = left_rotation(H);
    }

    if(color(H->left) == RED && color(H->left->left) == RED)
    {
        H = right_rotation(H);
    }

    if(color(H->left) == RED && color(H->right) == RED)
    {
        change_color(H);
    }

    return H;
}

int insert_tree(rb_tree *root, int value)
{
    int answer;
    *root = insert_node(*root, value, &answer);
    if((*root) != NULL)
    {
        (*root)->color = BLACK;
    }
    return answer;
}

struct Node *remove_node(struct Node *H, int value)
{
    if (value < H->data)
    {
        if(color(H->left) == BLACK && color(H->left->left) == BLACK)
        {
            H = move_to_left_red(H);
        }
        H->left = remove_node(H->left, value);
    }
    else
    {
        if(color(H->left) == RED)
        {
            H = right_rotation(H);
        }
        if(value == H->data && (H->right == NULL))
        {
            free(H);
            return NULL;
        }
        if(color(H->right) == BLACK && color(H->right->left) == BLACK)
        {
            H = move_to_left_red(H);
        }

        if(value == H->data)
        {
            struct Node *x = search_smallest(H->right);
            H->data = x->data;
            H->right = remove_smaller(H->right);
        }
        else
        {
            H->right = remove_node(H->right, value);
        }
    }
    return balance(H);
}

int remove_tree(rb_tree *root, int value)
{
    if(search_tree(root, value))
    {
        struct Node *h = *root;
        *root = remove_node(h, value);
        
        if(*root != NULL)
        {
            (*root)->color = BLACK;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

struct Node *remove_smaller(struct Node *H)
{
    if(H->left == NULL)
    {
        free(H);
        return NULL;
    }

    if(color(H->left) == BLACK && color(H->left->left) == BLACK)
    {
        H = move_to_left_red(H);
    }
    H->left = remove_smaller (H->left);
    return balance(H);
}

struct Node *search_smallest(struct Node *current)
{
    struct Node *no1 = current;
    struct Node *no2 = current->left;

    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->left;
    }
    return no1;
}

int search_tree(rb_tree *root, int value)
{
    if (root == NULL)
    {
        return 0;
    }
    struct Node *current = *root;
    while (current != NULL)
    {
        if(value == current->data)
        {
            return 1;
        }
        if(value > current->data)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return 0;
}

void print_in_order(rb_tree root) {
    if (root != NULL) {
        print_in_order(root->left);
        printf("%d (%s)\n", root->data, root->color == RED ? "RED" : "BLACK");
        print_in_order(root->right);
    }
}