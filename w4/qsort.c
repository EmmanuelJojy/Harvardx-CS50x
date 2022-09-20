#include <stdio.h>
#include<stdlib.h>

void q_sort(int *a, int l, int u);
void swap(int *a, int *b);

int main(int argc, int argv[])
{
	int n, i;
	printf("Enter number of elements: ");
	scanf("%d", &n);
	
	// Dynamic memeory allocation
	int *a = malloc(n * sizeof(int));
	if (a == NULL)
	{
		printf("Insuffecient memory!\n");
		return 1;
	}
	
	// Input for array elements
	printf("Enter elements in succession:\n");
	for (i = 0; i < n; i++)
	{
		printf("a[%d] = ", i);
		scanf("%d", a + i);
	}
	
	// Printing unsorted list
	printf("List before sort:\t");
	for (i = 0; i < n; i++)
	{
		printf("%d\t", *(a + i));
	}
	
	
	// Sorting 1D array
	q_sort(a, 0, n);
	
	// Printing sorted list
	printf("\nList after sort:\t");
	for (i = 0; i < n; i++)
	{
		printf("%d\t", *(a + i));
	}
	printf("\n");
	
	free(a);
	return 0;
}

void q_sort(int *a, int l, int u)
{
	if (u - l <= 1)
	{
		return;
	}
	
	// Set first element as the pivot
	int lp = l + 1, up;
	
	for (up = l +1; up < u; up++)
	{
		if (*(a + up) <= *(a + l))
		{
			swap(a + up, a + lp);
			lp++;
		}
	}
	swap(a + lp - 1, a + l);
	q_sort(a, l, lp - 1);
	q_sort(a, lp, u);
}
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
