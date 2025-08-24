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
void delete_one_child(node**, int);
void delete_two_children(node **, node **, int);

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
    
    if(val == (*root)->val) {
        return *root;
    }
    
    node* parent = *root;
    node* temp;

    temp = (val > parent->val) ? parent->right_child : parent->left_child;
    while(temp != NULL) { // !temp doesnt work here????
        if(temp->val == val) {
            return parent;
        } else {
            parent = temp;
            temp = (val > temp->val) ? temp->right_child : temp->left_child;
        }
        
    }

    printf("No luck finding %d...\n", val);
    return NULL;
}

void delete_node(node** root, int val)
{    
    node* parent = search_node(root, val);
    if(parent == NULL) {
        printf("Node %d doesn't exist, returning...\n", val);
        return;
    } else if(parent == *root) {
        if(val == (*root)->val) {
            printf("Haven't implemented deleting the root just yet\n");
        }
    }

    node* to_delete = (val > parent->val) ? parent->right_child : parent->left_child;
    
    if(to_delete->left_child == NULL && to_delete->right_child == NULL) {
        delete_leaf(&parent, val);
    } else if(to_delete->left_child != NULL && to_delete->right_child != NULL) {
        delete_two_children(root, &parent, val);
    } else {
        delete_one_child(&parent, val);
    }
}

void delete_one_child(node** temp, int val)
{
    printf("Going to delete a node with ONE child\n");

    node* to_delete = (val > (*temp)->val) ? (*temp)->right_child : (*temp)->left_child;
    node* new_child = (to_delete->left_child != NULL) ? to_delete->left_child : to_delete->right_child;

    if((*temp)->left_child == to_delete) {
        (*temp)->left_child = new_child;
    } else {
        (*temp)->right_child = new_child;
    }
    free(to_delete);
}

void delete_two_children(node **root, node** temp, int val)
{
    printf("Going to delete a node with TWO children: %d\n", val);

    node* node_to_be_deleted = (val > (*temp)->val) ? (*temp)->right_child : (*temp)->left_child;
    node* bigger_smallest = node_to_be_deleted->right_child;

    // eini vienakart i desine, tada kol gali i kaire 
    while(bigger_smallest->left_child != NULL) {
        bigger_smallest = bigger_smallest->left_child;
    }
    printf("to_delete: %d\tbigger_smallest %d\n", node_to_be_deleted->val, bigger_smallest->val);

    // replace one another
    node_to_be_deleted->val = bigger_smallest->val;
    bigger_smallest->val = val;

    // search for new leaf and delete it
    node* parent = search_node(&(node_to_be_deleted->right_child), val);
    printf("Found the parent: %d\n", parent->val);
    if(parent->val == val) {
        parent = node_to_be_deleted;
    }
    delete_leaf(&parent, val);

}

void delete_leaf(node **parent, int val)
{

    node* leaf_to_delete;
    node *l, *r;

    if((*parent)->left_child != NULL) {
        l = (*parent)->left_child;
        if(l->val == val) {
            leaf_to_delete = (*parent)->left_child;
            (*parent)->left_child = NULL;
            goto freeing;
        }
    } 
    if((*parent)->right_child != NULL) {
        r = (*parent)->right_child;
        if(r->val == val) {
            leaf_to_delete = (*parent)->right_child;
            (*parent)->right_child = NULL;
            goto freeing;
        }
    } 
freeing:
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

    insert_node(&root, 20);
    insert_node(&root, 65);
    insert_node(&root, 42);
    insert_node(&root, 33);
    insert_node(&root, 13);
    insert_node(&root, 50);
    insert_node(&root, 45);
    insert_node(&root, 44);

    printf("Initial tree\n");
    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 44);
    print_tree(root, 0);    
    printf("\n\n");

    delete_node(&root, 13);
    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 65);
    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 42);
    print_tree(root, 0);
    printf("\n\n");

    delete_node(&root, 45);
    print_tree(root, 0);
    printf("\n\n");

}
