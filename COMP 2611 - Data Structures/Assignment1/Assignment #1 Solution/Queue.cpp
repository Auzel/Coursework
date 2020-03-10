#include <iostream>
#include <cstdlib>
#include "NodeType.h"
#include "Queue.h"

using namespace std;


Queue * initQueue () {
	Queue* q = new Queue;
	q->top = NULL;
	q->last = NULL;
	return q;
}


bool isEmptyQueue (Queue * q) {
	if (q->top == NULL)
		return true;
	else
		return false;
}


int sizeQueue (Queue * q) {

	Node * curr;
	int size;

	curr = q->top;
	size = 0;

	while (curr != NULL) {
		curr = curr->next;
		size = size + 1;
	}

	return size;
}

void enqueue (Queue * q, char data) {
	Node * newElement = new Node;
	newElement->data = data;
	newElement->next = NULL;
	
	if (isEmptyQueue(q)) {
	
		q->top = newElement;
		q->last = newElement;
		
	}
	else {
			
		q->last->next = newElement;
		q->last = newElement;
	}
	

}


char dequeue (Queue * q) {
	if (isEmptyQueue(q))
		return ROGUEVALUE; 				// to indicate error if dequeuing from an empty queue

	Node * toRemove;
	char data;

	toRemove = q->top;
	data = toRemove->data;
	q->top = toRemove->next;
	if (q->top == NULL)
		q->last = NULL;

	delete toRemove;

	return data;
}

char peekQueue (Queue * q) {
	if (isEmptyQueue(q))
		return ROGUEVALUE; 				// to indicate error if dequeuing from an empty queue

	return q->top->data;
}

