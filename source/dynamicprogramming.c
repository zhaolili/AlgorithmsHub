/*
Description	:Dynamic Programming to solve the Longest Common Subsequence problem, Global and Local sequence alognment problems.
Author		:Lili Zhao <zhao86.scholar@gmail.com>
Date		:May, 2012
*/

#include "..\header\common_def.h"
#include <string.h>


/*
Longest Common Subsequence problem.
"The characters in a subsequence, unlike those in a substring, do not need to
be contiguous. For eaxample, ACE is a subsequence (but not a substring) of ABCDE."
*/

/*
*/
void traceback_lcs(char *lcs, char *String1, char *String2, CELL *table[])
{
	int counter;
	int x, y, t;

	y = strlen (String1);
	x = strlen (String2);
	counter = table[y][x].num;
	while(counter>0)
	{
		if (TRUE == table[y][x].flag)
		{ 
			lcs[counter-1] = String1[y-1]; 
			counter--;			
		}
		t = table[y][x].y;
		x = table[y][x].x;
		y = t;
	}
}

/*
Parameters	:String1, holding characters of sequence 1
			:String2, holding characters of sequence 2
Return value:None.
*/
void LongestCommonSubsequence(char *String1, char *String2)
{
	int i, j;
	int len1, len2, len_lcs;
	char *lcs=NULL;		//hold the lcs
	CELL **table;		//lcs table[len1+1][len2+1], [x][y] with x being the xth character in string 1, and y being the yth character in string 2

	len1 = strlen (String1);
	len2 = strlen (String2);

	//malloc memory
	if (NULL == mem_alloc_2D(&table, len1+1, len2+1))
		goto Exit;

	//fill in the table, the 0th row and column have been initialized with zeros
	for (j=1; j<len1+1; j++)		//table rows
	{
		for (i=1; i<len2+1; i++)	//table columns
		{ 
			table[j][i].num = table[j-1][i-1].num;
			table[j][i].x = i-1;
			table[j][i].y = j-1;
			if (String1[j-1] == String2[i-1])
			{
				table[j][i].num++;
				table[j][i].flag = TRUE;
			}
			if (table[j-1][i].num > table[j][i].num)
			{
				table[j][i].num = table[j-1][i].num;
				table[j][i].x++;
			}
			if (table[j][i-1].num > table[j][i].num)
			{
				table[j][i].num = table[j][i-1].num;
				table[j][i].y++;
			}
		}
	}

	len_lcs = table[len1][len2].num;
	if (NULL == (lcs = (char *)calloc(len_lcs, sizeof(len_lcs))))
	{
		printf("Memory allocation for LCS sequence failed.\n");
		goto Exit;
	}

	//Get the LCS
	traceback_lcs(lcs, String1, String2, table);

	//print the LCS
	printf("The LCS of %s and %s is %s.\n", String1, String2, lcs);

Exit:
	//release memory
	if (lcs)
		free(lcs);
	mem_free_2D(table, len1+1);

	return;
}

/*
"In sequence alignment, you want to find an optimal alignment that, loosely speacking, maximizes the number of mathces and minimizes
the number of spaces and mismatches.
Needleman-Wunsch algorithm is an example used for computing global sequence alignment.
Smith-Waterman algorithm is an exmaple used for computing local sequence alignment.
*/

//Needleman-Wunsch algorithm

/*
*/
void traceback_needleman(char *alignedseq, char *string1, char *string2, CELL *table[])
{
	int i, j, tmp;
	int len1, len2, len;

	len1 = strlen(string1);
	len2 = strlen(string2);
	len = (len1>len2) ? len1 : len2;

	j = len1;
	i = len2;
	while (j!=0 && i!=0)
	{
		switch (table[j][i].flag)
		{
		case -1:
			alignedseq[--len] = (len1>len2) ? string2[i-1] : string1[j-1];
			break;
		case 0:
			alignedseq[--len] = string1[j-1];
			break;
		case 1:
			alignedseq[--len] = (len1>len2) ? '-' : string1[j-1];
			break;
		case 2:
			alignedseq[--len] = (len1>len2) ? string2[i-1] : '-';
			break;
		}
		tmp = table[j][i].y;
		i = table[j][i].x;
		j = tmp;
	}
}
/*
Inputs	:string1
		:string2
		:price[3]: 0, match award; 1, space penalized cost; 2, mismatch cost
*/
void needleman(char *string1, char *string2, int price[3])
{
	int i,j;
	int len1, len2;
	CELL **table;
	char *alignedseq;

	len1 = strlen(string1);
	len2 = strlen(string2);

	//allocate memory for table
	if (NULL == mem_alloc_2D(&table, len1+1, len2+1))
		goto Exit;

	//Initialize the 0th row and column of the table
	for (j=1; j<len1+1; j++)
	{
		table[j][0].num = table[j-1][0].num + price[1];
	}
	for (i=1; i<len2+1; i++)
	{
		table[0][i].num = table[0][i-1].num + price[1];
	}

	//fill in table
	for (j=1; j<len1+1; j++)
	{
		for (i=1; i<len2+1; i++)
		{
			table[j][i].num = table[j-1][i-1].num;
			table[j][i].y = j-1;
			table[j][i].x = i-1;				
			if (string1[j-1] == string2[i-1])		//match
			{
				table[j][i].flag = 0;	//match
				table[j][i].num = table[j][i].num + price[0];
			}
			else									//mismatch
			{
				table[j][i].flag = -1;
				table[j][i].num = table[j][i].num + price[2];
			}

			if (table[j-1][i].num+price[1] > table[j][i].num)		//above
			{
				table[j][i].num = table[j-1][i].num + price[1];		//space penalty
				table[j][i].x = i;
				table[j][i].flag = 1;			//insert space in string2 
			}
			if (table[j][i-1].num+price[1] > table[j][i].num)
			{
				table[j][i].num = table[j][i-1].num + price[1];
				table[j][i].y = j;
				table[j][i].x = i-1;
				table[j][i].flag = 2;			//insert space in string1
			}
		}
	}

	//allocate memory for aligned sequence
	if (NULL == (alignedseq = (char *)calloc((len1>len2?len1:len2)+1, sizeof(char))))
	{
		printf("memory allocation for algined sequence failed.\n");
		goto Exit;
	}

	//trace back
	traceback_needleman(alignedseq, string1, string2, table);

	//print the aligned sequence
	if (len1 > len2)
		printf("The global aligned sequence of \" %s\" and \" %s \" is :\n%s\n%s\n", string1, string2, string1, alignedseq);
	else
		printf("The global aligned sequence of \" %s\" and \" %s \" is :\n%s\n%s\n", string1, string2, string2, alignedseq);

Exit:
	//release memory
	if (alignedseq)
		free(alignedseq);
	mem_free_2D(table, len1+1);

	return;
}

//Smith-Waterman algorithm
//Smith-Waterman is different from Needleman-wushen algorithm in three ways:
//First, in the initialization stage, the fist row and fist column are filled in with 0s.
//Second, when you fill in the table, if a score becomes negative, you put in 0 instead, and you add the pointer back only for cells that have positive scores.
//Finally, in the tracebackm you start with the cell that has the highest score and work abck until you reach a cell with a score of 0. (the cell with a score of 0 should be excluded from the local aligned sequence.)


void traceback_smith(char *str1, char *str2, char *seq1, char *seq2, CELL *table[], int y, int x)
{
	int i, j, tmp;
	int len;

	len = 0;

	j = y; i = x;
	while(table[j][i].num>0)
	{
		switch (table[j][i].flag)
		{
		case 0:
			seq1[len++] = str1[j-1];
			seq2[len] = str2[i-1];
			break;
		case -1:
			seq1[len++] = str1[j-1];
			seq2[len] = str2[i-1];
			break;
		case 1:
			seq1[len++] = '-';
			seq2[len] = str2[i-1];
			break;
		case 2:
			seq1[len++] = str1[j-1];
			seq2[len] = '-';
		}
		tmp = table[j][i].y;
		i = table[j][i].x;
		j = tmp;
	}

}

void smith(char *string1, char *string2, int price[3])
{
	int i,j, max, maxy, maxx;
	int len1, len2;
	char *alignedseq1, *alignedseq2;
	CELL **table;
	CELL maxcell;
	
	len1 = strlen(string1);
	len2 = strlen(string2);

	if (NULL == mem_alloc_2D(&table, len1+1, len2+1))
		goto Exit;
	if (NULL == (alignedseq1 = (char *)calloc((len1>len2 ? len1+1: len2+1), sizeof(char))))
	{
		printf("memory allocation for alignedseq1 failed.\n");
		goto Exit;
	}
	if (NULL == (alignedseq2 = (char *)calloc((len1>len2 ? len1+1: len2+1), sizeof(char))))
	{
		printf("memory allocation for alignedseq1 failed.\n");
		goto Exit;
	}

	//initialize the first row and first column in the table
	for (j=0; j<len1+1; j++)		
	{
		table[j][0].num = 0;		//we don't initialize the traceback pointers for the first column cells since they are not used  
	}
	for (j=1; j<len2+1; j++)
	{
		table[0][j].num = 0;
	}

	max = 0;

	//fill in the table
	for (j=1; j<len1+1; j++)
	{
		for (i=1; i<len2+1; i++)
		{
			table[j][i].num = table[j-1][i-1].num;
			table[j][i].y = j-1;
			table[j][i].x = i-1;
			if (string1[j-1] == string2[i-1])
			{
				table[j][i].num += price[0];
				table[j][i].flag = 0;
			}
			else 
			{
				table[j][i].num += price[2];
				table[j][i].flag = -1;
			}
			if (table[j-1][i].num +price[1] > table[j][i].num )
			{
				table[j][i].num = table[j-1][i].num + price[1];
				table[j][i].x = i;
				table[j][i].flag = 1;
			}
			if (table[j][i-1].num +  price[1] > table[j][i].num)
			{
				table[j][i].num = table[j][i-1].num + price[1];
				table[j][i].y = j;
				table[j][i].x = i-1;
				table[j][i].flag = 2;
 			}
			if (table[j][i].num < 0) table[j][i].num = 0;
			else {
				if (table[j][i].num >max)
				{
					max = table[j][i].num;
					maxy = j;
					maxx = i;
				}
			}
		}
	}

	traceback_smith(string1, string2, alignedseq1, alignedseq2, table, maxy, maxx);

	printf("The local aligned sequence for %s and %s is:\n%s\n%s\n", string1, string2, alignedseq1, alignedseq2);

Exit:
	mem_free_2D(table, len1+1);
	if (alignedseq1)
		free(alignedseq1);
	if (alignedseq2)
		free(alignedseq2);
}


//The Knapsack problem
//Suppose you have a knapsack which can hold at most W pounds.
//And you can choose as many as goods which have weights and values for each.
//In which way can you fill in you knapsack with value-maximized goods? 

/*
Description: A nonrecursive (DP) solution to the knapsack problem.
Inputs	:v[] contains the price for each good
		:w[] contains the weight for each good
		:num, the number of items
		:capacity, the maximum weights your knapsack can hold
*/
int knapsack(int v[], int w[], int num, int capacity)
{
	/*
	Define v(i,j) as the maximum value that can be attained from considering i items weighting at most j pounds.
	Obviously, we have:
	v(i, j) = 0			if (i=0 or j=0)
			= v(i-1, j)	if (the ith item weighs more than j)
			= max(v[i]+v(i-1, j-w[i]), v(i-1, j)) otherwise
	*/
	int i, j;
	int **value;

	//create a numxcapacity table to save the maximized value in each step
	mem_alloc_2D_int(value, num+1, capacity+1);

	//initialize the cells in the first row and the first column
	for (i=0; i<num+1; i++)
	{
		value[i][0] = 0;
	}
	for (j=1; j<capacity+1; j++)
	{
		value[0][j] = 0;
	}
	
	//fill in the table
	for (i=1; i<num+1; i++)
	{
		for(j=1; j<capacity+1; j++)
		{
			if (v[i]>j)
				value[i][j] = value[i-1][j];
			else
				value[i][j] = (value[i-1][j] > (v[i] + value[i-1][j-w[i]])) ? value[i-1][j] : v[i] + value[i-1][j-w[i]];
		}
	}

	//release memory
	mem_free_2D_int(value, num+1);

	//return the maximum value
	return value[num][capacity];
}

//A recursive implementation for the knapsack problem
int knapsack_re(int v[], int w[], int num, int capacity)
{
	int val1, val2;

	if (num==0 || capacity==0)
		return 0;
	if (w[num] > capacity)
		return knapsack_re(v, w, num-1, capacity);
	val1 = knapsack_re(v, w, num-1, capacity);
	val2 = knapsack_re(v, w, num-1, capacity-w[num]) + v[num];

	return val1>val2 ? val1: val2;
}


//Travel Salesman Problem
//Given n cities and the distance between any two of them, we wish to find the shortest tour goinh through all cities and back to the starting city.
//Usually the TSP is given as G=(V,D), where V={1,2,...n} is the set of cities, and D is the adjacency distance matrix.
//The problem is to find the tour with minimal distance weight, that starting in 1 goes trough all n cities and returns to 1.


/*
Input	:distancet[j][i] distance from city j+1 to city i+1
		:N number of cities in total
*/
int travel_salesman_problem(int *distance[], int N)
{
	int i, j, s;
	int **cost; //cost[n][c]	//the cost of starting from 1, going through n citys and reaching city c+1 (c!=0)
	int tmp, min = MAX_VALUE;

	//allocate memory
	mem_alloc_2D_int(&cost, N, N);
	
	//fill in the table
	for (s=0; s<N-1; s++)
	{
		for (j=1; j<N; j++)
		{
			if (s==0)
				cost[s][j] = distance[0][j];
			else
			{
				for (i=1; i<N; i++)
				{
					tmp = cost[s-1][i]+distance[i][j];
					if (tmp<min) min = tmp;
				}
			}
		}
	}

	min = MAX_VALUE;
	for (j=1; j<N; j++)
	{
		tmp = cost[N-2][j]+distance[j][0];
		if (tmp < min) min = tmp;
	}

	//release memory
	mem_free_2D_int(cost, N);

	return min;
}















