#include <stdio.h>
#include <stdlib.h>

//Name: Emily Xu
//Introduction: This short program is meant print out the values for only one row in Pascal's Triangle. The row number is chosen by the user.
//The program is based on two for loop functions: one for loop is there to keep track of and progress where we are in the row. The other for loop computes the actual number
//at that location.

int main()
{
	 int row;

 	printf("Enter a row index: ");
	scanf("%d",&row);


  // Write your code here
  // row = n and final k value in (n k)
  

	unsigned long coefficient = 1;					//initialize coefficient to an unsigned long integer
	int k, i;							//declare variables for k ("where we are" in the row))
									//and for i (used in computation to get the right number)
	for (k=0; k <= row; k++)					//loop until we have (row+1) amount of terms in the row
	{
		if (k == 0)						//if k is 0, the answer will always be 1. Check if k is 0
		{
			printf("%lu ", coefficient);			//prints 1 if k = 0 (coefficient initialized as 1)
		}
		else							//if k is anything but 0, compute the correct number
		{			
			coefficient = 1;				//reset coefficient value to 1 for every new term we are computing
			for (i = 1; i <= k; i++)			//loop until i = k. This for loop will get the right number for our current location in the row	
			{	
				coefficient *= (row + 1 - i);		//calculates the "numerator" portion 
				coefficient /= i;			//divide by "denominator" portion in the end to avoid integer division truncating values
					 
			}
			printf("%lu ", coefficient);			//prints out term		
		}
	
	}
	printf("\n");							//for formatting
	return 0;							//end of program
}
