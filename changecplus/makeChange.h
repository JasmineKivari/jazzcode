/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   makeChange.h
 * Author: Jazz
 *
 * Created on March 6, 2018, 2:03 PM
 */
// sets up the structs for the program.
#ifndef MAKECHANGE_H
#define MAKECHANGE_H

#include <cstring>
using namespace std;

typedef struct {
    double value;
    string name;
    string pluralName;
} Currency;

typedef struct ChangeValue{
    int amount;
    double revisedBalance;
    
}ChangeVaue;




#endif /* MAKECHANGE_H */

