#include <stdio.h>

#include "trees.h"
#include "graph.h"

int main(const int argc, const char* const argv[])
{
    if (argc < 2)
    {
        printf("You didn't enter the filename!\n");
        return 1;
    }

    const char* filename = argv[1];

    TreeNode* root = NULL;

    root = insert_node(root, 10);
    root = insert_node(root, 5);
    root = insert_node(root, 20);
    root = insert_node(root, 15);
    root = insert_node(root, 25);

    print_infix_node(root);
    printf("\n");

    tree_dump(root, filename);

    free_tree(root);
    return 0;
}
