/*
 *This program reads and writes ascii files that uses commands line arguments.
 */

/* 
 * File:   main.c
 * Author: Jazz
 *
 * Created on January 30, 2018, 1:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"
#include <string.h>

/*
 * This program reads and writes ascii files that uses commands line arguments.
 * opens read and writes to files and console.
 */
int main(int argc, char** argv) {
    // declaration of variables.
    FILE *inputFile;
    FILE *outputFile;
    double avg;
    double standardDev;
    double s;
    int count = 0;
    double sumsq = 0;
    double sum = 0;
    char *fileName;
    char *firstFile = argv[1];

    //checks to see if there are less than 2 command line arguments, throw
    //an error.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fileName\n", argv [0]);
        return (EXIT_FAILURE);
    }
    //Open file and read
    inputFile = fopen(argv [1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Unable to open input file \"%s\"", argv[1]);
        return EXIT_FAILURE;
    }
    // read and update variables into the file. Throw a error if less than 2 
    // values were read.
    while (fscanf(inputFile, "%lf", &s) == 1) {
        count = count + 1;
        sum = sum + s;
        sumsq = sumsq + (s * s);
    }
    if (count < 2) {
        printf("%s\n", "Failure: Less than two values read, need more than 2!");
        return (EXIT_FAILURE);
    }
    //calculate the mean and standard deviation
    avg = mean(sum, count);
    standardDev = ssdev(sum, sumsq, count);    
    printStats(stdout, count, avg, standardDev);


    //created the results to file.
    char *answer = "Result_";
    int len = strlen(answer) + strlen(firstFile);
    fileName = malloc (len+1);
    strncpy(fileName, answer, len);
    strncat(fileName, firstFile, len-strlen(answer));

    //open and write to a file and throws error if file was not successfully opened.
    outputFile = fopen(fileName, "w");
    if (outputFile == NULL) {
        printf("Unable to open output file \"%s\"", outputFile);
        return (EXIT_FAILURE);
    }
    printStats(outputFile, count, avg, standardDev);
    // close the files.
    fclose(inputFile);
    fclose(outputFile);
    return (EXIT_SUCCESS);
}
// print outcome to console and file.

void printStats(FILE *dest, const int count, const double mean, const double ssdev) {
    fprintf(dest, "%d Values, Mean = %.5lf, Sample Standard Deviation = %.5lf", count, mean, ssdev);
}








