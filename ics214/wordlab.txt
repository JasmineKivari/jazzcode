/* 
 * File:   main.c
 * Author: C0374314
 *
 * Created on February 20, 2018, 1:05 PM
 */

#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include "messageService.h"
// Allocate the array of blocks
static LinkType blocksHead; // Circular queue index for first available block
static LinkType blocksTail; // Circular queue index for last available block
static LinkType blocksFree[N_MESSAGE_BLOCKS]; // Free list is a circular queue
static int blocksAvailable; // Current number of free blocks

// For each block, the link to the next block (-1 indicates no next block)
static LinkType links[N_MESSAGE_BLOCKS];
static char messageBlocksInitialized = 0;
static char messageBlocks[N_MESSAGE_BLOCKS][MESSAGE_BLOCK_SIZE];

/*
 * Get one free Message Block
 *
 * @return Block index if successful. -1 otherwise.
 */
static LinkType getBlock() {
    if (blocksAvailable <= 0) {
        return -1;
    }
    LinkType block = blocksFree[blocksHead];
    blocksHead = (++blocksHead) & N_MESSAGE_BLOCKS_MASK;
    --blocksAvailable;
    return block;
}

/**
 * Copies a message from an array of chars (bytes) into a newly-allocated
 * set of buffers.
 *
 * @param myMessage A pointer to the first byte of data to be copied
 * @param nBytes The number of bytes to be copied
 *
 * @return A struct containing the Message
 */

Message createMessage(const char *myMessage, const int nBytes) {
    if (!messageBlocksInitialized) {
        initializeMessageBlocks();
    }

    Message retVal;
    retVal.nBytes = nBytes;

    // Division by a power of 2 is simply a shift
    int blocksNeeded = nBytes >> (MESSAGE_BLOCK_BITS);
    // Need one more if there is a remainder
    if (nBytes & MESSAGE_BLOCK_MASK) {
        ++blocksNeeded;
    }

    if (blocksNeeded > blocksAvailable) {
        retVal.nBytes = -1; // Mark as invalid Message
        return retVal;
    }

    LinkType firstBlock = getBlock();
    LinkType thisBlock = firstBlock;

    retVal.firstBlock = firstBlock;

    DPRINT("Need %d. Using blocks: %d ", blocksNeeded, firstBlock);

    // Go into a loop to copy data into each block and link the blocks
    int bytesLeft = nBytes;

    for (int i = 1; i < blocksNeeded; i++) {
        memcpy(messageBlocks[thisBlock], myMessage, MESSAGE_BLOCK_SIZE);
        bytesLeft -= MESSAGE_BLOCK_SIZE;
        myMessage += MESSAGE_BLOCK_SIZE;
        LinkType nextBlock = getBlock();
        DPRINT("%d ", nextBlock);
        links[thisBlock] = nextBlock;
        thisBlock = nextBlock;
    }
    memcpy(messageBlocks[thisBlock], myMessage, bytesLeft);
    links[thisBlock] = -1;
    DPRINT("\n");

    return retVal;
}

/**
 * Returns all buffers used by a Message to the buffer pool.
 *
 * @param The Message to be freed
 */
void freeMessage(Message message) {
    
    LinkType thisBlock = message.firstBlock;
    while (thisBlock != -1) {
        blocksTail = ++blocksTail & N_MESSAGE_BLOCKS_MASK;
        DPRINT ("Freeing block %d.  blocksTail=%d\n", thisBlock, blocksTail);
        blocksFree[blocksTail] = thisBlock;
        ++blocksAvailable;
        thisBlock = links[thisBlock];
    }
}

/**
 * Initializes the entire set of data structures for the buffer pool system.
 */
void initializeMessageBlocks(void) {
    for (int k = 0; k < N_MESSAGE_BLOCKS; k++) {
        blocksFree[k] = k;
    }
    blocksHead = 0;
    blocksTail = N_MESSAGE_BLOCKS - 1;
    blocksAvailable = N_MESSAGE_BLOCKS;
    messageBlocksInitialized = 1;
}

/**
 * Returns the number of buffers that are available in the pool.
 * A convenience function that is not needed for using the Message Service.
 *
 * @return The number of free buffers
 */
int numberOfFreeBuffers(void) {
    return blocksAvailable;
}

/**
 * Prints the bytes contained in the Message as a character string to stdout.
 *
 * @param message The Message to be printed
 */
void printMessage(FILE *stream, const Message message) {
    LinkType thisBlock = message.firstBlock;
    int nBytes = message.nBytes;
    while (thisBlock >= 0) {
        int n = (nBytes >= MESSAGE_BLOCK_SIZE) ? MESSAGE_BLOCK_SIZE : nBytes;
        fwrite(messageBlocks[thisBlock], 1, n, stream);
        nBytes -= n;  
        thisBlock = links[thisBlock];            
    }
}