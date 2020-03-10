#define ROGUEVALUE ' '
struct Queue {
	Node * top;
	Node * last;
};

Queue * initQueue ();
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, char data);
char dequeue (Queue * q);
char peekQueue(Queue *q);
