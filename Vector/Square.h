/*
 * A Rectangle that is derived from Shape
 *
 * File:   Square.h
 * Author: dale
 *
 * Created on October 31, 2011, 2:10 PM
 */

#ifndef SQUARE_H
#define	SQUARE_H
#include "Rectangle.h"
#include <iostream>

class Square : public Rectangle {
private:
    
protected:
    void printMe(std::ostream& os) const;
public:
    /**
     * This constructor passes the x,y location to the base class constructor
     * in Shape and also initializes the Square's size.
     *
     * We choose to make this an inline function.
     *
     * @param l Length
     * @param l Width
     * @param xLoc Initial x coordinate
     * @param yLoc Initial y coordinate
     */
    inline Square(double side,int x, int y)
        : Rectangle(side,side, x, y) {
    }
    
    /**
     * The Square "draws" itself at its current location
     */
    void draw() const;
};


#endif	/* SQUARE_H */