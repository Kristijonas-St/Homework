#include <stdio.h>
#include <stdlib.h>

typedef struct ll {
    int val;
    struct ll *next;
} ll;

void insert_node(int, int, ll**, ll**);
void print_list(ll*);
void print_head_tail(ll*, ll*);
ll *search_for_value(ll **, ll**, int);
void delete(int, ll **, ll **);
void replace(int, int, ll **, ll **);

void insert_node(int val, int position, ll **head, ll **tail)
{
    ll *node = (ll*)malloc(sizeof(ll));
    node->val = val;

    // Linked List is empty
    if(!*tail && !*head) {
        node->next = NULL;
        *head = *tail = node;
        return;
    }

    // add first
    if(!position) {
        node->next = *head;
        *head = node;
    } else {
        ll* temp = *head;
        int i = 0;
        
        if(position == -1) {
            // add last
            (*tail)->next = node;
            node->next = NULL;
            *tail = node;
        } else {
            ll *temp = *head;
            int i = 0;

            while(i++ < position - 1) {
                temp = temp->next;
                if(!temp) {
                    printf("--- %d is out of bounds, NO BUENO\n", position);
                    free(node);
                    return;
                }
            }
            node->next = temp->next;
            temp->next = node;
        }
    }
}

void delete(int val, ll **head, ll **tail)
{
    ll *rmv, *temp = *head;

    if(!*head) {
        printf("Linked List is empty, exiting...\n");
        return;
    } else {
        rmv = search_for_value(head, tail, val);
        if(!rmv) {
            printf("Such node doesn't exist, exiting...\n");
            return;
        } else {
            if(rmv == *head) {
                // remove first
                *head = rmv->next;
            } else {
                while(temp->next != rmv) {
                    temp = temp->next;
                }

                temp->next = rmv->next;
                if(rmv == *tail) {
                    // remove last
                    *tail = temp;
                }
                free(rmv);
            }   
        }
    }
}

ll *search_for_value(ll **head, ll **tail, int val)
{
    ll *temp = *head;

    while(temp != (*tail)->next) {
        if(temp->val == val) {
            //printf("Found what you were looking for\n");
            return temp;
        }
        temp = temp->next;
    }

    printf("%d isn't in the linked list, exiting...\n", val);
    return NULL;
}

void print_list(ll *head)
{
    ll* node = head;
    
    printf("\n");
    if(!node) {
        printf("linked list is EMPTY\n");
        return;
    }

    while(node != NULL) {
        printf("%d", node->val);
        if(node->next != NULL) {
            printf(" -> ");
        }
        node = node->next;
    }
    printf("\n\n");
}

void print_head_tail(ll* head, ll *tail) 
{
    printf("HEAD: %d  TAIL: %d\n", head->val, tail->val);
}

void replace(int primary, int result, ll **head, ll **tail)
{
    ll *rep = search_for_value(head, tail, primary);
    if(!rep) {
        printf("%d doesn't exist, exiting...\n", primary);
        return;
    } else {
        rep->val = result;
    }
}

int main(void)
{
    ll *head = NULL, *tail = NULL;

    insert_node(5, 0, &head, &tail);
    insert_node(4, 0, &head, &tail);
    insert_node(3, 0, &head, &tail);
    insert_node(2, 0, &head, &tail);
    insert_node(1, 0, &head, &tail);
    insert_node(6, -1, &head, &tail);


    printf("Original List\n");
    print_list(head);

    delete(2, &head, &tail);
    replace(5, 55, &head, &tail);
    insert_node(22, 1, &head, &tail);
    insert_node(100, 100, &head, &tail);

    printf("\n\nAfterwards\n");
    print_list(head);

    return 0;
}