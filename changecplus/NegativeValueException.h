/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NegativeValueException.h
 * Author: Jazz
 *
 * Created on March 6, 2018, 1:55 PM
 * This is called when a negative money amount is used on the prompt.
 */
#include <exception>
using namespace std;
class NegativeValueException : public exception {
public:
    const char* what() const throw(){
    return " Negative values are not allowed\n";
}
};


