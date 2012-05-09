#include <stdio.h>
#include <stdlib.h>

/*
Building Fibonacci numbers.
*/

//Recursive implementation
int re_fibonacci(int n)
{
	if (0==n)
		return 0;
	else if (1==n)
		return 1;
	else
		return re_fibonacci(n-1)+re_fibonacci(n-2);
}

//Nonrecursive implementation
int fibonacci(int n)
{
	int n1, n2, fib;
	int i;

	if (0 == n)
		return 0;
	if (1 == n)
		return 1;

	n1 = 1;
	n2 = 0;
	for (i=2; i<=n; i++)
	{
		fib = n1+n2;
		n2 = n1;
		n2 = fib;
	}
	return fib;
}