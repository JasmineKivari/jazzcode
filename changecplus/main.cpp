/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jazz
 *
 * Created on March 6, 2018, 9:19 AM
 */
//This programs prompts user for total purchase price.
 //* The program then prompts for the amount tendered.
 //* The program then shows the total amount due.
 //* Lastly this program computes and displays the number 
 // and types of bills and coins in change.
#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include "makeChange.h"
#include "NegativeValueException.h"
#include <cmath>
using namespace std;

#define N_CURR 8

double getMoneyValue(string prompt) throw(NegativeValueException);
ChangeValue makeChange (double balance, double denominationValue);
// declare an array to store the denominations of the currency returned.
 static const Currency monies[N_CURR] = {
        {20.00," Twenty"," Twenties"},
        {10.00," Ten"," Tens"},
        {5.00," Five"," Fives"},
        {2.00, " Toonie"," Toonies"},
        {1.00," Loonie","Loonies"},
        {0.25," Quarter"," Quarters"},
        {0.10," Dime"," Dimes"},
        {0.05," Nickel"," Nickels"},
       
    };
int main(void) {
    // gives the change due and prompts the user to enter the amount of the purchase
    // and the amount tendered, will let user know that there was not enough money.
    //This also round the change due to the nearest nickel.
    double price, tendered, changeDue;
    
    string totalAmount = "Enter the amount of the purchase: $";
    string tenderedAmount = "Enter the amount tendered: $";
    
    bool isEverythingok = false;
    
    while (isEverythingok == false){
        try {
            price = getMoneyValue(totalAmount);
            
            
        } catch(NegativeValueException &e) {
           cerr << e.what();
            continue;
        }
        try {
            tendered = getMoneyValue(tenderedAmount);
        } catch(NegativeValueException &e){
            cerr << e.what();
            continue;
        }
        //lets user know that there was not enough money
        if(price > tendered ){
            cout << "Not enough money tendered try again" << endl;
            continue;
        }
        isEverythingok = true;
    } 
    //prints out the change due and the change rounded to the nearest nickel.
    changeDue = tendered - price;
    cout << "Change Due is: " << "$" << changeDue << endl;
    changeDue = round(changeDue * 20) / 20;
    cout << "Change due rounded to the nearest nickel: " << setprecision(2) << fixed << "$" << changeDue << endl;
    
    
    for( int i = 0; i < N_CURR; i ++){
        
        double denomination = monies[i].value;
        ChangeValue valueOf = makeChange(changeDue,denomination);
        if(valueOf.amount == 1){
            cout << valueOf.amount << monies[i].name << endl;
            changeDue = valueOf.revisedBalance;
            
            
        }else if (valueOf.amount > 1){
            cout << valueOf.amount << monies[i].pluralName << endl;
            changeDue = valueOf.revisedBalance;
        }
    }
       
}
 // does the calculation for monetary denominations
    ChangeValue makeChange (double balance, double denominationValue){
        ChangeValue newAmount;
        double moneyValue = balance;
        double dnom = denominationValue;
        int numOfChangeItems;
        
        if (denominationValue <= balance) {
            numOfChangeItems = balance / denominationValue;
            moneyValue = moneyValue - numOfChangeItems * denominationValue;
            newAmount.revisedBalance = moneyValue;
            newAmount.amount = numOfChangeItems;
            return newAmount;
        }
        newAmount.revisedBalance = balance;
        newAmount.amount = 0;
        return newAmount;
    }

// throws the negative value exception that is in the header.
double getMoneyValue(string prompt) throw(NegativeValueException){
        double money;
        cout << prompt;
        cin >> money; 
        if (money <= 0 ){
            throw NegativeValueException();
        }  
        return money;
}


