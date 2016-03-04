#include <stdio.h>
#include <stdlib.h>

int binary_search_recursive(int *array, int low, int high, int value)
{
	if(low > high)
		return -1;

	int middle = (low + high) / 2;
	if(array[middle] == value)
		return middle;
	else if(value < array[middle])
		return binary_search_recursive(array, low, middle - 1, value);
	else
		return binary_search_recursive(array, middle + 1, high, value);
}

#ifdef BINARY_SEARCH_RECURSIVE
int main()
{
	int len;
	printf("Please input the array length:\n");
	scanf("%d", &len);

	int *array = malloc(sizeof(int) * len);
	printf("Please input the array elements:\n");
	for(int i = 0; i < len; i++)
		scanf("%d", array + i);

	int value;
	printf("Please input the value being searched:\n");
	scanf("%d", &value);
	int index = binary_search_recursive(array, 0, len - 1, value);

	printf("The index of value %d in array is %d.\n", value, index);
	free(array);

	return 0;
}
#endif
