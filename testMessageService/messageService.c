/*
 * Author: Jasmine Kivari
 * Student Number: C0303302
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messageService.h"
/* This is a program which goes through a circular index for message blocks*/
static LinkType blocksHead; //Circular queue which goes for the first block
static LinkType blocksTail; // Circular queue which goes to the last available block
static LinkType blocksFree[N_MESSAGE_BLOCKS]; // Number of blocks free

//Goes through each block and links them together, return -1 if there is no next 
//block.

//Initialized message blocks and declaration of blocks available.

static LinkType links[N_MESSAGE_BLOCKS];
static char messageBlocks[N_MESSAGE_BLOCKS][MESSAGE_BLOCK_SIZE];
static char messageBlocksInitialized = 0;
static int blocksAvailable;
// get block function which goes through to find blocks available and returns
// -1 if next block not available.
// also frees block and returns a block once block is free.

static LinkType getBlock() {
    if (blocksAvailable <= 0) {
        return -1;
    }
    LinkType block = blocksFree[blocksHead];
    blocksHead = (++blocksHead) & N_MESSAGE_BLOCKS_MASK;
    --blocksAvailable;
    return block;
}

// creates message and puts the messages into a new buffer
// Also bit shifts by the power of 2 for blocks needed

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
    // Prints off the amount of blocks needed and the first block
    DPRINT("Need %d. Using blocks: %d", blocksNeeded, firstBlock);
    // Go into a loop to copy data into each block and link the blocks
    int theLastBite = nBytes;

    for (int i = 1; i < blocksNeeded; i++) {
        memcpy(messageBlocks[thisBlock], myMessage, MESSAGE_BLOCK_SIZE);
        theLastBite -= MESSAGE_BLOCK_SIZE;
        myMessage += MESSAGE_BLOCK_SIZE;
        LinkType NectBlocko = getBlock();
        DPRINT(" %d ", NectBlocko);
        links[thisBlock] = NectBlocko;
        thisBlock = NectBlocko;
    }
    memcpy(messageBlocks[thisBlock], myMessage, theLastBite);
    links[thisBlock] = -1;
    DPRINT("\n");
    DPRINT("blocksHead: %d\n", blocksHead);
    return retVal;
}

void freeMessage(Message message) {
    // Free's blocks in message and also prints off the block tail.
    LinkType thisBlock = message.firstBlock;
    DPRINT("Freeing blocks: ");
    while (thisBlock != -1) {
        blocksTail = ++blocksTail & N_MESSAGE_BLOCKS_MASK;
        DPRINT(" %d", thisBlock);
        blocksFree[blocksTail] = thisBlock;
        ++blocksAvailable;
        thisBlock = links[thisBlock];

    }
    DPRINT("\nblockTail %d\n", blocksTail);
}

// initializes and prepares the message block into the buffer pool

void initializeMessageBlocks(void) {

    for (int k = 0; k < N_MESSAGE_BLOCKS; k++) {
        blocksFree[k] = k;
    }
    blocksHead = 0;
    blocksTail = N_MESSAGE_BLOCKS - 1;
    blocksAvailable = N_MESSAGE_BLOCKS;
    messageBlocksInitialized = 1;

}
// returns the amount of free blocks available

int numberOfFreeBuffers(void) {
    return blocksAvailable;
}
//Prints off the full message needed to the stream

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

