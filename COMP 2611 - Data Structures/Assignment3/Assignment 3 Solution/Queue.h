struct QueueNode {
	int data;
	QueueNode * next;	
};

struct Queue {
	QueueNode * top;
	QueueNode * last;
};

Queue * initQueue ();
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, int data);
int dequeue (Queue * q);
