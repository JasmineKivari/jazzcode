/*
This program computes the height and velocity of a falling object, including
 * the effects of atmospheric drags.
 */

/* 
 * File:   main.c
 * Author: Jazz
 *
 * Created on January 23, 2018, 1:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*This program computes the height and velocity of a falling object, including
 * the effects of atmospheric drags.
 * 
 */
int main(void) {
    /* Declares physics variables*/

    const double gravity = 9.80667;
    double time = 0, velocity = 0;
    const double airDensity = 1.2754;
    
    double fDrag;
    double height;
    double timeStep;
    double dragCoeff;
    double cross;
    double fNet;
    double fGrav;
    double acceleration;
    double term_velocity;
    double mass;
   
    /* Ask for the height in meters*/
    printf("Enter the height in meters: ");
    scanf("%lf", &height);
    
    /* Ask for the mass in kilograms*/
    printf("Enter the mass in kg: ");
    scanf("%lf", &mass);
    
    /* Ask for the drag coefficient*/
    printf("Enter the drag coefficient: ");
    scanf("%lf", &dragCoeff);
    
    /* Asks for cross-sectional area*/
    printf("Enter the cross-sectional area: ");
    scanf("%lf", &cross);
    
    /* Asks for a time step*/
    printf("Enter the time step size: ");
    scanf("%lf", &timeStep);
    
    /* Does a quick printoff in specific format*/
    printf("   Time      ");
    printf("Height    ");
    printf("Velocity\n");
    /*iterates to the maximum iterations of 1 million and calculates force of
     * gravity, force of drag and accelaration */
    for (int max_iterations = 0; max_iterations <= 1000000; max_iterations ++) { 
        fDrag = -0.5 * dragCoeff * airDensity * cross* (velocity * velocity);
        
        fGrav = gravity * mass;
        
        fNet = fGrav + fDrag;
        
        acceleration = fNet / mass;
       /* Prints off time height and velocity outcomes*/
        //printf("    %.2lf",time );
        //printf("       %.1lf" ,height);
        //printf("        %.1lf\n", velocity);
        printf("%10.1lf %10.1lf %10.1lf\n", time, height, velocity);

        velocity = velocity + acceleration * timeStep;
        
        height = height - (timeStep * velocity);
        
        time = time + timeStep;
        /* height cannot be a negative number*/
        if (height < 0) {
            
            break;
        } 
      
    }
    /*Finds terminal velocity*/
    term_velocity = sqrt((2 * mass * gravity) / (airDensity * cross * dragCoeff));
    
    printf("Theoretical terminal velocity is %.1lf m/s", term_velocity);

    return (EXIT_SUCCESS);
}




    
    
   
    
