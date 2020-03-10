struct Queue {
	Node * top;
	Node * last;
};

Queue * initQueue ();
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, BTNode * data);
BTNode * dequeue (Queue * q);
