/* 
   This header file declares functions that operate on both
   max-heaps and min-heaps. 
*/
	
// Functions that are common to both max-heaps and min-heaps
  
int parent (int i);
int leftChild(int i);
int rightChild (int i);

// Functions that apply only to a max-heap

void maxHeapify (Node A[], int heapSize, int i);
void buildMaxHeap(Node A[], int lengthA);

// Functions that apply only to a min-heap

void minHeapify (Node A[], int heapSize, int i);
void buildMinHeap(Node A[], int lengthA);
