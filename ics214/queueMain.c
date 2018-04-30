#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int ac, char *av[]) {

    // Initialize Queue structure with Front, Rear, and Size of List
    Queue queue = {NULL, NULL, 0};

    // 
    int done = 0;
    while (!done) {
        int choice, nValid;
        do {
            printf("Enter 1 to add to queue or 0 to remove "
                    "(-1 to quit): ");
            nValid = scanf("%d", &choice);
        }
	while (nValid != 1 || choice < -1 || choice > 1);

        switch (choice) {
            case 0: {
                ItemType *item;
                if ((item = dequeue(&queue)) != NULL) {

		    // *item is a dereferenced pointer that forwards memory address of item to item
                    printf("Removed " ITEM_FORMAT "\n", *item);
		    // Memory address of item, which is just the current value of item as an int in memory and this frees up the space			
		    free (item);
                } 
                else {
                    printf("Queue is empty\n");
                }
                break;
            } // End case 0

            case 1: {

		// Make item memory space for item
                ItemType *item = malloc (sizeof(ItemType));
                if (item == NULL) {
                    fprintf(stderr, "%s: Error allocating memory for item.\n", av[0]);
                    return EXIT_FAILURE;
                }

                printf ("Enter " ITEM_PROMPT ": ");
                if (scanf(ITEM_FORMAT, item) != 1) {
                    fprintf(stderr, "Unable to read " ITEM_PROMPT "\n");
                    break;
                }

                if ((item = enqueue(&queue, item)) != NULL) {
                    printf("Added " ITEM_FORMAT "\n", *item);
                } 
                else {
                    fprintf(stderr, "%s: Error allocating memory to queue.\n", av[0]);
                    return EXIT_FAILURE;
                }
                break;
            } // End case 1

            case -1: {
                done = 1;
                break;
            } // End case -1

            default:
		fprintf(stderr, "Invalid choice entered");
        }
    }

    printf ("Items remaining in the queue:\n");
    printQueue (queue, stdout);


    return EXIT_SUCCESS;
}
