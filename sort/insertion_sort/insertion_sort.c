#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int array[], int len){
	for(int j = 1; j < len; j++) {
		int key = array[j];
		int i = 0;
		while(i < j && array[i] <= key)
			i++;

		for(int k = j - 1; k >= i; k--) {
			array[k + 1] = array[k];
		}

		array[i] = key;
	}
}


void insertion_sort_back_version(int array[], int len)
{
	for(int j = 1; j < len; j++) {
		int i = j - 1;
		int key = array[j];

		while( i >= 0 && array[i] > key) {
			array[i + 1] = array[i];
			i--;
		}
		
		array[i + 1] = key;
	}
}

int main(int argc, char *argv[])
{
	int len;
	int *array;

	printf("please input the array lenth: ");
	scanf("%d", &len);
	if(len <= 0) {
		printf("invalid array length.\n");
		exit(-1);
	}

	array = malloc(len * sizeof(int));
	if(array == NULL) {
		printf("cannot allocate memeory space.\n");
		exit(-1);
	}

	printf("please input the array elements: ");
	for(int i = 0; i < len; i++)
		scanf("%d", array + i);

	insertion_sort_back_version(array, len);

	printf("array after sort:");
	for(int i = 0; i < len; i++)
		printf(" %d", array[i]);
	printf("\n");

	free(array);
	return 0;
}
