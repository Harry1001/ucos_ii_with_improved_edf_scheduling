#include "minheap.h"
#include <ucos_ii.h>
#include <stdlib.h>

#define TASK_MAX 64

MinHeap* heapInitialize(){
	MinHeap *heap;
	heap = (MinHeap*)malloc(sizeof(MinHeap));
	if (heap == 0){
		exit(1);
	}
	heap->size = 0;
	heap->capacity = TASK_MAX;
	//the first element of array is sentinel_element -1, but when compute size and capacity, it is not included

	heap->elements = (Heap_Data*)malloc(sizeof(Heap_Data)*(TASK_MAX + 1));
	if (heap->elements == 0){
		exit(1);
	}
	else{
		heap->elements[0].deadline = 0;
		heap->elements[0].prio = -1;
	}
	return heap;
}

void clearHeap(MinHeap* heap){
	if (heap != 0){
		heap->size = 0;
	}
	else{
		exit(1);
	}
}

void heapInsert(Heap_Data* data, MinHeap* heap){
	if (heap == 0){
		exit(1);
	}
	if (isFull(heap)){
		exit(1);
	}
	else{
		INT32U i;
		for (i = ++heap->size; data->deadline<(heap->elements[i / 2]).deadline; i /= 2){
			heap->elements[i] = heap->elements[i / 2];
		}
		heap->elements[i].deadline = data->deadline;
		heap->elements[i].prio = data->prio;
	}
}

INT32U heapPeakMinTask(MinHeap *heap)
{
	if (heap == 0 || isEmpty(heap)){
		return OS_TASK_IDLE_PRIO;
	}
	return heap->elements[1].prio;
}

INT32U heapDeleteMin(MinHeap* heap){
	INT32U i;
	INT32U child;
	Heap_Data min;
	Heap_Data last;

	if (heap == 0){
		exit(1);
	}
	if (isEmpty(heap)){
		return OS_TASK_IDLE_PRIO;
	}
	min = heap->elements[1];
	last = heap->elements[heap->size--];
	for (i = 1; i * 2 <= heap->size; i = child){
		child = i * 2;
		if (child<heap->size&&heap->elements[child].deadline > heap->elements[child + 1].deadline){
			child++;
		}
		if (last.deadline < heap->elements[child].deadline){
			break;
		}
		else{
			heap->elements[i] = heap->elements[child]; //иобк
		}
	}
	heap->elements[i] = last;
	return min.prio;
}

INT8U isFull(MinHeap* heap){
	if (heap == 0){
		exit(0);
	}
	else{
		return heap->size == heap->capacity;
	}
}

INT8U isEmpty(MinHeap* heap){
	if (heap == 0){
		exit(1);
	}
	else{
		return heap->size == 0;
	}
}