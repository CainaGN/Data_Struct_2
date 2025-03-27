#ifndef TREE_H
#define TREE_H

typedef struct Node_tree 
{
    int data;
    struct Node_tree *left, *right;
    int level;
} node_tree;

node_tree *create_new_node(int n);
node_tree *insert_node(node_tree *Node, int n);
void print_left_rr(node_tree *Node);
void print_root_lr(node_tree *Node);
void print_left_right_root(node_tree *Node);
void bfs_print_levels(node_tree *root, int height);
void node_counter(node_tree *Node, int *count);
void destroy_tree(node_tree *Node);
int get_height(node_tree *Node);
int are_equals(node_tree *n1, node_tree *n2);

#endif

