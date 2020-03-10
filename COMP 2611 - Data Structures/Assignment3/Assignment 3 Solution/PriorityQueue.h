/*
   This header file contains functions that operate on both
   min priority queues and max priority queues.
*/

// Functions that are common to both min priority queues
// and max priority queues:
   
bool isEmptyHeap (Node A[], int heapSize);
int searchHeap (Node A[], int heapSize, int vertex);

// Functions that apply only to a max priority queue:

int maxHeapInsert (Node A[], int heapSize, Node newElement);
Node heapMaximum (Node A[], int heapSize);
Node heapExtractMax (Node A[], int heapSize);
bool heapIncreasePriority (Node A[], int heapSize, int i, int newPriority);

// Functions that apply only to a min priority queue:

int minHeapInsert (Node A[], int heapSize, Node newElement);
Node heapMinimum (Node A[], int heapSize);
Node heapExtractMin (Node A[], int heapSize);
bool heapDecreasePriority (Node A[], int heapSize, int i, int newPriority);

