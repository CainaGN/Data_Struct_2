#include <stdio.h>
#include <stdlib.h>


int node_count = 0;



typedef struct Node_tree
{
	int data;
	struct Node_tree *left, *right;

} node_tree;

/*typedef struct Queue
{
	node_tree leaf[node_count];
	node_tree *prev;
	node_tree *next;
		
} queue;*/

node_tree *create_new_node (int n)
{
	node_tree *temp = (node_tree*)malloc(sizeof(node_tree));
	temp->data = n;
	temp->left = temp->right = NULL;
    return temp;
}

node_tree *insert_node(node_tree *Node, int n)
{
	if (Node == NULL)
	{
		return create_new_node(n);
	}
	else if (n < Node->data || n == Node->data)
	{
		Node->left = insert_node(Node->left, n);
	} else if (n > Node->data)
	{
		Node->right = insert_node(Node->right, n);
	}
	
	return Node;
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

void node_counter(node_tree *Node)
{
	if(Node == NULL)
	{
		return;
	}
	node_count++;
	node_counter(Node->left);
	node_counter(Node->right);
}

void print_node(node_tree *Node)
{
	return;
		
}

/*void print_tree(node_tree *Node)
{
	node_tree queue[node_count];
	

}*/

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




int main ()
{
	node_tree  *BST = create_new_node(1);
	
	insert_node(BST, 2);
	insert_node(BST, 3);
	insert_node(BST, 5);
	insert_node(BST, 8);
	insert_node(BST, 5);
	insert_node(BST, 1);
	
	node_counter(BST);
	printf("\nquantidade de folhas: %i\n", node_count);
	
	printf("Root-left-right:\n");
	print_root_lr(BST);
	printf("\nLeft-root-right\n");
	print_left_rr(BST);
	printf("\nLeft-right-root\n");
	print_left_right_root(BST);
	printf("\n");
	destroy_tree(BST);

}

/*
IMPRIMIR DE FORMA BONITINHA ARVORE, ESTRUTURADO EM ARVORE. Trazer o custo para ver qual é o mais eficiente. FAzer em forma de biblioteca. Na verdade, poe todas essas funçoes em uma biblioteca kkk
//Procurar saber sobre a biblioteca n8n

*/
//SMART POINTERS, pesquisar sobre isso!!!
