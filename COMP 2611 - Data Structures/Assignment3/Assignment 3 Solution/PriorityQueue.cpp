#include <iostream>
#include "DataTypes.h"
#include "Heap.h"
#include "PriorityQueue.h"
   using namespace std;

// Functions that are common to both min priority queues
// and max priority queues:

bool isEmptyHeap (Node A[], int heapSize) {
	
	return (heapSize == 0);

}

int searchHeap (Node A[], int heapSize, int vertex) {
	
	int i;
	
	for (i=1; i<=heapSize; i=i+1) {
		if (A[i].vertex == vertex)
			return i;
	}
	return -1;
}

// Functions that apply only to a max priority queue:

int maxHeapInsert (Node A[], int heapSize, Node newElement) {
	
	bool success;
	
	heapSize = heapSize + 1;
	A[heapSize] = newElement;
	A[heapSize].cost = -9999;			// priorities will always be greater than this

	success = heapIncreasePriority (A, heapSize, heapSize, newElement.cost);
	
	if (success)
		return heapSize;
	else
		return -1;
}


Node heapMaximum (Node A[], int heapSize) {
	Node maximum;
	
	if (isEmptyHeap(A, heapSize)) {
		maximum.vertex = -1;
		return maximum;
	}
	
	return A[1];	
}


Node heapExtractMax (Node A[], int heapSize) {
	Node maximum;

	if (isEmptyHeap(A, heapSize)) {
		maximum.vertex = -1;
		return maximum;
	}
	
	maximum = A[1];
	A[1] = A[heapSize];
	heapSize = heapSize - 1;
	maxHeapify(A, heapSize, 1);
	
	return maximum;
}


bool heapIncreasePriority (Node A[], int heapSize, int i, int newPriority) {
	Node temp;
	
	if (newPriority < A[i].cost) {
		cout << "Error increasing priority: new priority is less than current priority." << endl;
		return false;
	}
	
	A[i].cost = newPriority;
	
	while (i > 1 && A[parent(i)].cost < A[i].cost) {
		temp = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = temp;
		i = parent(i);
	}
	
	return true;
}


// Functions that apply only to a min priority queue:

int minHeapInsert (Node A[], int heapSize, Node newElement) {
	bool success;
	
	heapSize = heapSize + 1;
	A[heapSize] = newElement;
	A[heapSize].cost = INFINITY;			// priorities will always be less than this

	success = heapDecreasePriority (A, heapSize, heapSize, newElement.cost);
	
	if (success)
		return heapSize;
	else
		return -1;
}


Node heapMinimum (Node A[], int heapSize) {
	Node minimum;
	
	if (isEmptyHeap(A, heapSize)) {
		minimum.vertex = -1;
		return minimum;
	}
	
	return A[1];	
}


Node heapExtractMin (Node A[], int heapSize) {
	Node minimum;

	if (isEmptyHeap(A, heapSize)) {
		minimum.vertex = -1;
		return minimum;
	}
	
	minimum = A[1];
	A[1] = A[heapSize];
	heapSize = heapSize - 1;
	minHeapify(A, heapSize, 1);

	return minimum;
}


bool heapDecreasePriority (Node A[], int heapSize, int i, int newPriority) {
	Node temp;
	
	if (newPriority > A[i].cost) {
//		cout << "Error decreasing priority: new priority is greater than current priority." << endl;
		return false;
	}
	
	A[i].cost = newPriority;
	
	while (i > 1 && A[parent(i)].cost > A[i].cost) {
		temp = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = temp;
		i = parent(i);
	}
	
	return true;
}
