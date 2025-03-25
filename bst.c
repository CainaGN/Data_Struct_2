#include <stdio.h>
#include <stdlib.h>

typedef struct Node_tree {
    int data;
    struct Node_tree *left, *right;
    int level;
} node_tree;

typedef struct Queue_node {
    node_tree *leaf;  //  ponteiro para o nó da árvore
    struct Queue_node *next;
} queue_node;

typedef struct Queue {
    queue_node *first;
    queue_node *last;
    int qtd;
} queue;

node_tree *create_new_node(int n) {
    node_tree *temp = (node_tree*)malloc(sizeof(node_tree));
    temp->data = n;
    temp->left = temp->right = NULL;
    temp->level = 0;
    return temp;
}

node_tree *insert_node(node_tree *Node, int n) {
    if (Node == NULL) {
        return create_new_node(n);
    } else if (n < Node->data || n == Node->data) {
        Node->left = insert_node(Node->left, n);
    } else {
        Node->right = insert_node(Node->right, n);
    }
    return Node;
}

queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = q->last = NULL;
    q->qtd = 0;
    return q;
}

int is_empty(queue *q) {
    return (q->qtd == 0);
}

void enqueue(queue *q, node_tree *leaf) {
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->leaf = leaf;
    new_node->next = NULL;

    if (q->last == NULL) {
        q->first = new_node;
    } else {
        q->last->next = new_node;
    }
    q->last = new_node;
    q->qtd++;
}

node_tree *dequeue(queue *q) {
    if (is_empty(q)) return NULL;

    queue_node *temp = q->first;
    node_tree *leaf = temp->leaf;
    q->first = q->first->next;
    if (q->first == NULL) {
        q->last = NULL;
    }
    free(temp);
    q->qtd--;
    return leaf;
}

void destroy_queue(queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
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

void bfs_print_levels(node_tree *root) {
    if (root == NULL) return;

    queue *q = create_queue();
    enqueue(q, root);

    int current_level = 0;
    printf("Nível %d: ", current_level);

    while (!is_empty(q)) {
        node_tree *current = dequeue(q);
        
        if (current->level > current_level) {
            current_level = current->level;
            printf("\nNível %d: ", current_level);
        }

        printf("%d ", current->data);

        if (current->left) {
            current->left->level = current->level + 1;
            enqueue(q, current->left);
        }
        if (current->right) {
            current->right->level = current->level + 1;
            enqueue(q, current->right);
        }
    }

    destroy_queue(q);
}

void node_counter(node_tree *Node, int count)
{
	if(Node == NULL)
	{
		return;
	}
	count++;
	node_counter(Node->left, count);
	node_counter(Node->right, count);
}

void destroy_tree(node_tree *Node)
{	
	if (Node == NULL)
	{
		return;
	}
	destroy_tree(Node->right);
	destroy_tree(Node->left);
	
	free(Node);
}

int main() {
    node_tree *BST = create_new_node(4);

    insert_node(BST, 2);
    insert_node(BST, 6);
    insert_node(BST, 1);
    insert_node(BST, 3);
    insert_node(BST, 5);
    insert_node(BST, 7);

    int count = 0;
    node_counter(BST, count);
	printf("\nquantidade de folhas: %i\n", count);
	
	printf("Root-left-right:\n");
	print_root_lr(BST);
	printf("\nLeft-root-right\n");
	print_left_rr(BST);
	printf("\nLeft-right-root\n");
	print_left_right_root(BST);
	printf("\n");
	

    printf("Busca em largura (BFS):\n");
    bfs_print_levels(BST);
    printf("\n");


    destroy_tree(BST);
    return 0;
}
