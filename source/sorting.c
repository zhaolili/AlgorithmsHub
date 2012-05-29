//
//sorting operations
//

#include "..\header\sorting.h"
#include "..\header\common_def.h"


//bubble sort
//Bubble sort works by repeatedly exchanging adjacent numbers
//Complexity: O(n^2)
//Stable
//Need no extra memory
void bubblesort(int data[], int n)
{
	int i,j;
	int tmp;
	//int bcomp = FALSE;	

	for (i=0; i<n-1; i++)
	{
		for (j=0; j<n-i-1; j++)
		{
			if (data[j] > data[j+1] )
			{
				tmp = data[j+1];
				data[j+1] = data[j];
				data[j] = tmp;
				//bcomp = TRUE;
			}
		}
		/*if (!bcomp)
			break;*/
	}
}

//insert sort
//Complexity: O(n^2)
//Stable
//Need no extra memory
void insertsort(int data[], int n)
{
	int i, j;
	int tmp;

	for (i=0; i<n-1; i++)
	{
		tmp = data[i+1];
		for (j=i+1; j>0; j--)
		{
			if (tmp <data[j-1])
			{
				data[j] = data[j-1];
			}
			else
			{
				data[j] = tmp;
				break;
			}
		}
		if (j==0)
		{
			data[j] = tmp;
		}
	}
}

//selection sort
//select from the suceeding n-i numbers the smallest one to insert in position i;
//Complexity: O(n^2)
//Stable
//Need no extra memory
void selectsort(int data[], int n)
{
	int i, j;
	int tmp, min;

	for (j=0; j<n-1; j++)
	{
		min = j;
		for (i=j+1; i<n; i++)
		{
			if (data[i]<data[min])
			{
				min = i;
			}
		}
		if (i!=j)
		{
			tmp = data[j];
			data[j] = data[min];
			data[min] = tmp;
		}
	}
}

//Shell sort
//Shell sort is a variant of insert sort.
//Shell sort can be implemeted in two steps:
//Arrange the data sequnce in a 2D array
//Sort the columns of the array
//The effect is that the data sequence is partially sorted. The process above is repeated, but each time with a narrower array, i.e. with a smaller number of columns. In the last step, the array consists of only one column.
//The number of Shell sorting operations necessary in each step is limited due to the presotedness of the sequence obtained in the preceding steps.

//gap: the invertal of two numbers in the same group
//len: the number of data in total
void shellinsert(int data[], int gap, int len)
{
	int i, m, n;
	int num;		//the number of elements in current group
	int tmp;
	int anc;

	for (i=0; i<gap; i++)
	{
		num = len/gap;
		if (len%gap>i)
			num++;

		//selection sort
		for (n=0; n<num-1; n++)
		{
			anc = data[(n+1)*gap+i];
			for (m = n; m>=0; m--) 
			{
				if (anc < data[m*gap+i])
				{
					data[(m+1)*gap+i] = data[m*gap+i];
				}
				else
				{
					break;
				}
			}
			data[(m+1)*gap+i] = anc;
		}
	}
}

void shellinsertmain(int data[], int gap[], int n, int m)
{
	int i;

	for (i=0;i<m; i++)
	{
		shellinsert(data, gap[i], n);
	}
}

//heap sort

//堆调整从当前节点m开始调整其子树
void HeapAdjust(int data[], int N, int m)
{
	int j;			//child node
	int rc;			//key
	rc = data[m];

	for (j=m*2+1; j<N; j+=2)
	{
		if (j<N-1 && data[j]<data[j+1]) j++;
		if (rc>=data[j])	break;			//already big heaped
		data[m] = data[j];
		m = j;
	}
	data[m] = rc;
}

void HeapSort(int data[], int N)
{
	int j;
	int tmp;
	
	//Build heap
	//建堆的过程是从最后一个非叶子结点开始向上调整堆的过程
	for (j=(N/2-1); j>=0; j--)		//the last non-leaf node is N/2-1
	{
		HeapAdjust(data, N, j);
	}

	//Now we have a big heap
	//exchange the maximum node with the last node and then adjust heap
	for (j=N-1; j>0; j--)
	{
		//exchange
		tmp = data[j];
		data[j] = data[0];
		data[0] = tmp;

		//adjust heap
		HeapAdjust(data, j, 0);
	}
}

//Merge sort
//recursive implementation

//Merge
void merge(int data[], int p, int q, int r)
{
	int *temp;
	int i,j, k;

	temp = (int *)calloc((r-p+1), sizeof(int));

	for (j=0; j<=(q-p); j++)
	{
		temp[j] = data[p+j];
	}
	for (j=q-p+1; j<(r-p+1); j++)
	{
		temp[j] = data[p+j];
	}
	
	i = j = 0;
	k = 0;
	while (TRUE)
	{
		if (k>(r-p))
			break;
		if (temp[i]<=temp[j+(q-p+1)])
		{
			data[(k++)+p] = temp[i++];
		}
		else
		{
			data[(k++)+p] = temp[(j++)+(q-p+1)];
		}
		if (i>(q-p))
		{
			for (;j<(r-q); )
			{
				data[(k++)+p] = temp[(j++)+(q-p+1)];
			}
		}
		if (j>(r-q-1))
		{
			for (;i<=(q-p);)
			{
				data[(k++)+p] = temp[i++];
			}
		}
	}

	if (temp)
		free(temp);
}

//MergeSort
//recursive implementation
void rMergeSort(int data[], int p, int q)
{
	int mid;
	if (p==q)
		return;
	mid = (p+q)/2;
	rMergeSort(data, p, mid);
	rMergeSort(data, mid+1, q);
	merge(data, p, mid, q);
}
//non-recursive implementation
void MergeSort(int data[], int p, int q)
{
	int i, k;
	int m, n, l;

	n = (q-p+1)/2;
	l = 2;

	while(TRUE)
	{
		if (n==0)
			break;
		m = l/2-1;
		for (k=0; k<n-1; k++)
		{
			i = k*l;
			merge(data, p+i, p+i+m, p+i+l-1);
		}

		i = (n-1)*l;
		m = (q-p-i)/2;
		merge(data, p+i, p+i+m, q-p);

		n = n>>1;
		l = l<<1;
	}
}
