/*
 * A Circle that is derived from Shape
 *
 * File:   Circle.h
 * Author: dale
 *
 * Created on October 31, 2011, 2:05 PM
 */

#ifndef CIRCLE_H
#define	CIRCLE_H
#include "Shape.h"
#include <iostream>

class Circle : public Shape {
private:
    double radius;
protected:
    void printMe(std::ostream& os) const;
public:

    /**
     * This constructor passes the x,y location to the base class constructor
     * in Shape and also initializes the Circle's radius.
     * 
     * We choose to make this an inline function.
     *
     * @param r Radius
     * @param xLoc Initial x coordinate
     * @param yLoc Initial y coordinate
     */
    inline Circle(double r, int xLoc, int yLoc)
        : Shape(xLoc, yLoc), radius(r) {
    }

    inline double getRadius(void) const {
        return radius;
    }


    /**
     * The Circle "draws" itself at its current location
     */
    void draw() const;
};


#endif	/* CIRCLE_H */
