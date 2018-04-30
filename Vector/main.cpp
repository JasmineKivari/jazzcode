/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jazz
 *
 * Created on March 13, 2018, 1:29 PM
 */

#include <cstdlib>
#include <vector>
//#include <iostream>
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "StackException.h"
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {

    Circle c1(20.5, 4, 10);
    Rectangle r1(10, 20.7, 8, 8);
    Circle c2(11, 10, 5);
    Square s1(5, 5, 5);

    vector <Shape*> vectShape;


    cout << "The size is : " << (vectShape.size()) << "\n";
    vectShape.push_back(&c1);
    vectShape.push_back(&r1);
    vectShape.push_back(&s1);
    cout << "Capacity : " << (vectShape.capacity()) << "\n";

    cout << "The maximum size is: " << vectShape.max_size() << "\n";
    cout << "This is the front shape: " << *(vectShape.front()) << "\n";
    cout << "This is the back shape: " << *(vectShape.back()) << "\n";

    vectShape.insert(vectShape.begin(), &c2);

    cout << "The new first item is : " << *(vectShape[0]) << "\n";

    vectShape.pop_back();

    cout << "The new back item is : " << *(vectShape.back()) << "\n";

    cout << "This is the shape at position 3 : " << *(vectShape.at(2)) << "\n";

    vector <Shape*> ::iterator loopStart = vectShape.begin();
    vector <Shape*> ::iterator loopEnd = vectShape.end();

    for (loopStart; loopStart != loopEnd; loopStart++) {
        cout << **loopStart << "\n";
    }
    try {
        vectShape.at(-2);
    } catch (out_of_range& error) {
        cout << error.what() << "\n";
    }
    return EXIT_SUCCESS;
}


