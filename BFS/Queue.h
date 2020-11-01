#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 99
#define MAX_NODE 3999999
#define MAX_DISTANCE 9999

typedef struct _node {
    int id,vertice_num,hospital;
    struct _node* vertice[MAX_VERTEX];
} Node;

typedef struct _listnode{
   Node* item;
   struct _listnode *next;
   struct _listnode *prev;
} ListNode;

typedef struct _queue{
   int size;
   ListNode *head;
   ListNode *tail;
} Queue;

void enqueue(Queue *q, Node* item);
Node* dequeue(Queue *q);
int isEmptyQueue(Queue *q);
#endif // QUEUE_H
