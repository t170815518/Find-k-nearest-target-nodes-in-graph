#include "Queue.h"

void enqueue(Queue *q, Node* item){
    ListNode *temp = malloc(sizeof(ListNode));
    temp->item = item;
    temp->prev = NULL;

    if(q->head == NULL){
       //enqueue empty queue
        q->size = 1;
        q->head = temp;
        q->tail = temp;
        temp->next = NULL;

    }
    else{
        temp->next = q->head;
        q->head->prev = temp;
        q->head = temp;
        q->size++;
    }
}

Node* dequeue(Queue *q){
    Node* item;
    if(q->tail == NULL){
        return NULL;
    }
    item = q->tail->item;

    ListNode *temp = q->tail;
    q->tail = q->tail->prev;
    if(q->tail != NULL){
        q->tail->next = NULL;
    }
    else{
        q->head = NULL;
    }

    free(temp);
    q->size--;
    return item;
}

int isEmptyQueue(Queue *q){
   if (q->size == 0)
      return 1;
   return 0;
}
