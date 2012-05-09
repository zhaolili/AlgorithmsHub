#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

extern int re_fibonacci(int n);
extern int fibonacci(int n);
extern void LongestCommonSubsequence(char *String1, char *String2);
extern void needleman(char *string1, char *string2, int price[3]);
extern void smith(char *string1, char *string2, int price[3]);


int main (int argc, char *argv[])
{
	char *str1="GCCCTAGCG";
	char *str2="GCGCAATGCCCTG";
	int price[3] = {1, -2, -1};

	//LongestCommonSubsequence(str1, str2);
	//needleman(str1, str2, price);
	smith(str1, str2, price);

	return 0;
}