//
//print all the prime numbers less than or equal to the number given.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void prime(int num)
{
	int curr, div;
	int i;

	if (num<0)
	{
		printf(".\n");
		return;
	}

	curr = 2;
	while(curr <= num)
	{
		div = curr/2;
		for (i=2; i<=div; i++)
		{
			if (curr%i == 0 && curr != i)
				break;
		}
		if (i>div)
		{
			printf("%d	", curr);
		}
		curr++;
	}
	printf ("\n");
}

//A rule in mathematics: If any number has no number that evenly multiplies into it, which is less than or equal to, it's square root, then it's a prime number.
void prime2(int num)
{
	int curr, div;
	int i;

	if (num<2)
		return;

	curr = 2;
	while(curr <= num)
	{
		div = (int)sqrt(curr);
		for (i=2; i<=div; i++)
		{
			if (curr%i==0 && curr!=i && 1!=i)
				break;
		}
		if (i>div)
			printf("%d ", curr);
		curr++;
	}
	printf("\n");
}