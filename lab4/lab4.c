#include <stdio.h>
#include "prime.h"

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
	int number, i;
	printf("Please enter a number.\n");
	scanf("%d", &number);
	printf("Printing prime numbers less than or equal to: %d \n", number);
	for (i = 2; i <= number; i++)
	{
		if (is_prime(i))
		{
			printf("%d ",i);
		}
	}
	printf("\n");
	return 0;
}

