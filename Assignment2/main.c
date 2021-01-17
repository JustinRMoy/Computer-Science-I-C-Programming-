/* COP 3502C Midterm Assignment TwoThis program is written by: Justin Moy 
It uses a doubly Linked-List*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int position;
    struct node* prev;
    struct node* next;
}soldier;

void insertAtEnd(soldier* head, soldier* n){

    head->prev->next = n;
    n->prev = head->prev;
    n->next = head;
    head->prev = n;

}

soldier* deleteCurrent(soldier* head, soldier* current){

    soldier* temp;
    if(head == current){
        temp = head;
        head->next->prev = head->prev;
        head->prev->next = head->next;
        head = head->next;
        free(temp);
        return head;
    }else if(current->next == head && current->prev == head){
        temp = current;
        head->next = NULL;
        head->prev = NULL;
        free(temp);
        return head;
    }else{
        temp = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(temp);
        return head;
    }

}

soldier* create_soldier (int sequence){

    soldier* ret = malloc(sizeof(soldier));
    ret->next = NULL;
    ret->position = sequence;
    ret->prev = NULL;
    return ret;

}

soldier* create_reverse_circle(int  n){

    soldier* head;
    soldier* t;
    for(int i = n; i>= 1; i--){
        if(i == n){
            head = create_soldier(i);
        }else if(i == n-1){
            t = create_soldier(i);
            t->next = head;
            head->prev = t;
            head->next = t;
            t->prev = head;
        }else{
            insertAtEnd(head, create_soldier(i));
        }
    }
    return head;
}

soldier* rearrange_circle(soldier*  head){

    soldier* t = head;
    soldier* temp;
    while(t->next != head){
        temp = t->next;
        t->next = t->prev;
        t->prev = temp;
        t = t->prev;
    }
    t->next = t->prev;
    t->prev = head;
    head = t;

    return head;
}

void  display(soldier*  head){

    soldier* t = head;
    while(t->next->position != head->position){
        printf("%d, ", t->position);
        t = t->next;
    }
    printf("%d\n", t->position);

}

int kill(soldier* head, int n, int k){

    soldier* t = head;
    printf("People executed: ");
    while(n != 1){
        for(int i = 0; i < k; i++){
            t = t->next;
        }
        printf("%d, ", t->prev->position);
        head = deleteCurrent(head, t->prev);
        n--;
    }
    printf("\n");
    return head->position;
}

int main()
{
    printf("How many people are there? ");
    int n;
    scanf("%d", &n);
    printf("Which kth person will be killed? ");
    int k;
    scanf("%d", &k);

    soldier* test = create_reverse_circle(n);
    display(test);
    test = rearrange_circle(test);
    display(test);
    printf("\nThe Survivor is at position: %d\n", kill(test, n, k));
    return 0;
}
