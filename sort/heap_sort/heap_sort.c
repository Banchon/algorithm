#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)
#define PARENT(i) (((i) - 1) >> 1)


void max_heapify(int *array, int heap_size, int i)
{
	int largest = i;
	int l = LEFT(i);
	int r = RIGHT(i);
	if( l < heap_size && array[l] > array[largest])
		largest = l;
	if( r < heap_size && array[r] > array[largest])
		largest = r;
	if(largest != i) {
		int temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;
		max_heapify(array, heap_size, largest);
	}
}

void build_max_heap(int *array, int heap_size)
{
	for(int i = heap_size / 2; i >= 0; i--)
		max_heapify(array, heap_size, i);
}

void heap_sort(int *array, int len)
{
	build_max_heap(array, len);
	for(int i = len - 1; i > 0; i--) {
		int temp = array [i];
		array[i] = array[0];
		array[0] = temp;
		max_heapify(array, i, 0);
	}
}

#ifdef HEAP_SORT 
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

	heap_sort(array, len);
	printf("The array after heap_sort:\n");
	for(int i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");

	free(array);
	return 0;
}
#endif