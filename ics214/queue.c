#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Add an item to the rear of the dynamically-allocated queue.
 * Returns:  pointer to the item if successful, NULL if not */
ItemType *enqueue (Queue *queue, ItemType *item) {
	
    // Create a new node and set new node's next pointer to null
    ListNode *newNode = malloc(sizeof(ListNode));
    
    if (newNode == NULL) {
        fprintf(stderr, "Unable to allocate memory for null node.");
        return NULL;
    }

    // Update new node's item and next pointers
    newNode->item = item;
    newNode->next = NULL;

    // If Queue is empty, update Queue's front and rear pointers to new node
    if (queue->front == NULL) {
        queue->front = queue->rear = newNode;
        queue->size++;
        return newNode->item;
    }
    else {
        // Otherwise, Queue's rear pointer & List Node's next pointer = new node
        queue->rear->next = newNode;
        queue->rear = newNode;
        queue->size++;
        return newNode->item;
    }
}

/* Removes an item from the front of the queue.
 * Returns:  pointer to the item if successful, NULL if empty */
ItemType *dequeue (Queue *queue) {
	
    // If Queue is empty, display to user
    if (queue->front == NULL) {
        fprintf(stderr, "\nQueue is empty.\n");
        return NULL;
    }
    else {
        // Otherwise, create a temporary node pointer to front of Queue
        ListNode *tempNode = malloc(sizeof(ListNode));
        
        if (tempNode == NULL) {
            fprintf(stderr, "Unable to allocate memory for temp node.");
            return NULL;
        }
        tempNode = queue->front;
        queue->front = queue->front->next;
        queue->size--;
        ItemType *tempItem = tempNode->item;
        free(tempNode);
        return tempItem;
      
    }
}

/* Returns:  number of items in the queue */
int queueSize (const Queue queue) {
    
    // Get size of queue
    return queue.size;
}

/* Print the contents of the queue to the specified stream */
void printQueue (const Queue queue, FILE *stream) {
    
    // If Queue is empty, display to user
    if (queue.front == NULL) {
        printf("\nThe Queue is empty.");
    }
    else {
        ListNode *tempNode = queue.front;
        while (tempNode->next != NULL) {
            fprintf(stream, "\n%d", *(tempNode->item));
            *tempNode = *tempNode->next;
        }
        fprintf(stream, "\n%d\n", *(tempNode->item));
    }
}