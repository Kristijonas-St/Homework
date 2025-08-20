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
void delete_leaf(node**, int);

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
    node* parent = *root;
    node* temp;

    if((*root)->val == val) {
        printf("It's root, need special attention here\n");
        return NULL;
    }

    temp = (val > parent->val) ? parent->right_child : parent->left_child;
    while(temp != NULL) { // !temp doesnt work here????
        if(temp->val == val) {
            printf("Found %d\n", val);
            return parent;
        } else {
            parent = temp;
            temp = (val > temp->val) ? temp->right_child : temp->left_child;
        }
    }

    return NULL;
}

void delete_node(node** root, int val)
{
    node* parent = search_node(root, val);
    if(parent == NULL) {
        printf("Node %d doesn't exist, returning...\n", val);
        return;
    }

    node* to_delete = (val > parent->val) ? parent->right_child : parent->left_child;
    
    if(to_delete->left_child == NULL && to_delete->right_child == NULL) {
        delete_leaf(&parent, val);
    } else if(to_delete->left_child != NULL && to_delete->right_child != NULL) {
        printf("Goind to delete a node with TWO children\n");
    } else {
        printf("Going to delete a node with ONE child\n");
    }
}

void delete_leaf(node** temp, int val)
{
    printf("%d: Goind to delete a LEAF\n", val);
    node* leaf_to_delete;
    
    if(val > (*temp)->val) {
        leaf_to_delete = (*temp)->right_child;
        (*temp)->right_child = NULL;
    } else {
        leaf_to_delete = (*temp)->left_child;
        (*temp)->left_child = NULL;
    }
    free(leaf_to_delete);  
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
    node* search_result, *temp;

    insert_node(&root, 6);
    insert_node(&root, 4);
    insert_node(&root, 3);
    insert_node(&root, 5);
    insert_node(&root, 7);
    insert_node(&root, 8);

    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 8);
    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 7);
    print_tree(root, 0);    
    printf("\n\n");

}