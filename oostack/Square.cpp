#include "Square.h"

// The draw() function.
void Square::draw() const {
    std::cout << "Square of size: [" << getWidth() << "] drawn at " << getX() << " " << getY() << std::endl;
}

//To print out the size of the square
void Square::printMe(std::ostream& os) const {
    os << "Square of size: [" << getWidth() << "] at " << getX() << " " << getY();
}
