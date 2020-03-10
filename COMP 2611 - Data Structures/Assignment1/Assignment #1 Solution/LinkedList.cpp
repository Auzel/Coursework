#include <iostream>
#include <cstdlib>
#include <stdbool.h>
#include "NodeType.h"
#include "LinkedList.h"
#include "Stack.h"

using namespace std;


Node * createNode (char c) {
   Node * newNode;

   newNode = (Node *) malloc (sizeof (Node));
   newNode->data = c;
   newNode->next = NULL;
   return newNode;
}



Node * insertAtHead (Node * top, char c) {
   Node * newNode;

   newNode = createNode (c);
   newNode->next = top; // this works even if the list is empty
   top = newNode;
   return top;          // return pointer to new head of list
}

Node * getLast (Node * top) {

   Node * curr, * last;

   last = NULL;
   curr = top;
   while (curr != NULL) {
      last = curr;
      curr = curr->next;
   }

   return last;
}


Node * insertAtTail (Node * top, char c) {
   Node * newNode, * lastNode;

   newNode = createNode (c);
   lastNode = getLast (top);

   if (lastNode == NULL)   // linked list has no elements
      top = newNode;       // let top be the address of the node just created
   else                    // let lastNode refer to the node just created
      lastNode->next = newNode;

   return top;             // return top in case it got changed
}


Node * recursiveCopy(Node *top){

	if(top==NULL)
		return top;
	
	Node* np=new Node;
	np->data=top->data;
	np->next=recursiveCopy(top->next);
	return np;
}

Node * removeAll (Node *top, char c){
	
	if(top==NULL)
		return NULL;
	else if (top->data==c){
		Node* next=top->next;
		delete top;
		return removeAll(next,c);
	}
	else {
		top->next=removeAll(top->next,c);
		return top;
	}
	
	
}

Node * nonRecRemoveAll (Node *top, char c){
	
	Node*curr=top;
	Node* prev=NULL;

	while(curr!=NULL){
		
		if(curr->data==c){
			if(curr==top){				
				top=top->next;
			} else {
				prev->next=curr->next;
			}
			delete curr;
		}
		prev=curr;
		curr=curr->next;	
	
	}
	
	return top;
	
}

Node* addRest(Node* newTop, Node* last, Node* list){
	Node* np;
	
	while(list!=NULL){
		np=new Node;
		np->data=list->data;
		
		if(newTop==NULL)
			newTop=np;
		else 
			last->next=np;
		
		last=np;
		
		list=list->next;
	}

	return newTop;

}

Node * nonRecursiveMerge (Node *top1, Node *top2){

	Node* newTop=NULL;
	Node* last;
	Node* np;
	
	while(top1!=NULL && top2!=NULL){
		
		if(top1->data <top2->data){
			np=new Node;
			np->data=top1->data;
			top1=top1->next;
		}
		else {
			np=new Node;
			np->data=top2->data;
			top2=top2->next;
		}
		
		if(newTop==NULL){
			newTop=np;
		} else {
			last->next=np;
		}
		
		last=np;
	}
	
	if(top1!=NULL)
		addRest(newTop,last,top1);
	else
		addRest(newTop,last,top2);
		
	
}

int compare (Node * top1, Node * top2){
	
	while(top1!=NULL && top2!=NULL){
		if(top1->data<top2->data)
			return -1;
		else if(top1->data>top2->data)
			return 1;
	
		top1=top1->next;
		top2=top2->next;
	}
	
	if(top1==NULL && top2==NULL)
		return 0;
		
	if(top1!=NULL)
		return 1;
	
	return -1;
}

void nonRecursivePrint(Node * top){
	
	Stack* s=initStack();
	
	while(top!=NULL){
		push(s,top->data);
		top=top->next;
	}
	
	while(!isEmptyStack(s))
		cout<<pop(s);
	
}
	
	
Node * nthNodeFromEnd(Node* top, int n){
	
	// consider that nth from back means size-nth+1 from front

	int size=0;
	Node* curr=top;
	while(curr!=NULL){
		size++;
		curr=curr->next;
	}
	
	curr=top;
	int i=0;
	while(curr!=NULL){
		i++;
		if(i==size-n+1)
			return curr;
		else 
			curr=curr->next;
	}
	
	return NULL;
	
}

Node * segregateEvenOdd(Node * top){
	
	Node* topE=NULL;
	Node* topO=NULL;
	Node* lastE;
	Node* lastO;
	while(top!=NULL){
	//alternatively insert at head and use an advCurr
		if(top->data%2==0){
			
			if(topE==NULL)
				topE=top;
			else
				lastE->next=top;
			lastE=top;
		}	
		else {
			if(topO==NULL)
				topO=top;
			else
				lastO->next=top;
			lastO=top;
		}
		top=top->next;
	}

	//keep separate list
	lastE->next=NULL;
	lastO->next=NULL;
	
	//merge list
	if(topE==NULL)
		return topO;
	
	if(topO==NULL)
		return topE;
	
	lastE->next=topO;
	
	return topE;

	
}


Node* printList(Node* top){
	while(top!=NULL){
		cout<<top->data;
		top=top->next;
	}
}
