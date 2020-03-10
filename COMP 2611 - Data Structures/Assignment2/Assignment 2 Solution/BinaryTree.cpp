#include <iostream>
#include "NodeTypes.h"
#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

BTNode * createBTNode (string data) {
	BTNode * newNode;
	
	newNode = new BTNode;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	
	return newNode;

}


void visitNode (BTNode * btNode) {
	cout << btNode->data << " ";
	
}


int height (BTNode * root) {
	
	if(root==NULL)
		return 0;
		
	Queue* q=initQueue();
	BTNode* data;
	
	int height=0;
	int remNodesonLvl=0;
	
	
	enqueue(q,root);	
	while(!isEmptyQueue(q)){
		remNodesonLvl=sizeQueue(q);
		
		while(remNodesonLvl>0){
			data=dequeue(q);
			remNodesonLvl--;
			
			if(data->left!=NULL)
				enqueue(q,data->left);
			
			if(data->right!=NULL)
				enqueue(q, data->right);
			
		}
		height++;
		
	}
	
	return height;
}


void inOrderIterative(BTNode * root) {
	BTNode* curr;
	Stack* s;
	
	s=initStack();	
	curr=root;
	
	
		
	while(curr!=NULL || !isEmptyStack(s)){
		
		while(curr!=NULL){
			push(s,curr);
			curr=curr->left;
		}
		
		curr=pop(s);    //if execution reaches this point, there must be something in the stack 
		visitNode(curr);
		curr=curr->right;
			
	}
	
	
	
	
}


bool isEmptyTree (BTNode * root) {
	return root==NULL;
}


bool isEqual (BTNode * root1, BTNode * root2) {
	if(root1==NULL && root2==NULL)
		return true;
	
	else if(root1!=NULL && root2!=NULL){
		return (root1->data==root2->data && isEqual(root1->left,root2->left) && isEqual(root1->right,root2->right));
				
	}
	return false;
}


void levelOrder (BTNode * root) {
	
	if(root!=NULL){
		Queue* q=initQueue();
		BTNode* curr;
		
		enqueue(q,root);
		while(!isEmptyQueue(q)){
			curr=dequeue(q);
			visitNode(curr);
			
			if(curr->left!=NULL)
				enqueue(q,curr->left);
			
			if(curr->right!=NULL)
				enqueue(q,curr->right);			
		}		
	}
}


int moment(BTNode * root) {
	if(root==NULL)
		return 0;
	
	return 1+moment(root->left)+moment(root->right);
}



void preOrderIterative (BTNode * root) {
	Stack* s=initStack();
	BTNode* curr;
	
	curr=root;
	while(curr!=NULL || !isEmptyStack(s)){
		
		while(curr!=NULL){
			visitNode(curr);
			push(s,curr);
			curr=curr->left;
		}
		
		curr=pop(s);
		curr=curr->right;

	}
	
}


void postOrderIterative (BTNode * root) {
	if(root==NULL)
		return;
		
	Stack* s1=initStack();
	Stack* s2=initStack();
	BTNode* temp;
	
	push(s1,root);
	while(!isEmptyStack(s1)){
		temp=pop(s1);
		push(s2,temp);
		
		if(temp->left)
			push(s1,temp->left);
		
		if(temp->right)
			push(s1,temp->right);
	}
	
	while(!isEmptyStack(s2)){
		temp=pop(s2);
		visitNode(temp);
	}
}


int weight(BTNode * root) {
	if(root==NULL)
		return 0;
		
	if(root->left==NULL && root->right==NULL)
		return 1;
	
	return weight(root->left) + weight(root->right);

}


int width(BTNode * root) {
	if(root==NULL)
		return 0;
		
	Queue* q=initQueue();
	BTNode* curr;
	int max=-1;
	int numNodesatLvl;
	
	enqueue(q,root);
	while(!isEmptyQueue(q)){
		numNodesatLvl=sizeQueue(q);
		if(numNodesatLvl>max)
			max=numNodesatLvl;
		
		while(numNodesatLvl>0){
			curr=dequeue(q);
			numNodesatLvl--;
			
			if(curr->left!=NULL)
				enqueue(q,curr->left);
			
			if(curr->right!=NULL)
				enqueue(q,curr->right);
		}		
		
	}
	
	
	return max;
}
