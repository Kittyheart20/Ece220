#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
	float n, omega1, omega2, x;
    // Prompt user for input
    	printf("This short program will compute the fuction sin(w1x) + 0.5sin(w2x). \n");
	printf("Pick the number of pairs, the first coefficient value and the second coefficient value. \n");
    // Get user input
	scanf("%f %f %f", &n, &omega1, &omega2);
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
	for (int i = 0; i < n; i++)
	{
		x = M_PI * i/n;
		printf("(%f,%f)\n", x, sin(omega1*x) + 0.5*sin(omega2*x));
	} 
    return 0;
}

