/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */

#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

int main() {
	
	int seed, one, two, three;

	printf("Enter a seed number: \n");
	scanf("%d", &seed);
	srand(seed);
	roll_three(&one, &two, &three);
	if (three == two && three == one)
	{
		printf("Triple!\n");
	}	
 	else if (three == two || three == one)
	{
		printf("Double!\n");
	}
	else
		printf("\n");

	
	return 0;
}
