#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* left_child;
    struct node* right_child;
    int val;   
} node;

void insert_node(node**, int);
void print_tree(node**);

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

void print_tree(node** root)
{
    int height = 0;
    node* iteration = *root, *l = NULL, *r = NULL;

    printf("%d\n", iteration->val);
    if(iteration->left_child != NULL) {
        l = iteration->left_child;
    } 
    if(iteration->right_child != NULL) {
        r = iteration->right_child;
    }
    
    while(1) {
        if(l != NULL) {
            printf("%d", l->val);
            l = l->left_child;
        }

        printf("\t");

        if(r != NULL) {
            printf("  %d", r->val);
            r = r->right_child;
        }

        if(l == NULL && r == NULL) {
            return;
        }
        
        printf("\n");
    } 


}

int main(void)
{
    node* root = NULL;
    insert_node(&root, 6);
    insert_node(&root, 4);
    insert_node(&root, 3);
    insert_node(&root, 5);
    insert_node(&root, 7);
    insert_node(&root, 8);
    insert_node(&root, 9);
    insert_node(&root, 2);
    

    print_tree(&root);
    
}