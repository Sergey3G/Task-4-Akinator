#include <stdio.h>
#include "trees.h"

void node_dump(const TreeNode* node, FILE* f, size_t* node_num)
{
    if (!f || !node || !node_num)
        return;

    size_t current_num = (*node_num)++;

    fprintf(f, "  node%zu [label=\"{address: %p | value = %d | {LEFT | RIGHT}}\"];\n",
            current_num, (void*)node, node->value);

    if (node->left)
    {
        size_t left_num = *node_num;
        node_dump(node->left, f, node_num);
        fprintf(f, "  node%zu -> node%zu;\n", current_num, left_num);
    }

    if (node->right)
    {
        size_t right_num = *node_num;
        node_dump(node->right, f, node_num);
        fprintf(f, "  node%zu -> node%zu;\n", current_num, right_num);
    }
}


void tree_dump(const TreeNode* root, const char* filename)
{
    if (!root || !filename)
        return;

    FILE* f = fopen(filename, "w");
    if (!f)
    {
        printf("Error: cannot open file '%s'\n", filename);
        return;
    }

    size_t node_num = 0;

    fprintf(f, "digraph G {\n");
    fprintf(f, "  bgcolor=\"#ffffffff\";\n");
    fprintf(f, "  node [shape=record, fontname=\"Helvetica\", fontsize=10, "
                "style=filled, fillcolor=\"#ded1d1ff\", fontcolor=\"#c20c0cff\", color=gray];\n");
    fprintf(f, "  edge [arrowsize=0.7, color=gray];\n\n");

    node_dump(root, f, &node_num);

    fprintf(f, "}\n");
    fclose(f);
}
