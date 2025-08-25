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
void delete_two_children(node **, int);
void delete_root(node **, int);
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
    // For checking if root is the parent BEGIN
    node *l, *r;
    if((*root)->left_child != NULL) {
        l = (*root)->left_child;
        if(l->val == val) {
            return *root;
        }
    }

    if((*root)->right_child != NULL) {
        r = (*root)->right_child;
        if(r->val == val) {
            return *root;
        }
    }
    // For checking if root is the parent END


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
    printf("Delete %d\n", val);
    // Need to delete the root;
    if(val == (*root)->val) {
        delete_root(root, val);
        return;
    } 
    
    node* parent = search_node(root, val);
    if(parent == NULL) {
        printf("Node %d doesn't exist, returning...\n", val);
        return;
    } 

    // If it exists, just proceed...
    node* to_delete = (val > parent->val) ? parent->right_child : parent->left_child;
    
    if(to_delete->left_child == NULL && to_delete->right_child == NULL) {
        delete_leaf(&parent, val);
    } else if(to_delete->left_child != NULL && to_delete->right_child != NULL) {
        delete_two_children(&parent, val);
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
    // free(to_delete);
}

void delete_two_children(node** temp, int val)
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
            free(leaf_to_delete);
            (*parent)->left_child = NULL;
            return;
        }
    } 
    if((*parent)->right_child != NULL) {        
        r = (*parent)->right_child;
        if(r->val == val) {
            leaf_to_delete = (*parent)->right_child;
            free(leaf_to_delete);
            (*parent)->right_child = NULL;
            return;
        }
    } 
}

void delete_root(node **root, int val)
{
    if((*root)->left_child != NULL && (*root)->right_child != NULL) {
        goto quick_test;
        
    } else if((*root)->left_child == NULL && (*root)->right_child == NULL) {
        free(*root);
        *root = NULL;
        return;
    } else if((*root)->right_child == NULL && (*root)->left_child != NULL) {
        node* old_left_child = (*root)->left_child;
        node* new_left_child = old_left_child->left_child;
        node* old_root = *root;

        *root = old_left_child;
        (*root)->left_child = new_left_child;

        free(old_root);
        old_root = NULL;

    } 
    else {
quick_test:        
        
        node* r = (*root)->right_child;
        node* bigger_smallest;
        

        if(r->left_child == NULL) {
            node* old_right_child = (*root)->right_child;
            node* new_right_child = old_right_child->right_child;
            node* old_left_child = (*root)->left_child;
            node* old_root = *root;

            *root = old_right_child;
            (*root)->right_child = new_right_child;
            (*root)->left_child = old_left_child;

            free(old_root);
            old_root = NULL;            
            return;
        } else {
            bigger_smallest = (*root)->right_child;
        }

        while(bigger_smallest->left_child != NULL) {
            bigger_smallest = bigger_smallest->left_child;
        }

        // replace one another
        int temp_root = (*root)->val;
        (*root)->val = bigger_smallest->val;
        bigger_smallest->val = temp_root;

        // delete old_root_val
        node* right_subtree = (*root)->right_child;
        if(right_subtree->val == val) {
            delete_leaf(root, val);
            return;    
        }

        node* to_delete = search_node(&right_subtree, val);
        delete_leaf(&to_delete, val);
        return;
    }
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

    insert_node(&root, 70);
    insert_node(&root, 40);
    insert_node(&root, 60);
    


    printf("Initial tree\n");
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");     
    } else printf("Tree is empty\n");

    delete_node(&root, 70);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 10);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 5);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");    

    insert_node(&root, 20);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 100);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 80);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 50);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 45);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    // Delete root with two children
    delete_node(&root, 40);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n"); 

    delete_node(&root, 45);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    delete_node(&root, 50);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    delete_node(&root, 60);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    delete_node(&root, 80);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");

    insert_node(&root, 101);
    if(root != NULL) {
        print_tree(root, 0);
        printf("\n__________________________\n");    
    } else printf("Tree is empty\n");
}
