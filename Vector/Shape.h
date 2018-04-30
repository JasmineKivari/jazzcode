/*
 * Base class for all Shapes.
 *
 * Shape is an abstract class because draw() is a pure virtual function
 *
 * File:   Shape.h
 * Author: dale
 *
 * Created on October 31, 2011, 2:02 PM
 */

#ifndef SHAPE_H
#define	SHAPE_H
#include <iostream>

class Shape {
private:
    int x;
    int y;
protected:
    /**
     * This function is supplied so that we can use polymorphism
     * with the stream insertion operator <<
     *
     * @param os The output stream
     */
    virtual void printMe(std::ostream& os) const = 0;
public:
    inline Shape (int xLoc, int yLoc) : x(xLoc), y(yLoc) {    }

    /**
     * Sets new values for the coordinates
     *
     * @param x New position
     * @param y New position
     */
    inline void moveTo (int x, int y) {
        this->x = x;  // Using this-> resolves the member x from the parameter x
        this->y = y;
    }

    /**
     *
     * @return The current x coordinate
     */
    inline const int getX() const {
        return x;
    }
    /**
     *
     * @return The current y coordinate
     */
    inline const int getY() const {
        return y;
    }

    /**
     * The shape draws itself
     *
     * Since this is a pure virtual function, it MUST be overridden
     * in any derived concrete class
     */
    virtual void draw() const = 0;


    /**
     * Overload the stream insertion operator so that we
     * can print a Shape in its entirety.
     * The implementation uses the virtual member function printMe()
     * so that polymorphism will work.
     */
    friend std::ostream& operator<< (std::ostream &out, Shape &rect);
};

#endif	/* SHAPE_H */
