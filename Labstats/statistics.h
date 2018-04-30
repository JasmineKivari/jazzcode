/*
* This is the header file that takes the mean and standard deviation and prints
 * out the information.
 */

/* 
 * File:   statistics.h
 * Author: Jazz
 *
 * Created on February 3, 2018, 5:01 PM
 */

#ifndef STATISTICS_HEADER
#define STATISTICS_HEADER

#include <stdio.h>

double mean(const double sum, const int count);
double ssdev(const double sum, const double sumsq, const int count);
void printStats (FILE *dest, const int count, const double mean, const double ssdev);



#endif /* STATISTICS_HEADER*/

