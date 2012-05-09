/*
C memory allocation and free.
*/
#include "..\header\mem.h"

//allocate memory for 2D array
//CELL type
CELL** mem_alloc_2D(CELL ***table, int len1, int len2)
{
	int j;
	if (NULL != ((*table) = (CELL **)malloc(len1*sizeof(CELL *))))
	{
		for (j=0; j<len1; j++)
		{
			if (NULL == ((*table)[j] = (CELL *)calloc(len2, sizeof(CELL))))
			{
				printf ("memory allocation for table[] failed.\n");
				return NULL;
			}
		}
	}
	else
	{
		printf("memory allocation for table failed.\n");
		return NULL;
	}
	return (*table);
}

//int type
int** mem_alloc_2D_int(int ***table, int len1, int len2)
{
	int j;
	if (NULL != ((*table) = (int **)malloc(len1*sizeof(int *))))
	{
		for (j=0; j<len1; j++)
		{
			if (NULL == ((*table)[j] = (int *)calloc(len2, sizeof(int))))
			{
				printf ("memory allocation for table[] failed.\n");
				return NULL;
			}
		}
	}
	else
	{
		printf("memory allocation for table failed.\n");
		return NULL;
	}
	return (*table);
}

//free 2D array memory
void mem_free_2D(CELL **table, int len)
{
	int j;
	if (table)
	{
		for (j=0; j<len; j++)
		{
			if (table[j])
				free(table[j]);
		}
		free(table);
	}
}

//int
void mem_free_2D_int(int **table, int len)
{
	int j;
	if (table)
	{
		for (j=0; j<len; j++)
		{
			if (table[j])
				free(table[j]);
		}
		free(table);
	}
}