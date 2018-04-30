
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/* Add an item to the rear of the dynamically-allocated queue.
 * Returns:  pointer to the item if successful, NULL if not */
ItemType *enqueue(Queue *queue, ItemType *item) {
    //Create thisNode and set the next pointer 
    // if pointer is null let standard error state it cannot allocate space
    ListNode *thisNode = (ListNode*) malloc(sizeof (ListNode));
    if (thisNode == NULL) {
        fprintf(stderr, "Failure: Cannot Allocate Space for Empty Node!");

        return NULL;
    }
    //Set up pointers and item node

    thisNode->item = item;

    thisNode-> next = NULL;
    // if the front of the queue is empty then update front and rear to thisNode
    if (queue -> front == NULL) {
        queue -> front = queue -> rear = thisNode;
    } else {
        //else the rear of the queue and the next pointer is updated to thisNode
        queue -> rear -> next = thisNode;
        queue -> rear = thisNode;
    }
    queue -> size++;
    return thisNode -> item;
}

/* Removes an item from the front of the queue.
 * Returns:  pointer to the item if successful, NULL if empty */
ItemType *dequeue(Queue *queue) {
    //Null if empty
    if (queue -> front == NULL) {
        return NULL;
    }
    // create another node pointer to the beginning of the queue
    ListNode *otherNode = (ListNode*) malloc(sizeof (ListNode));
    if (otherNode == NULL) {
        fprintf(stderr, "Failure: Cannot Allocate Space for Node!");
        return NULL;
    }
    otherNode = queue -> front;
    queue -> front = queue -> front -> next;
    queue -> size--;
    ItemType *otherItem = otherNode -> item;
    free(otherNode);

    return otherItem;

}

/* Returns:  number of items in the queue through the size of the queue */
int queueSize(const Queue queue) {
    return queue.size;
}

/*Print the contents of the queue to the specified stream
 *lets the user know if the queue is empty */
void printQueue(const Queue queue, FILE *stream) {
    if (queue.size == 0) {
        printf("\n Empty Queue.");
    } else {
        ListNode *otherNode = queue.front;
        while (otherNode -> next != NULL) {
            fprintf(stream, "\n%d", *(otherNode -> item));
            otherNode = otherNode -> next;
        }
        fprintf(stream, "\n%d\n", *(otherNode -> item));
    }
}

