#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct list {
    int val;
    struct list* next;
    struct list* prev;
} dll;

void insert_node(int, int, dll **, dll **);
void insert_first(dll **, dll **, dll **);
void insert_last(dll **, dll **, dll **);
void delete_node(dll **, dll **, int);
void delete_first(dll **, dll **);
void delete_last(dll **, dll **);
void print_list(dll **, dll **, int);

void insert_node(int val, int position, dll **head, dll **tail)
{

    dll *node = (dll*)malloc(sizeof(dll));
    node->val = val;
    
    if(!*head && !*tail) {
        node->next = NULL;
        node->prev = NULL;
        *head = *tail = node;
        return;
    } 

    if(!position) {
        insert_first(head, tail, &node);
        return;
    } else {
        dll *temp;
        int i = 0;

        if(position == -1) {           
            insert_last(head, tail, &node);
            return;
        }

        temp = *head;
        while(i++ < position - 1) {
            temp = temp->next;
            if(!temp) {
                printf("Out of bounds, exiting...\n");
                free(node);
                return;
            }
        }

        if(temp == *tail) {
            insert_last(head, tail, &node);
            return;
        } else if(temp == *head) {
            insert_first(head, tail, &node);
            return;
        }

        dll *temp2 = temp->next;        
        node->next = temp2;
        temp2->prev = node;

        temp->next = node;
        node->prev = temp;
    }
}

void insert_first(dll **head, dll **tail, dll **node)
{
    (*head)->prev = *node;
    (*node)->next = *head;
    *head = *node;
    (*node)->prev = NULL;
}

void insert_last(dll **head, dll **tail, dll **node)
{
    (*tail)->next = *node;
    (*node)->prev = *tail;
    (*node)->next = NULL;
    *tail = *node;
}

void delete_node(dll **head, dll **tail, int position)
{
    if(!*head && !*tail) {
        printf("Can't remoave from empty list, returning...\n");
        return;
    }
    
    if(!position) {
        delete_first(head, tail);
    } else if(position == -1) {
        delete_last(head, tail);
    } else {
        dll *temp = *head;
        int i = 0;

        while(i++ < position - 1) {
            temp = temp->next;
            if(!temp) {
                printf("Out of bounds, returning...\n");
                return;
            }
        }

        if(temp == *head) {
            delete_first(head, tail);
        } else if(temp == *tail) {
            delete_last(head, tail);
        } else {
            dll *temp2 = temp->prev, *temp3 = temp->next;
            temp2->next = temp->next;
            temp3->prev = temp2;
        }
    }
}

void delete_first(dll **head, dll **tail)
{
    dll *temp = (*head)->next;
    *head = temp;
    (*head)->next = temp->next;
    (*head)->prev = NULL;
}

void delete_last(dll **head, dll **tail)
{
    dll *temp = (*tail)->prev;
    *tail = temp;
    (*tail)->prev = temp->prev;
    (*tail)->next = NULL;
}

void print_list(dll **head, dll **tail, int pole)
{
    printf("\n");
    if(!pole) {
        printf("Going backwards\n");
        dll *temp = *tail;

        while(temp != (*head)->prev) {
            printf("%d", temp->val);
            if(temp->prev != NULL) {
                printf(" -> ");
                
            }
            temp = temp->prev;
            
        }
    } else {
        printf("Going forward\n");
        dll* temp = *head;

        while(temp != (*tail)->next) {
            printf("%d", temp->val);
            if(temp->next != NULL) {
                printf(" ⇄ ");
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// ⇄
int main(void)
{
    dll *head = NULL, *tail = NULL;
    double time_used = 0;
    
    clock_t start = clock();
    long num_of_ops = 1000000;

    for (int i = 0; i < num_of_ops; i++) {
        insert_node(i, -1, &head, &tail);
    }
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    double ops_per_sec = (double)num_of_ops / seconds;

    printf("Total time: %.8f sec\n", seconds);
    printf("Ops per second: %.2f\n", ops_per_sec);

    return 0;
}