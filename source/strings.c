//
//String operations
//

#include "..\header\strings.h"
#include "..\header\common_def.h"




//-----String matching---------------------------------
//p[]: pattern string
//t[]: text string
//m: the length of pattern string
//n: the length of text string

//simple matching algorithm
int searchsubstring(char p[], char t[], int m, int n)
{
	int i, j;
	for (i=0; i<n-m+1; i++)
	{
		for (j=0; j<m; j++)
		{
			if (p[j]!=t[i+j])
				break;
		}
		if(j==m)	//
			return i;
	}
	return -1;
}

//The Knuth-Morris-Pratt algorithm
//compute pi values
void compute_pi(char p[], int m, int *pi)
{
	int i, q;
	pi[0] = q = 0;			//the first char
	for (i=0; i<m-1;)
	{	
		//P[0, ..., pi(i)] is the longest prefix of P[0,..,i] that is also a suffix of it.
		if (p[q] == p[i+1])
		{
			pi[i+1] = q+1;	//update pi
			q = pi[i+1];
			i++;
		}
		else
		{
			if (0 != q)
				q = pi[q-1];		//index starts from 0
			else
				i++;
		}
	}
}
//KMP algorithm
int KMP(char p[], char t[], int pi[], int m, int n)
{
	int i;
	int q;

	i=q=0;
	while (i<n)
	{
		if (p[q] == t[i])
		{
			i++;
			q++;
			if (q==m-1){
				return i-q;
			}
		}
		else
		{
			if (q==0) {i++;}
			else q = pi[q-1];
		}		
	}
	return -1;
}
//Boyer Moore algorithm, BM
//"The BM algorithm is considered as the most efficient string-matching algorithm in usual applications. A simplified version of it or the entire algorithtm is often implemented in text editors for the search and substitute commands."
//"The algorithm scans the charactres of the pattern from right to left beggining with the rightmost one. In case of a mismatch(or a complete match of the whole pattern) it uses two precomputed functions to shift the window to the right."
//--http://www-igm.univ-mlv.fr/~lecroq/string/node14.html

//The implementation is not completed yet.
//bad char table
void preBadChar(char *p, int BC[], int m, int asize)
{
	int i;
	for (i=0; i<asize; i++)
	{
		BC[i] = m;
	}
	for (i=0; i<m; i++)
	{
		BC[p[i]] = m-1-i;
	}
}

//good suffix table
//get suff table
//			-|<--suff[i]-->|		|<--suff[i]-->|
//---------------------------------------------------
//						  i|					 m|

//a straightforward solution
void getSuff(char *p, int suff[], int m)
{
	int i, q;

	suff[m-1] = m;
	for (i=m-2; i>=0; i--)
	{
		q = i;
		while (p[q] == p[m-(i-q)-1] && q>=0)
			--q;
		suff[i] = i-q+1;
		if (q<0)
			suff[i] -= 1;		//i-(q+1)+1
	}
}

//
void preGoodSuf(char *p, int GS[], int suff[], int m)
{
	int i, j;
	
	//have no suff
	for (i=0; i<m; i++)
	{
		GS[i] = m;
	}
	
	//|=======|-------------|----------========|
	for (i=m-1; i>=0; i++)
	{
		j = 0;
		if (suff[i] == i+1)
			for (; j<m-i; j++)
			{
				if (GS[j] == m)
					GS[j] = m-i-1;
			}
	}

	//
	for (i=0; i<m; i++)
	{
		GS[m-suff[i]] = m-1 -i;
	}
}

//BM search algorithm
int BMSearch(char *p, char *t, int m, int n)
{
	int s;
	int i;
	int *Bc, *Gs;

	i = m-1;
	for (s=0; s<=n-m; s++)
	{
		if (i>=0 && p[i] == t[s+i])
		{
			i--;
		}
		if (i<0)
		{
			return s+i+1;
		}
		s += max(Bc[t[s+i]]-(m-1-i), Gs[i]);
		i = m-1;
	}
}

//Rabin-Carp algorithm
//--http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching

//suffix tree
//-http://www.allisons.org/ll/AlgDS/Tree/Suffix/
