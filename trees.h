#ifndef TREES_H
#define TREES_H

#define MAX_NODE_VALUE_LEN 100
#define MAX_TREE_DEPTH 256

typedef char* data_t;

typedef enum AnswersEnum
{
    NO = 0,
    YES = 1
} AnswersEnum;

typedef struct TreeNode
{
    data_t value;
    struct TreeNode* yes;
    struct TreeNode* no;
} TreeNode;

typedef struct Answer
{
    char name[4];
    AnswersEnum code;
} Answer;

TreeNode* construct_node(data_t value);
void print_infix_tree(const TreeNode* node);
void free_tree(TreeNode* root);
void tree_traversal(TreeNode* root);
AnswersEnum analyse_answer(void);
void run_game(TreeNode* root);
char* file_to_buffer(const char* filename);
TreeNode* construct_tree_from_buffer(char* buffer);
TreeNode* parse_tree(char** p);
void print_prefix_tree(const TreeNode* node);
void compare_characters(TreeNode* root);

#endif

