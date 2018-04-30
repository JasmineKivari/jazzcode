/*
 * A main() to demonstrate inheritance, polymorphism, virtual functions,
 * and an abstract class.
 * Uses classes: Shape, Rectangle, and Circle.
 * 
 * File:   main.cpp
 * Author: dale
 *
 * Created on November 7, 2011, 2:27 PM
 */

#include <cstdlib>
#include "Rectangle.h"
#include "Circle.h"
#include "ShapeStack.h"
#include "Square.h"
using namespace std;

int main(int argc, char* argv[]) {
    Circle c1(20.5, 4, 10);
    Rectangle r1(10, 20.7, 8, 8);
    Circle c2(11, 10, 5);
    Square s1(5 ,5 ,5 );
    //Creating a new shapestack
    ShapeStack shape = ShapeStack();
    //Do a stack exception if there is nothing on the top of the stack
    try {
    shape.top();
    }
    catch (StackException& e) {
        cout << e.getMessage() << "\n";
    }
    try {
        shape.pop();
    }
    //Do a stack exception if there is nothing to remove from the stack
    catch (StackException& e) {
        cout << e.getMessage() << "\n";
    }
    // Different pop and push functions
    //Drawing the shapes
    shape.push(&c1);
    shape.top()->draw();
    shape.push(&r1);
    shape.push(&c2);
    shape.push(&s1);
    cout << "Count: "<< shape.size() <<  "\n";
    
    //Draw each shape as popped off the stack
    while (shape.size() > 0) {
        shape.pop()->draw();
    }
    
    return EXIT_SUCCESS;
}
