#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trees.h"

TreeNode* construct_node(data_t value)
{
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
    assert(node);
    node->value = value;
    return node;
}

TreeNode* insert_node(TreeNode* root, data_t value)
{
    if (!root)
    {
        return construct_node(value);
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    while (current != NULL)
    {
        parent = current;

        if (value <= current->value)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    TreeNode* new_node = construct_node(value);
    if (value < parent->value)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }

    return root;
}

TreeNode* remove_node(TreeNode* root, data_t value)
{
    if (!root)
    {
        return NULL;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    while (current && current->value != value)
    {
        parent = current;
        if (value < current->value)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (!current)
    {
        return root;
    }

    free_tree(current);

    if (!parent)
    {
        return NULL;
    }
    else if (parent->left == current)
    {
        parent->left = NULL;
    }
    else
    {
        parent->right = NULL;
    }

    return root;
}

void print_infix_node(const TreeNode* node)
{
    if (!node)
        return;

    printf("(");
    print_infix_node(node->left);
    printf("%d", node->value);
    print_infix_node(node->right);
    printf(")");
}

void free_tree(TreeNode* root)
{
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
