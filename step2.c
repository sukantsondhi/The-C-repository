#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define BLOCKSIZE 2

struct node
{
    struct node *next;
    int i;
    struct node *prev;
};

struct list
{
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    int length;
};

void printList(struct list *pList, int *counter)
{
    struct node *cur = pList->head;
    while (cur)
    {
        printf(" | %d | ", cur->i);
        cur = cur->next;
    }
    if (!(pList->head) || !(pList->tail) || *counter == 0)
        printf(" ||");
    printf("\ncounter = %d\n", *counter);
}

void deAllocator(void *p, int *counter)
{
    if (p != NULL)
    {
        free(p);
        (*counter)--;
    }
}

void *allocator(int size, int *counter)
{
    struct node *result = malloc(size);
    if (result != NULL)
    {
        (*counter)++;
    }
    return result;
}

void initialiseList(struct list *pList, int *counter)
{
    pList->head = malloc(sizeof(struct node));
    (*counter)++;
    pList->tail = malloc(sizeof(struct node));
    (*counter)++;
    pList->head->next = pList->tail;
    pList->tail->prev = pList->head;
    pList->head->prev = NULL;
    pList->tail->next = NULL;
    pList->head->i = 0;
    pList->tail->i = 0;
    pList->left = pList->head;
    pList->right = pList->tail;
    pList->length = 0;
}

void freeList(struct list *pList, int *counter)
{
    if (pList->left == pList->head && pList->right == pList->tail && pList->length == 0)
    {
        deAllocator(pList->head, counter);
        deAllocator(pList->tail, counter);
        pList->head = NULL;
        pList->left = NULL;
        pList->tail = NULL;
        pList->right = NULL;
        pList->length = -1;
    }
}

void allocateBlock(struct list *pList, int *counter, int nNodes)
{
    for (int i = 0; i < nNodes; i++)
    {
        struct node *object = (struct node *)allocator(sizeof(struct node), counter);
        object->prev = pList->left;
        object->next = pList->left->next;
        pList->left->next->prev = object;
        pList->left->next = object;
        object->i = -1;
        (pList->length)++;
    }
}

void deAllocateBlock(struct list *pList, int *counter, int nNodes)
{
    int n = (pList->length) - nNodes;
    while ((pList->length) > n)
    {
        struct node *temp = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = temp->next;
        deAllocator(temp, counter);
        (pList->length)--;
    }
}

int main()
{
    int counter = 0;
    struct list myList;
    initialiseList(&myList, &counter);
    printList(&myList, &counter);
    allocateBlock(&myList, &counter, BLOCKSIZE);
    printList(&myList, &counter);
    deAllocateBlock(&myList, &counter, BLOCKSIZE);
    printList(&myList, &counter);
    freeList(&myList, &counter);
    printList(&myList, &counter);
}
