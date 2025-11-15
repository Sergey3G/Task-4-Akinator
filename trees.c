#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#include "trees.h"

Answer answers[2] = {{"NO", NO},
                     {"YES", YES}};


TreeNode* construct_node(data_t value)
{
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
    assert(node);

    node->value = strdup(value);
    assert(node->value);

    node->yes = node->no = NULL;
    return node;
}

void print_infix_tree(const TreeNode* node)
{
    if (!node)
        return;

    printf("(");
    print_infix_tree(node->yes);
    printf("%s", node->value);
    print_infix_tree(node->no);
    printf(")");
}

void free_tree(TreeNode* root)
{
    if (!root)
        return;

    free_tree(root->yes);
    free_tree(root->no);
    free(root->value);
    free(root);
}

void tree_traversal(TreeNode* node)
{
    if (!node)
        return;

    printf("Is your character %s? Answer \"YES\" or \"NO\":\n", node->value);
    AnswersEnum answer_code = analyse_answer();

    switch (answer_code)
    {
        case NO:
            if (!node->no)
            {
                printf("I don't know your character! Please enter his name:\n");
                char new_character_name[MAX_NODE_VALUE_LEN] = {0};
                scanf(" %99[^\n]", new_character_name);
                printf("\n");

                printf("What is difference between your character and %s?\n", node->value);
                char new_question_name[MAX_NODE_VALUE_LEN] = {0};
                scanf(" %99[^\n]", new_question_name);

                char* old_value = node->value;
                TreeNode* old_yes = node->yes;
                TreeNode* old_no = node->no;

                node->value = strdup(new_question_name);

                node->no = construct_node(old_value);
                node->no->yes = old_yes;
                node->no->no = old_no;

                node->yes = construct_node(new_character_name);
                free(old_value);

                printf("You successfully added a new character!\n");

                return;
            }
            else
            {
                tree_traversal(node->no);
                return;
            }
        case YES:
            if (!node->yes)
            {
                printf("I guessed your character! I hope now you understand that I am cleverer than you!\n");
                return;
            }
            else
            {
                tree_traversal(node->yes);
                return;
            }
        default:
            return;
    }
}

AnswersEnum analyse_answer(void)
{
    char answer_name[4] = {0};

    while(1)
    {
        scanf("%3s", answer_name);

        for (size_t i = 0; i < 2; i++)
        {
            if (!strcmp(answers[i].name, answer_name))
            {
                return answers[i].code;
            }
        }

        printf("Your answer is incorrect! Please answer only \"YES\" or \"NO\"!\n");
    }
}

void run_game(TreeNode* root)
{
    while (1)
    {
        printf("MENU\n");
        printf("1 - Play Akinator\n");
        printf("2 - Compare 2 characters\n");
        printf("3 - Exit\n");
        printf("Enter your choice:\n");

        int choice = 0;
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nStarting game...\n\n");
                tree_traversal(root);
                break;
            case 2:
                printf("\nComparing characters...\n\n");
                compare_characters(root);
                break;
            case 3:
                printf("Goodbye!\n");
                return;
            default:
                printf("Incorrect answer!\n");
                break;
        }
    }
}

char* file_to_buffer(const char* filename)
{
    struct stat st;
    if (stat(filename, &st) != 0)
    {
        perror("stat failed\n");
        return NULL;
    }

    size_t file_size = (size_t)st.st_size;
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: cannot open file %s!\n", filename);
        return NULL;
    }

    char* buffer = (char*)calloc(file_size + 1, sizeof(char));
    if (!buffer)
    {
        printf("Error: memory allocarion failed!\n");
        return NULL;
    }

    size_t read_size = fread(buffer, sizeof(char), file_size, file);
    fclose(file);
    if (read_size != file_size)
    {
        printf("Error: cannot read file content!\n");
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0';
    return buffer;
}

TreeNode* construct_tree_from_buffer(char* buffer)
{
    char* current = buffer;
    return parse_tree(&current);
}

static void skip_spaces(char** p)
{
    while (**p == ' ' || **p == '\n' || **p == '\t')
        (*p)++;
}

TreeNode* parse_tree(char** p)
{
    skip_spaces(p);
    if (strncmp(*p, "nil", 3) == 0)
    {
        *p += 3;
        return NULL;
    }

    if (**p != '(')
    {
        return NULL;
    }

    (*p)++;
    skip_spaces(p);
    if (**p != '"')
    {
        return NULL;
    }

    (*p)++;

    char value[MAX_NODE_VALUE_LEN] = {0};
    int i = 0;

    while (**p && **p != '"' && i < MAX_NODE_VALUE_LEN - 1)
    {
        value[i++] = **p;
        (*p)++;
    }
    value[i] = '\0';
    if (**p == '"')
    {
        (*p)++;
    }

    TreeNode* node = construct_node(value);
    skip_spaces(p);
    node->yes = parse_tree(p);
    skip_spaces(p);
    node->no = parse_tree(p);
    skip_spaces(p);

    if (**p == ')')
    {
        (*p)++;
    }

    return node;
}

void print_prefix_tree(const TreeNode* node)
{
    if (!node)
    {
        printf(" nil ");
        return;
    }

    printf("(");
    printf("\"%s\"", node->value);
    print_prefix_tree(node->yes);
    print_prefix_tree(node->no);
    printf(")");
}

int find_path(TreeNode* root, const char* target, char* path, int depth)
{
    if (!root)
        return 0;

    if (!strcmp(root->value, target))
    {
        path[depth] = '\0';
        return 1;
    }

    path[depth] = 'Y';
    if (find_path(root->yes, target, path, depth + 1))
        return 1;

    path[depth] = 'N';
    if (find_path(root->no, target, path, depth + 1))
        return 1;

    return 0;
}

void print_common_questions(TreeNode* root, const char* p1, const char* p2)
{
    TreeNode* cur = root;
    int i = 0;

    printf("Common questions:\n");

    while (p1[i] && p2[i] && p1[i] == p2[i])
    {
        printf("- %s (ответ: %c)\n", cur->value, p1[i]);

        cur = (p1[i] == 'Y') ? cur->yes : cur->no;
        i++;
    }

    if (i == 0)
        printf("No common questions.\n");
    else
        printf("There are %d common questions.\n", i);
}

void print_first_difference(TreeNode* root, const char* p1, const char* p2)
{
    TreeNode* cur = root;
    int i = 0;

    while (p1[i] && p2[i] && p1[i] == p2[i])
    {
        cur = (p1[i] == 'Y') ? cur->yes : cur->no;
        i++;
    }

    if (!p1[i] || !p2[i])
    {
        printf("Characters are similar or one is subtree of another.\n");
        return;
    }

    printf("\nFirst different question:\n");
    printf("%s\n", cur->value);
    printf(" - character 1: %c\n", p1[i]);
    printf(" - character 2: %c\n", p2[i]);
}

void compare_paths(const char* p1, const char* p2)
{
    printf("Path 1: %s\n", p1);
    printf("Path 2: %s\n", p2);
}

void compare_characters(TreeNode* root)
{
    char name1[MAX_NODE_VALUE_LEN] = {0};
    char name2[MAX_NODE_VALUE_LEN] = {0};

    printf("Enter first character's name: ");
    scanf(" %99[^\n]", name1);

    printf("Enter second character's name: ");
    scanf(" %99[^\n]", name2);

    char path1[MAX_TREE_DEPTH] = {0};
    char path2[MAX_TREE_DEPTH] = {0};

    if (!find_path(root, name1, path1, 0))
    {
        printf("Character %s is not found in tree!\n", name1);
        return;
    }

    if (!find_path(root, name2, path2, 0))
    {
        printf("Character %s is not found in tree!\n", name2);
        return;
    }

    printf("Comparing:\n");
    compare_paths(path1, path2);
    printf("Common questions:\n");
    print_common_questions(root, path1, path2);
    printf("First different question:\n");
    print_first_difference(root, path1, path2);
}

