#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_

#include <stdlib.h>
#include <stdio.h>

#if __STDC_VERSION__ >=199901L
#else
#define TRUE	1
#define FALSE	0
typedef int BOOL;

#define inline static

#endif


typedef struct
{
	int num;		//lcs length
	int	x;			//the colummn number of the cell from which current cell points.
	int	y;			//the row number.
	int	flag;	//true, if the xth character of string1 equals the yth character of string2.
}CELL;

#endif