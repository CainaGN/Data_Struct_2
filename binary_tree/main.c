#include <stdio.h>
#include "tree.h"
#include "linked_list.h"

int main()
{
    node_tree *BST = create_new_node(4);
    insert_node(BST, 1);
    insert_node(BST, 1);
    insert_node(BST, 2);
    insert_node(BST, 3);
    insert_node(BST, 5);
    insert_node(BST, 8);
    insert_node(BST, 13);
    insert_node(BST, 21);
	
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
    

	
	
    List *list = List_create();
    tree_to_list(BST, list);
    print_LL(list);

    List_Destroy(&list);
    destroy_tree(BST);
    return 0;
}
