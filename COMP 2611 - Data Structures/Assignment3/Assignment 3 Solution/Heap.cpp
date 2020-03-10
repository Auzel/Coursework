#include <iostream>
#include "DataTypes.h"
#include "Heap.h"
   using namespace std;

// Functions that are common to both max-heaps and min-heaps

int parent(int i) {
	return (i/2);
}

int leftChild(int i) {
	return (2 * i);
}

int rightChild (int i) {
	return (2 * i) + 1;
}


// Functions that apply only to a max-heap

void maxHeapify (Node A[], int heapSize, int i) {
	int left, right, largest;
	
	left = leftChild(i);
	right = rightChild(i);
	
	if (left <= heapSize && A[left].cost < A[i].cost) 
		largest = left;
	else
		largest = i;
		
	if (right <= heapSize && A[right].cost < A[largest].cost) 
		largest = right;
		
	if (largest != i) {
		Node temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		maxHeapify(A, heapSize, largest);
	}
}

void buildMaxHeap(Node A[], int lengthA) {

	int heapSize, i;
	
	heapSize = lengthA;
	
	for (i = (lengthA/2); i >= 1; i = i - 1) 
		maxHeapify(A, heapSize, i);
}
	
// Functions that apply only to a min-heap

void minHeapify (Node A[], int heapSize, int i) {
	int left, right, smallest;
	
	left = leftChild(i);
	right = rightChild(i);
	
	if (left <= heapSize && A[left].cost < A[i].cost) 
		smallest = left;
	else
		smallest = i;
		
	if (right <= heapSize && A[right].cost < A[smallest].cost) 
		smallest = right;
		
	if (smallest != i) {
		Node temp = A[i];
		A[i] = A[smallest];
		A[smallest] = temp;
		minHeapify(A, heapSize, smallest);
	}
}

void buildMinHeap(Node A[], int lengthA) {

	int heapSize, i;
	
	heapSize = lengthA;
	
	for (i = (lengthA/2); i >= 1; i = i - 1) 
		minHeapify(A, heapSize, i);
}
