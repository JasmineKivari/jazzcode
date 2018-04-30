/*
 * A linked implementation of a stack that can be used to store Shape objects
 *
 * File:   Stack.h
 * Author: dale
 *
 * Created on November 14, 2011, 5:54 PM
 */

#ifndef SHAPESTACK_H
#define	SHAPESTACK_H

#include <cstdlib>
#include "Shape.h"
#include "StackException.h"

class ShapeStack {
private:
    // The node that will be used for the Stack
    typedef struct stackNode {
        struct stackNode *next;
        Shape *theShape;
    } StackNode;

    /** A pointer to the StackNode at the top of the stack */
    StackNode *topItem;
    /** The number of Shapes currently on the stack */
    int count;
public:
    /** Constructor initializes the data members */
    inline ShapeStack () : topItem(NULL), count(0) {
    }
// Pushes to the stack
    void push (Shape *shape);

// Removes from the stack
    Shape* pop(void) throw (StackException);
     
    Shape* top(void) throw (StackException);

    // return the count size
    inline int size(void) {
        return count;
    }
// 
    inline bool isEmpty(void) {
        return count == 0;
    }
};


#endif	/* STACK_H */

