#include <stdio.h>
#include <stdlib.h>

#include "trees.h"
#include "graph.h"
#include "user_interface.h"

int main(const int argc, const char* const argv[])
{
    if (argc < 3)
    {
        printf("You didn't enter enough filenames!\n");
        return 1;
    }

    const char* tree_filename = argv[1];
    const char* dump_filename = argv[2];

    char* string = file_to_buffer(tree_filename);
    if (!string)
    {
        printf("Error: cannot read file %s!\n", tree_filename);
        return 1;
    }


    TreeNode* root = construct_tree_from_buffer(string);
    if (!root)
    {
        printf("Cannot construct tree!\n");
        free(string);
        return 1;
    }

    if (ui_init() == 0)
    {
        fprintf(stderr, "UI initialization failed!\n");
        return 1;
    }

    run_game(root);
    tree_dump(root, dump_filename);
    ui_shutdown();

    FILE* output_file = fopen(tree_filename, "w");
    if (!output_file)
    {
        printf("Error: cannot open file %s!\n", tree_filename);
        return 1;
    }
    tree_to_file(output_file, root);

    free_tree(root);
    free(string);
    return 0;
}

