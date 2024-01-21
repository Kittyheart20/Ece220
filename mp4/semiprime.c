#include <stdlib.h>
#include <stdio.h>

/*Name: Emily Xu
 * partners: ufacio2, ehaynes2
 * Errors: There were 4 errors in this program.
 * The first one was located in is_prime: the return values should be swapped. Rather than returning 1 in the if statement,
 * we should be returning 0. This is because the for loop is checking to see if there are any values before our inputted number that are factors of our number. For example, if we input
 * 4, 2 would be considered a factor because 4%2 == 0. However, if we return 1 when this happens, that would indicate that we have a prime number. If we swap the order of
 * the return values, then we would return a 0 if the if loop detects that our number has other factors (denoting that it is not a prime number), correcting our error.
 * The second error is in print_semiprimes. The error was "k=i%j" and it was fixed by making the statement "k=i/j". This should be a division sign because after checking that j
 * is a prime number, we want to know if the other factor of "i" is a prime number too or not. To do that, we can isolate that number by dividing j out so we do not have to worry about it 
 * anymore. Then, we can check if the result is a prime number or not. We do not need the remainder(%) to compute that because if we have a semiprime number, that means it has factors
 * of prime numbers. If the first one (j) is prime, taking the remainder of it will always result in a 0. This will not allow the second is_prime to run at all. 
 * The third error happens after the print statement in print_semiprimes. There needs to be a break statement here because if there isn't one, some values will be repeatedly
 * printed out since semiprimes have factors. Therefore, we will accidentally print out certain semiprime numbers multiple time (For example, 6 will print out two
 * times: one for when j=2 and  when j=3). Hence, we should break out the for loop after printing out that number once.
 * The last error concerns the final return value. The program sets the return value as 0 in print_semiprimes, however it never actually updates when a semiprime is detected. 
 * Therefore, to fix this issue, we can add "ret = 1;" after the print statement because when we print a number, it will always print a semiprime. Updating ret afterwards ensures we have
 * a semiprime.
*/


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;  		//if there is a factor of our number before itself, then it is not a prime number
        }
    }
    return 1; //the number doesn't have any factors before itself
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			break;
                    }
                }
            }
        }
   }
    
    printf("\n");
    return ret;

}
