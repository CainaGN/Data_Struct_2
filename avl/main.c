#include <stdio.h>
#include "avl.h"
#include "queue.h"

int main()
{
    node_tree *BST = create_new_node(4);
    avl_insert(&BST, 1);
    avl_insert(&BST, 1);
    avl_insert(&BST, 2);
    avl_insert(&BST, 3);
    avl_insert(&BST, 5);
    avl_insert(&BST, 8);
    avl_insert(&BST, 13);
    avl_insert(&BST, 21);
	
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
    

    destroy_tree(BST);
    return 0;
}

