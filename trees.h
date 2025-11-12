#ifndef TREES_H
#define TREES_H

typedef char* data_t;

typedef struct TreeNode
{
    data_t value;
    TreeNode* left;
    TreeNode* right;
} TreeNode;

TreeNode* construct_node(data_t value);
TreeNode* insert_node(TreeNode* root, data_t value);
TreeNode* remove_node(TreeNode* root, data_t value);
void print_infix_node(const TreeNode* node);
void free_tree(TreeNode* root);

#endif
