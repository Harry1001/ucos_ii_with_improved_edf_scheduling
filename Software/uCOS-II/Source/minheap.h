#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include <os_cpu.h>

typedef struct heap_data{
	INT32U prio;
	INT32U deadline;
}Heap_Data;

typedef struct myheap{
	INT32U capacity;
	INT32U size;
	Heap_Data *elements;
}MinHeap;

MinHeap* heapInitialize();
void clearHeap(MinHeap* heap);
void heapInsert(Heap_Data* data, MinHeap* heap);
INT32U heapDeleteMin(MinHeap* heap);
INT8U isFull(MinHeap* heap);
INT8U isEmpty(MinHeap* heap);
INT32U heapPeakMinTask(MinHeap *heap);

#endif