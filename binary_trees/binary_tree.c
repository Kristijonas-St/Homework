#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* left_child;
    struct node* right_child;
    int val;   
} node;

void insert_node(node**, int);
node* search_node(node**, int);
void delete_node(node**, int);
void print_tree(node*, int);

void insert_node(node** root, int value)
{
    if(!*root) {
        *root = (node*)malloc(sizeof(node));
        (*root)->val = value;
        (*root)->left_child = NULL;
        (*root)->right_child = NULL;
    
        return;
    }

    node* iteration = *root;
    node* new_node;

    int i = 0;
    while(1) {
        if(value < iteration->val) {

            if(iteration->left_child == NULL) {
                new_node = (node*)malloc(sizeof(node));
                iteration->left_child = new_node;
                new_node->val = value;
                return;
            } else {
                iteration = iteration->left_child;
            }

        } else {
            if(iteration->right_child == NULL) {
                new_node = (node*)malloc(sizeof(node));
                iteration->right_child = new_node;
                new_node->val = value;            
                return;
            } else {
                iteration = iteration->right_child;
            }

        }
    // printf("i amount: %d\n", ++i);
    }
    
}

node* search_node(node** root, int val)
{
    node* temp = *root;

    while(temp != NULL) {
        if(temp->val == val) {
            return temp;
        } else {
            temp = (val < temp->val) ? temp->left_child : temp->right_child;
        }
    }
    return NULL;
}

void delete_node(node** root, int value)
{
    
}



// not mine, just to check the functionality
void print_tree(node* root, int space)
{
    if(root == NULL) return;

    space += 5;

    print_tree(root->right_child, space);

    printf("\n");
    for(int i = 5; i < space; i++) printf(" ");
    printf("%d\n", root->val);

    print_tree(root->left_child, space);
}


int main(void)
{
    node* root = NULL;
    node* search_result;

    insert_node(&root, 6);
    insert_node(&root, 4);
    insert_node(&root, 3);
    insert_node(&root, 5);
    insert_node(&root, 7);
    insert_node(&root, 10);
    insert_node(&root, 11);
    insert_node(&root, 8);
    insert_node(&root, 1);
    insert_node(&root, 2);
    insert_node(&root, 9);
    insert_node(&root, 20);

    // search example
    int value = 11;
    search_result = search_node(&root, value);
    if(search_result == NULL) {
        printf("%d node doesn't exist!!!\n", value);
    } else {
        printf("FOUND %d\n", value);
    }

    print_tree(root, 0);
}