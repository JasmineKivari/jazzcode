/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ShapeStack.h"
#include "StackException.h"

   void ShapeStack :: push(Shape *shape){
        
        StackNode *newNode = new StackNode;
        
        newNode->next = topItem;
        newNode->theShape = shape;
        topItem = newNode;
        count++;
    }
   
   Shape* ShapeStack :: pop(void) throw (StackException){
        StackNode *tempNode = new StackNode;
        if(topItem == NULL){
            throw StackException("Nothing to remove from stack\n");
        }
        tempNode = topItem;
        Shape *shape = tempNode->theShape;
        topItem = tempNode->next;
        delete(tempNode);
        count--;
        return shape;
        
    }
    Shape* ShapeStack :: top(void) throw (StackException){
         
        if(topItem == NULL) {
            throw StackException("Nothing on the top of the stack");
        }
        return topItem->theShape;
         
        
    }
    // return the count size


