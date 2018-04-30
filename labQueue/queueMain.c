
/* 
 * File:   main.c
 * Author: Jazz
 *
 * Created on February 6, 2018, 1:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Main to test the queue and present a menu.
 * 
 */
int main(int ac, char *av[]) {
    //Create a queue structure with the size, front and last.
    Queue queue = {NULL, NULL, 0};
    // initialize a menu with choices.
    // prompt user to enter 1 to add or 0 to remove from queue.
    int done = 0;
    while (!done) {
        int choice, nValid;
        do {
            printf("Enter 1 to add to queue or 0 to remove "
                    "(-1 to quit): ");
            nValid = scanf("%d", &choice);

            if (nValid == 0) {while (getchar() !="\n"){}
            }
            } while (nValid != 1 || choice < -1 || choice > 1);
        // choice for remove of item in the queue and lets user know of the
        //removed item
        switch (choice) {
            case 0:
            {
                ItemType *item;
                if ((item = dequeue(&queue)) != NULL) {
                    printf("Removed " ITEM_FORMAT "\n", *item);
		    free (item);
                } else {
                    printf("Queue is empty\n");
                }
                break;
            }
            // let's the user know there was an error in finding memory space 
            // for the item.
            case 1:
            {
                ItemType *item = malloc (sizeof(ItemType));
                if (item == NULL) {
                    fprintf(stderr, "%s: Error allocating memory for item.\n", av[0]);
                    return EXIT_FAILURE;
                }
                // if choice is not equal to 1 then have unable to read error.
                printf ("Enter " ITEM_PROMPT ": ");
                if (scanf(ITEM_FORMAT, item) != 1) {
                    fprintf(stderr, "Unable to read " ITEM_PROMPT "\n");
                    break;
                }

                if ((item = enqueue(&queue, item)) != NULL) {
                    printf("Added " ITEM_FORMAT "\n", *item);
                } else {
                    fprintf(stderr, "%s: Error allocating memory to queue.\n", av[0]);
                    return EXIT_FAILURE;
                }
                break;
            }

            case -1:
            {
                done = 1;
                break;
            }
            // print off error if an invalid choice is entered.
            default:
                    fprintf(stderr, "Invalid choice entered");
                    
                   
        }
    }
    // let's the user know how many items are remaining in the queue and print it off
    printf ("Items remaining in the queue:\n");
    printQueue (queue, stdout);


    return EXIT_SUCCESS;
}

