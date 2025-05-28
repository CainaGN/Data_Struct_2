#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"



int main() {
    rb_tree root = NULL;

    int values[] = {10, 20, 30, 15, 25, 5};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insert_tree(&root, values[i]);
    }

    printf("Árvore em ordem:\n");
    print_in_order(root);
    print_tree(root, 0);
    export_dot(root, "arvore1.dot");

    printf("\nRemovendo 15 e 10...\n");
    remove_tree(&root, 15);
    remove_tree(&root, 10);

    printf("Árvore após remoções:\n");
    print_in_order(root);
    print_tree(root, 0);
    export_dot(root, "arvore2.dot");



    return 0;
}
