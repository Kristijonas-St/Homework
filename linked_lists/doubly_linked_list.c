#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BENCHMARKING 0

typedef struct list {
    int val;
    struct list* next;
    struct list* prev;
} dll;

// CRUD
void Create(dll**, dll**, int, int);
dll* Read(dll**, dll**, int, int);
void Update(dll**, dll**, int, int);
void Delete(dll**, dll**, int);

void insert_first(dll **, dll **, dll **);
void insert_last(dll **, dll **, dll **);
void delete_first(dll **, dll **);
void delete_last(dll **, dll **);
void print_list(dll **, dll **, int);

void Create(dll** head, dll** tail, int val, int position)
{
    dll *node = (dll*)malloc(sizeof(dll));
    node->val = val;
    
    // Linked List is empty
    if(!*head && !*tail) {
        node->next = NULL;
        node->prev = NULL;
        *head = *tail = node;
        return;
    } 

    // 0 implies First position
    if(!position) {
        insert_first(head, tail, &node);
        return;
    } else {
        dll *temp;
        int i = 0;

        // -1 implies Last position
        if(position == -1) {           
            insert_last(head, tail, &node);
            return;
        } 

        temp = *head;
        while(i++ != position) {
            temp = temp->next;

            // Position exceeds the limit
            if(!temp) {
                free(node);
                return;
            }

        }

        // Iterated to the last
        if(temp == *tail) {
            insert_last(head, tail, &node);
            return;
        } else if(temp == *head) {
            insert_first(head, tail, &node);
            return;
        }

        // Reposition accordingly
        dll* old_prev = temp->prev;
        dll* old_node = temp;

        old_prev->next = node;
        node->prev = old_prev;

        temp->prev = node;
        node->next = temp;
    }
}

dll* Read(dll** head, dll **tail, int position, int pole)
{
    if(position == -1) {
        return *tail;
    } else if(position == 0) {
        return *head;
    }
    
    int i = 0;
    dll* temp = (pole) ? *head : *tail;

    // Search from tail just for fun
    while(i++ != position) {
        temp = (pole) ? temp->next : temp->prev;
        if(!temp) {
            return NULL;
        }
    }

    return temp;
}

void Update(dll** head, dll** tail, int position, int replacement)
{
    if(!BENCHMARKING)
        printf("Replace value at %d position with value %d\n", position, replacement);
    
    dll* to_replace = Read(head, tail, position, 1);
    if(to_replace) {
        to_replace->val = replacement;
    } else {
        if(!BENCHMARKING)
            printf("position %d doesn't exist\n", position);
    }
}

void Delete(dll** head, dll** tail, int position)
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

// Helper Functions
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
    
    if(BENCHMARKING) {
        double time_used = 0;
        
        clock_t start = clock();
        long num_of_ops = 1000000;

        for (int i = 0; i < num_of_ops; i++) {
            Create(&head, &tail, i, -1);
        }
        clock_t end = clock();

        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        double ops_per_sec = (double)num_of_ops / seconds;

        printf("Total time: %.8f sec\n", seconds);
        printf("Ops per second: %.2f\n", ops_per_sec);

        return 0;
    }
    
    // Indicing works like in arrays
    Create(&head, &tail, 3, 0);
    Create(&head, &tail, 1, 0);
    Create(&head, &tail, 4, -1);
    Create(&head, &tail, 77, 1);
    Create(&head, &tail, 78, 2);
    Create(&head, &tail, 79, 3);
    Create(&head, &tail, 76, 1);
    Create(&head, &tail, 80, 5);

    print_list(&head, &tail, 1);
    printf("____________________________________\n");

    int position, pole;
    dll* read_res;

    position = 4, pole = 1;
    read_res = Read(&head, &tail, position, pole);
    if(read_res) 
        printf("Pole: %d. At position %d, value is %d\n", pole, position, read_res->val);
    else printf("Couldn't read from %d position...\n", position);

    position = 5, pole = 0;
    read_res = Read(&head, &tail, position, 0);
    if(read_res) 
        printf("Pole: %d. At position %d, value is %d\n", pole, position, read_res->val);
    else printf("Couldn't read from %d position...\n", position);

    print_list(&head, &tail, 1);
    printf("____________________________________\n"); 

    Update(&head, &tail, 0, 75);
    Delete(&head, &tail, 7);
    Delete(&head, &tail, -1);
    Update(&head, &tail, 5, 81);


    print_list(&head, &tail, 1);
    printf("____________________________________\n"); 


}