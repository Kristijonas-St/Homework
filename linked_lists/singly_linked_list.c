#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BENCHMARKING 0

typedef struct ll {
    int val;
    struct ll *next;
} ll;

void Create(ll**, int, int);
ll* Read(ll**, int);
void Update(ll**, int, int);
void Delete(ll**, int);

void Create(ll** head, int position, int value)
{
    ll* new_node = (ll*)malloc(sizeof(ll));
    if(head == NULL) {
        new_node->val = value;
        new_node->next = NULL;
        *head = new_node;
        return;
    }

    if(!position) {
        new_node->val = value;
        new_node->next = *head;
        *head = new_node;
        return;
    }

    int i = 0;
    ll* ite = *head;
    while(i++ != position - 1) {        
        ite = ite->next;
        if(!ite) { 
            free(new_node);
            new_node = NULL;
            if(!BENCHMARKING)
                printf("Position %d is out of bounds, returning...\n", position);
            return;
        }
    }

    // Insert Last
    if(ite->next == NULL) {
        new_node->val = value;
        ite->next = new_node;
        new_node->next = NULL;
        return;
    }

    // Insert other position
    new_node->val = value;
    new_node->next = ite->next;
    ite->next = new_node;
}

ll* Read(ll** head, int position)
{
    if(*head == NULL) {
        if(!BENCHMARKING)        
            printf("Cannot iterate through empty list, returning NULL...\n");
        return NULL;
    }

    ll* ite = *head;
    int i = 0;
    while(i++ < position) {
        ite = ite->next;
        if(!ite) {
            return NULL;
        }
    }
    return ite;

}

void Update(ll** head, int position, int value) {
    if(*head == NULL) {
        printf("Cannot update an empty list, returning...\n");
        return;
    }
    
    ll* to_update = Read(head, position);

    if(to_update) {
        to_update->val = value;
        return;
    }

    printf("Pos %d invalid\n", position);
}

void Delete(ll** head, int position) {
    if(*head == NULL) {
        if(!BENCHMARKING)
            printf("Cannot delete an empty list, returning...\n");
        return;
    }

    // Delete First
    if(!position) {
        ll* old_head = *head;
        ll* new_head = (*head)->next;

        free(old_head);
        old_head = NULL;

        *head = new_head;
        return;
    }

    ll* ite = *head;
    int i = 0;
    while(i++ != position - 1) {
        ite = ite->next;
        if(!ite) {
            if(!BENCHMARKING)
                printf("Position %d is out of bounds, returning...\n", position);
            return;
        }
    }

    // Delete Last
    if(ite->next == NULL) {
        ll* last = Read(head, position - 2);
        last->next = NULL;
        free(ite);
        ite = NULL;
        return;
    }

    // Delete other position
    ll* temp1 = ite->next;
    ll* temp2 = temp1->next;

    ite->next = temp2;
    free(temp1);
    temp1 = NULL;
}

void print_list(ll* head)
{
    ll* ite = head;
    while(ite) {
        printf("%d", ite->val);
        if(ite->next != NULL) {
            printf(" -> ");
        }
        ite = ite->next;
    }
    printf("\n");
}

int main(void)
{
    ll *head = NULL;

    if(BENCHMARKING) {
        double time_used = 0;
        
        clock_t start = clock();
        long num_of_ops = 1000000;
        
        for (int i = 0; i < num_of_ops; i++) {
            Create(&head, 0, i);
        }
        clock_t end = clock();

        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        double ops_per_sec = (double)num_of_ops / seconds;

        printf("Total time: %.8f sec\n", seconds);
        printf("Ops per second: %.2f\n", ops_per_sec);

        return 0;   
    }

    ll* to_read = NULL;
    int position;

    Create(&head, 0, 45);
    Create(&head, 0, 18);
    Create(&head, 0, 26);
    Create(&head, 3, 72);
    Create(&head, 1, 72);
    Create(&head, 2, 77);
    Create(&head, 2, 100);

    print_list(head);
    
    position = 4;
    to_read = Read(&head, position);
    if(to_read)
        printf("Pos %d: %d\n", position, to_read->val);
    else 
        printf("Read for pos %d FAILED\n", position);

    Update(&head, 1, 27);
    Update(&head, 2, 101);
    print_list(head);

    Delete(&head, 7);
    print_list(head);

    Delete(&head, 1);
    print_list(head);

    Delete(&head, 2);
    print_list(head);  

}