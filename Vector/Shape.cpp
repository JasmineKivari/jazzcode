#include "Shape.h"
// Print out the shape 
std::ostream & operator<<(std::ostream &out, Shape &shape) {
    shape.printMe(out);

    return out;
}