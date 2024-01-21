#include "prime.h"

int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
	int o;
	for (o = 2; o < n; o++)
	{
		if (n%o == 0)
		{
			return 0;
		}
	}
	return 1;
}

