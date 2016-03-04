/*CLRS 2.3-7, determine whether there exist two elements sum to x in set S. give a cost of nlg(n) solution at the worst case.
 */

#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Array_s{
	int *ptr;
	int len;
} Array_t;

int delete_repeat_value_in_sorted_array(int *array, int len)
{
	int k = 0;
	for(int i = 0; i < len;) {
		int j = i + 1;
		while((array[j] == array[i]) && (j < len))
			j++;
		array[k] = array[i];
		i = j;
		k++;
	}

	return k;
}

Array_t look_addend_in_set(int *array, int len, int x)
{
	int *array_complement = malloc(sizeof(int) * len);
	int *array_copy = malloc(sizeof(int) * len);

	for(int i = 0; i < len; i++) {
		array_complement[i] = x - array[i];	
		array_copy[i] = array[i];
	}
	merge_sort(array_copy, 0, len - 1);
	merge_sort(array_complement, 0, len - 1);

	int n1, n2;
	n1 = delete_repeat_value_in_sorted_array(array_copy, len);
	n2 = delete_repeat_value_in_sorted_array(array_complement, len);
#ifdef DEBUG
	printf("array_copy after delete_repeat_value the length is %d,the elements is:\n", n1);
	for(int i = 0; i < len; i++)
		printf("%d ", array_copy[i]);
	printf("\n");
	printf("array_complement after delete_repeat_value the length is %d, the elements is:\n", n2);
	for(int i = 0; i < len; i++)
		printf("%d ", array_complement[i]);
	printf("\n");
#endif

	int *array_return = malloc(sizeof(int) * (n1 + n2));
	for(int i = 0; i < n1; i++)
		array_return[i] = array_copy[i];
	for(int i = 0; i < n2; i++)
		array_return[n1 + i] = array_complement[i];
	free(array_complement);
	free(array_copy);

	merge_without_sentinel(array_return, 0, n1 - 1, n1 + n2 -1);
	Array_t result;
	result.ptr = array_return;
	result.len = n1 + n2;
	
	return result;
}

int main()
{
	int len;
	printf("Please input the set length:\n");
	scanf("%d", &len);

	int *set = malloc(sizeof(int) * len);
	printf("Please input the set elements:\n");
	for(int i = 0; i < len; i++)
		scanf("%d", set + i);

	int value;
	printf("Please input the sum:\n");
	scanf("%d", &value);

	Array_t result = look_addend_in_set(set, len, value);

	printf("The result are as follows:\n");
	for(int i = 0; i < result.len; i++)
		printf("%d ", *(result.ptr + i));
	printf("\n");

	free(result.ptr);
	free(set);
	return 0;
}
