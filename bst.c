#include <stdio.h>
#include <stdlib.h>


typedef struct List_node
{
	int leaf;
	struct List_node *next;
	struct List_node *prev;


} list_node;

typedef struct Node_tree 
{
    int data;
    struct Node_tree *left, *right;
    int level;
} node_tree;


/*-------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------*/
typedef struct Queue_node 
{
    node_tree *leaf;  //  ponteiro para o nó da árvore
    struct Queue_node *next;
} queue_node;

typedef struct Queue 
{
    queue_node *first;
    queue_node *last;
    int qtd;
} queue;

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

node_tree *create_new_node(int n) 
{
    node_tree *temp = (node_tree*)malloc(sizeof(node_tree));
    temp->data = n;
    temp->left = temp->right = NULL;
    temp->level = 0;
    return temp;
}

/*-------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------*/


node_tree *insert_node(node_tree *Node, int n) 
{
    if (Node == NULL) 
    {
        return create_new_node(n);
    } else if (n < Node->data || n == Node->data) 
    {
        Node->left = insert_node(Node->left, n);
    } else 
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


int get_height(node_tree *Node)
{
	if (Node == NULL)
	{
		return 0;
	}
	
	int left_node = get_height(Node->left);
	int right_node = get_height(Node->right);
	
	return (left_node > right_node ? left_node : right_node) + 1; // condiçao ? se verdadeiro : se falso	

}

int are_equals(node_tree *n1, node_tree *n2)
{

	if (n1 == NULL && n2 == NULL)
	{
		return 1;
	}
	
	if (n1 == NULL || n2 == NULL)
	{
		return 0;
	}
	
	 return (n1->data == n2->data) && are_equals(n1->left, n2->left) && are_equals(n1->right, n2->right);
}


/*-------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------*/



list_node *enlist_begin(list_node *list, int leaf)
{
	
	
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	
	new_node->leaf = leaf;
	new_node->next = list;
	new_node->prev = NULL;
	
	if (list != NULL)
	{
		list->prev = new_node;
	}
	
	return new_node;

} 

list_node *enlist_end(list_node *list, int leaf)
{
	
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	
	new_node->leaf = leaf;
	new_node->next = NULL;
	
  	if (list == NULL) 
  	{
		new_node->prev = NULL;
		return new_node;  
    }
	
	list_node *current = list;
	while(current->next != NULL)
	{
		current = current->next;
	}
	
	
	new_node->prev = list;
	list->next = new_node;
	
	return new_node;

} 

void delete_list(list_node *list) 
{
    if (list == NULL) 
    {
        return; 
    }
    delete_list(list->next); 
    free(list);              
}

void print_list(list_node *list) 
{
	printf("\nteste\n");
    if (list == NULL) 
    {
        return; 
    }
    printf("\t%i", list->leaf);
    print_list(list->next);
}

void ord_insertion(node_tree *Node, list_node *list)
{
	if (Node == NULL)
	{
		return;
	}
	ord_insertion(Node->left, list);
	enlist_begin(list, Node->data);
	ord_insertion(Node->right, list);
	
}


/*-------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------*/

int main() 
{
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
	
	int height = get_height(BST);
	printf("\nAltura: %i\n", height);
    printf("Busca em largura (BFS):\n");
    bfs_print_levels(BST, height);
    printf("\n");
	
	list_node *list = NULL;
	enlist_end(list, 3);
	enlist_end(list, 2);
	enlist_end(list, 3);
	enlist_end(list, 5);	
	
	//ord_insertion(BST, list); 
	
	print_list(list);
	
	delete_list(list);
    destroy_tree(BST);
    return 0;
}
