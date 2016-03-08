#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)
#define PARENT(i) (((i) - 1) >> 1)

typedef struct max_priority_queue_s {
	int *array;
	int len;
} max_priority_queue_t;

void max_heapify(int *array, int heap_size, int i);
int heap_maximum(int *array, int len, int *result);
int heap_extract_max(int **array_ptr, int *heap_size, int *result);
int heap_increase_key(int *array, int heap_size, int i, int key);
int max_heap_insert(int **array_ptr, int *len, int x);

/***************The API of max priority queue*******************/
int maximum(max_priority_queue_t queue, int *result)
{
	return heap_maximum(queue.array, queue.len, result);
}

int extract_max(max_priority_queue_t *queue_ptr, int *result)
{
		return heap_extract_max(&(queue_ptr->array), &(queue_ptr->len), result);
}

int increase_key(max_priority_queue_t queue, int i, int key)
{
	return heap_increase_key(queue.array, queue.len, i, key);
}

int insert(max_priority_queue_t *queue, int x)
{
	return max_heap_insert(&(queue->array), &(queue->len), x);
}

void init(max_priority_queue_t *queue) {
	if(queue != NULL) {
		queue->array = NULL;
		queue->len = 0;
	}
}
/*************************************************************/


/*****The internel implementation of max priority queue******/
void max_heapify(int *array, int heap_size, int i)
{
	int largest = i;
	int l = LEFT(i);
	int r = RIGHT(i);

	if(l < heap_size && array[l] > array[largest])
		largest = l;
	if(r < heap_size && array[r] > array[largest])
		largest = r;
	if(largest != i) {
		int temp = array[i];
		array[i] = array[largest];
		array[largest] =temp;
		max_heapify(array, heap_size, largest);
	}
}

int heap_maximum(int *array, int len, int *result)
{
	if(len < 1) {
		return -1;
	} else {
		*result = array[0];
		return 0;
	}
}

int heap_extract_max(int **array_ptr, int *heap_size, int *result)
{
	if(*heap_size < 1) {
		return -1;
	} else {
		int len = *heap_size;
		int max = (*array_ptr)[0];
		(*array_ptr)[0] = (*array_ptr)[len - 1];
		*array_ptr = (int *)realloc(*array_ptr, sizeof(int) * (len - 1));
		*heap_size = len  - 1;
		if(*heap_size > 0) {
			max_heapify(*array_ptr, *heap_size, 0);
		}
		*result = max;
		return 0;
	}
}

int heap_increase_key(int *array, int heap_size, int i, int key)
{
	if( i >= heap_size || i < 0) {
		return -1;
	}

	if(array[i] > key) {
		return -1;
	}

	array[i] = key;

	while(i > 0 && array[PARENT(i)] < array[i]) {
		int temp = array[PARENT(i)];
		array[PARENT(i)] = array[i];
		array[i] = temp;
		i = PARENT(i);
	}
	return 0;
}

int max_heap_insert(int **array_ptr, int *len, int x)
{
	if(*len < 1) {
		*array_ptr = (int *)malloc(sizeof(int));
		(*array_ptr)[0] = x;
		*len = 1;
	} else {
		*array_ptr = (int *)realloc(*array_ptr, sizeof(int) * (*len + 1));
		*len = *len + 1;
		(*array_ptr)[*len - 1] = INT_MIN; //fixme: 
		heap_increase_key(*array_ptr, *len, *len - 1, x);
	}
	return 0;
}
/************************************************************/


#ifdef MAX_PRIORITY_QUEUE 
int main()
{
	max_priority_queue_t queue;
	init(&queue);

	int result;
	printf("Now the queue is empty. We test the maximum and extract_max api.\n");
	printf("The result of maximum: %d\n", maximum(queue, &result));
	printf("The result of extract_max: %d\n", extract_max(&queue, &result));

	printf("Now we test the insert api.\n");
	printf("Please input the number of elements to insert:\n");
	int num;
	scanf("%d", &num);

	int element;
	for(int i = 0; i < num; i++) {
		scanf("%d", &element);
		insert(&queue, element);
	}

	printf("Now pop all the elements in the queue to see whether the inserts in last step right.\n");
	for(int i = 0; i < num; i++) {
		if(extract_max(&queue, &element) == 0)
			printf("%d ", element);
	}
	printf("\n");

	printf("Now we insert some elements again.\n");
	printf("Please input the number of elements to insert:\n");
	scanf("%d", &num);
	for(int i = 0; i < num; i++) {
		scanf("%d", &element);
		insert(&queue, element);
	}

	printf("The inner state of the max priority queue is:\n");
	for(int i = 0; i < queue.len; i++)
		printf("%d ", (queue.array)[i]);
	printf("\n");

	printf("Now we test the increase_key api. Type Ctrl-C to terminate.\n");
	while(1) {
		int index;
		printf("Please input the index that you want to increase:\n");
		scanf("%d", &index);
		printf("please input the key:\n");
		int key;
		scanf("%d", &key);
		increase_key(queue, index, key);
		printf("The inner state of the max priority queue after increase_key is:\n");
		for(int i = 0; i < queue.len; i++)
			printf("%d ", (queue.array)[i]);
		printf("\n");
	}

	if(queue.len > 0)
		free(queue.array);
	return 0;
}
#endif
