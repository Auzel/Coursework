#include <iostream>
#include <cstdlib>
#include "NodeType.h"
#include "Stack.h"

using namespace std;


Stack * initStack () {
	Stack * s = new Stack;
	s->top = NULL;
	return s;
}


bool isEmptyStack (Stack * s) {
	if (s->top == NULL)
		return true;
	else
		return false;
}


void push (Stack * s, char data) {
	Node * newElement = new Node;
	newElement->data = data;
	newElement->next = s->top;
	s->top = newElement;
}


char  pop (Stack * s) {
	if (isEmptyStack(s))
		return ROGUEVALUE; 				// to indicate error if popping from an empty stack

	Node * toRemove;
	char data;

	toRemove = s->top;
	data = toRemove->data;
	s->top = s->top->next;
	delete toRemove;

	return data;
}

char peekStack(Stack *s){
	if (isEmptyStack(s))
		return ROGUEVALUE; 				// to indicate error if popping from an empty stack
	
	return s->top->data;	
}
