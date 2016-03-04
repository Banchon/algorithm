#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void merge_with_sentinel(int *array, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int *part_l = malloc(sizeof(int) * (n1 + 1));
	int *part_r = malloc(sizeof(int) * (n2 + 1));

	memcpy(part_l, &array[p], n1 * sizeof(int));
	memcpy(part_r, &array[q + 1], n2 * sizeof(int));

	//for(int i = 0; i < n1; i++)
	//	part_l[i] = array[p + i];

	//for(int i = 0; i < n2; i++)
	//	part_r[i] = array[q + 1 + i];

	
	part_l[n1] = INT_MAX;
	part_r[n2] = INT_MAX;
	
	int i = 0;
	int j = 0;
	for(int k = p; k <= r; k++) {
		if(part_l[i] <= part_r[j]) {
			array[k] = part_l[i];
			i++;
		} else {
			array[k] = part_r[j];
			j++;
		}
	}

	free(part_l);
	free(part_r);
}


void merge_without_sentinel(int *array, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int *part_l = malloc(sizeof(int) * (n1));
	int *part_r = malloc(sizeof(int) * (n2));

	memcpy(part_l, &array[p], n1 * sizeof(int));
	memcpy(part_r, &array[q + 1], n2 * sizeof(int));
/*
	for(int i = 0; i < n1; i++)
		part_l[i] = array[p + i];

	for(int i = 0; i < n2; i++)
		part_r[i] = array[q + 1 + i];
*/
	
	int i = 0;
	int j = 0;
	int k = p;
	while(i < n1 && j < n2) {
		if(part_l[i] <= part_r[j]) {
			array[k] = part_l[i];
			i++;
		} else {
			array[k] = part_r[j];
			j++;
		}
		k++;
	}

	if( i < n1 ) {
		memcpy(&array[k], &part_l[i], sizeof(int) * (n1 - i));
	} else {
		memcpy(&array[k], &part_r[j], sizeof(int) * (n2 - j));
	}

	free(part_l);
	free(part_r);
}



void merge_sort(int *array, int p, int r) 
{
	if(p < r) {
		int q;
		q = (p + r) / 2;
		merge_sort(array, p, q);
		merge_sort(array, q + 1, r);
		merge_without_sentinel(array, p, q, r);
	}
}

#ifdef MERGE_SORT
int main()
{
	int len;
	printf("Please input the array length:\n");
	scanf("%d", &len);

	int *array = malloc(sizeof(int) * len);
	printf("Please input the array elements:\n");
	for(int i = 0; i < len; i++)
		scanf("%d", &array[i]);

	merge_sort(array, 0, len - 1);

	for(int i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");

	free(array);
	return 0;
}
#endif
