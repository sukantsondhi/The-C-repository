#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define BLOCKSIZE 2
#define maxInput 5 * BLOCKSIZE

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
        struct node *object = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = object->next;
        deAllocator(object, counter);
        (pList->length)--;
    }
}

void pushInt(struct list *pList, int *counter, int i)
{
    if (pList->length == 0)
    {
        allocateBlock(pList, counter, BLOCKSIZE);
    }
    if ((i % 2 == 0) && (pList->right->prev))
    {
        pList->right->prev->i = i;
        pList->right = pList->right->prev;
        (pList->length)--;
    }
    else if ((i % 2 == 1) && (pList->left->next))
    {
        pList->left->next->i = i;
        pList->left = pList->left->next;
        (pList->length)--;
    }
}

void pullInt(struct list *pList, int *counter, int i)
{
    if (i % 2 == 1)
    {
        if (pList->left != pList->head)
        {
            pList->left->i = -1;
            pList->left = pList->left->prev;
            (pList->length)++;
        }
    }
    else
    {
        if (pList->right != pList->tail)
        {
            pList->right->i = -1;
            pList->right = pList->right->next;
            (pList->length)++;
        }
    }

    if (pList->length > BLOCKSIZE)
    {
        deAllocateBlock(pList, counter, BLOCKSIZE);
    }
}

void clearList(struct list *pList, int *counter)
{
    while (pList->left != pList->head)
    {
        pullInt(pList, counter, 1);
    }

    while (pList->right != pList->tail)
    {
        pullInt(pList, counter, 2);
    }

    deAllocateBlock(pList, counter, pList->length);
    freeList(pList, counter);
}

int getInput(char *s)
{
    char c;
    int i;
    i = 0;

    while ((c = getchar()) != '\n' && i < maxInput)
    {

        if ((c - '0') <= 9 && (c - '0') >= 0)
        {
            s[i] = c;
            i++;
        }
    }
    if (i == maxInput)
    {
        while ((c = getchar()) != '\n')
        {
            getchar();
        }
    }
    return i;
}

int main()
{
    int counter = 0;
    struct list myList;
    initialiseList(&myList, &counter);
    printList(&myList, &counter);
    char sPush[maxInput];
    char sPull[maxInput - 1];
    int lenPush = getInput(sPush);
    int lenPull = getInput(sPull);
    int i = 0;
    int j = 0;
    while ((i + j) < (lenPush + lenPull))
    {
        if (i < lenPush)
        {
            pushInt(&myList, &counter, sPush[i]);
            printList(&myList, &counter);
            i++;
        }
        if (j < lenPull)
        {
            pullInt(&myList, &counter, sPull[j]);
            printList(&myList, &counter);
            j++;
        }
    }
    printList(&myList, &counter);
    clearList(&myList, &counter);
    printList(&myList, &counter);
}
