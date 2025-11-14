#include <stdio.h>
#include <stdlib.h>
#include "trees.h"
#include "graph.h"

int main(const int argc, const char* const argv[])
{
    if (argc < 3)
    {
        printf("You didn't enter enough filenames!\n");
        return 1;
    }

    const char* filename_1 = argv[1];
    const char* filename_2 = argv[2];

    /*
    TreeNode* animal = construct_node("animal");
    TreeNode* beautiful = construct_node("Beautiful");
    TreeNode* poltorashka = construct_node("Poltorashka");
    TreeNode* kabanchik = construct_node("kabanchik");
    TreeNode* lecturer = construct_node("lecturer");
    TreeNode* petrovich = construct_node("Petrovich");
    TreeNode* pasha_t = construct_node("Pasha T");

    animal->yes = beautiful;
    beautiful->yes = poltorashka;
    beautiful->no = kabanchik;
    animal->no = lecturer;
    lecturer->yes = petrovich;
    lecturer->no = pasha_t;

    run_game(animal);

    print_infix_tree(animal);
    tree_dump(animal, filename);
    printf("\n");
    */

    char* string = file_to_buffer(filename_1);
    TreeNode* root = construct_tree_from_buffer(string);

    tree_dump(root, filename_2);
    printf("%s", string);
    print_prefix_tree(root);
    printf("\n");

    free_tree(root);
    free(string);
    return 0;
}

