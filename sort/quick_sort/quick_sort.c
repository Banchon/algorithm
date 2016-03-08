#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
int partition(int *array, int p, int r);
void quick_sort(int *array, int p, int r);

void quick_sort(int *array, int p, int r)
{
	if(p < r) {
		int q = partition(array, p, r);
		quick_sort(array, p, q - 1);
		quick_sort(array, q + 1, r);
	}
}

int partition(int *array, int p, int r)
{
	int i = p -1;
	int x = array[r];

	for(int j = p; j < r; j++) {
		if(array[j] <= x) {
			i++;
			swap(array + i, array + j);
		}
	}

	swap(array + i + 1, array + r);
	return i + 1;
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

#ifdef QUICK_SORT 
int main()
{
	int len;
	printf("Please input the array length:\n");
	scanf("%d", &len);

	int *array = (int *)malloc(sizeof(int) * len);
	printf("Please input the array elements:\n");
	for(int i = 0; i < len; i++) {
		scanf("%d", array + i);
	}
	quick_sort(array, 0, len - 1);
	printf("Array after quick sort:\n");
	for(int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	free(array);
	return 0;
}
#endif
