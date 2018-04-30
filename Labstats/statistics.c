/*
 *Statistic calculation for the mean and the standard deviation.
 */
#include <math.h>
#include "statistics.h"


// returns calculation for mean
double mean(const double sum, const int count){
  
    return sum / count;
}
//return standard deviation
double ssdev(const double sum, const double sumsq, const int count){
    double ssdev;
    ssdev = sqrt(((count * sumsq) - (sum * sum)) / (count * (count - 1)));
    return ssdev;
}

