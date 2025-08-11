#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int val;
    struct list* next;
    struct list* prev;
} dll;

void insert_node(int, int, dll **, dll **);
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
        (*head)->prev = node;
        node->next = *head;
        *head = node;
        node->prev = NULL;
    } else {
        dll *temp;
        int i = 0;

        if(position == -1) {           
            (*tail)->next = node;
            node->prev = *tail;
            node->next = NULL;
            *tail = node;
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

        if(temp == *tail)
        {
            (*tail)->next = node;
            node->prev = *tail;
            node->next = NULL;
            *tail = node;
            return;
        }

        dll *temp2 = temp->next;        
        node->next = temp2;
        temp2->prev = node;

        temp->next = node;
        node->prev = temp;

    }
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

    insert_node(3, 0, &head, &tail);
    insert_node(2, 0, &head, &tail);
    insert_node(1, 0, &head, &tail);
    insert_node(4, -1, &head, &tail);
    insert_node(66, 2, &head, &tail);
    insert_node(100, 5, &head, &tail);
    insert_node(111, 5, &head, &tail);

    print_list(&head, &tail, 1);
    print_list(&head, &tail, 0);


}