#include <fstream>
#include <iostream>
#include <cstdlib>
#include "NodeType.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <ctime>
using namespace std;



int main (){
	bool readFromFile(ifstream&, Queue*, Queue*);
	bool checkStackPermutation(Queue*, Queue*);
	void testLinkListOps();
	
	ifstream fin("strings.txt");
	if(!fin.is_open()){
		cout<<"File is unable to open"<<endl;
		return -1;
	}
	
	cout<<"String1\t\t\tString2\t\t\tStack Permutation Possible?"<<endl;
	cout<<"=========================================================================="<<endl;
	while(!fin.eof()){
		Queue* input, *output;
		input=initQueue();
		output=initQueue();
		if(readFromFile(fin, input, output)){
			if(checkStackPermutation(input,output))
				cout<<"True"<<endl;
			else
				cout<<"False"<<endl;	
		
		}
		
	}	
	fin.close();
	
	cout<<endl<<endl<<endl<<endl;
	cout<<"\t\t\tTesting of Linked List Functions"<<endl;
	cout<<"========================================================================="<<endl;
	testLinkListOps();
	
	
	return 0;
}

bool readFromFile(ifstream& fin, Queue* input, Queue* output){
	

	char ch;
	fin>>noskipws;
	
	fin>>ch;	
	
	if(fin.eof())
		return 0;
	
	int j;

	for(int i=0; i<2;i++){
		while(!fin.eof() && (ch==' '||ch=='\n' || ch=='\t'))
			fin>>ch;
		j=0;
		while (!fin.eof() && (ch!=' ' && ch!='\n' && ch!='\t') ){
			j++;
			cout<<ch;
			if(i==0)
				enqueue(input, ch);
			else
				enqueue(output, ch);
				
			fin>>ch;
		}	
		cout<<"\t\t";	
		if(j<7)	
			cout<<"\t";
	}
		
	return 1;
	
}

bool checkStackPermutation (Queue* input, Queue* output){
	char c;
	
	Stack* s=initStack();
	while(!isEmptyQueue(input)){
		c=dequeue(input);
		
		if(c==peekQueue(output)){
			dequeue(output);
			
			while(!isEmptyStack(s) && peekStack(s)==peekQueue(output)){
					pop(s);
					dequeue(output);
					
			}
		}
		else 
			push(s,c);
	}
	
	return (isEmptyQueue(input) && isEmptyStack(s) && isEmptyQueue(output));

}

void testLinkListOps(){
	srand(time(0));
	Node* top1=NULL;
	Node* top2=NULL;

	//generate random lowercase and uppercase alphabetical characters for linked list
	for(int i=0;i<10;i++){
		int j=0;
		if(rand()%2==0)
			j=32;
		top1=insertAtTail(top1,(char) 'a'+ rand()%('z'-'a'+1) - j );
	}
		
	
	//generate random lowercase alphabetical characters for linked list
	for(int i=0;i<15;i++){
		int j=0;
		if(rand()%2==0)
			j=32;
		top2=insertAtTail(top2,(char) 'a'+ rand()%('z'-'a'+1) -j );
	}
	
	Node* copy1, *copy2;
	copy1=recursiveCopy(top1);
	copy2=recursiveCopy(top2);
	//1. RecursiveCopy
	cout<<endl<<endl;
	cout<<"Recursive Copy"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(top2);	
	cout<<"\t\tOutput Linked List: ";
	printList(copy2);
	
	
	//2. RemoveAll
	char ch='a'+ rand()%('z'-'a'+1);
	cout<<endl<<endl;
	cout<<"Remove All Recursive '"<<ch<<"' occurrences"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(copy2);
	copy2=removeAll(copy2,ch);
	cout<<"\t\tOutput Linked List: ";
	printList(copy2);
	
	//3. nonRecRemoveAll
	copy2=recursiveCopy(top2);
	cout<<endl<<endl;
	cout<<"Remove All Non-Recursive '"<<ch<<"' occurrences"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(copy2);
	copy2=nonRecRemoveAll(copy2,ch);
	cout<<"\t\tOutput Linked List: ";
	printList(copy2);
	
	//4. nonRecursiveMerge
	Node *sort1=NULL, *sort2=NULL;
	for(int i='a';i<='c';i++)	
		sort1=insertAtTail(sort1,(char)i);
	for(int i='l';i<='p';i++)	
		sort1=insertAtTail(sort1,(char)i);
		
	for(int j='d';j<='k';j++)
		sort2=insertAtTail(sort2,(char)j);
	for(int j='o';j<='t';j++)
		sort2=insertAtTail(sort2,(char)j);
		
	cout<<endl<<endl;
	cout<<"Non-Recursive Merge"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List1: ";
	printList(sort1);
	cout<<"\tLinked List2: ";
	printList(sort2);
	Node* merge=nonRecursiveMerge(sort1,sort2);
	cout<<"\t\tOutput Linked List: ";
	printList(merge);
	
	//5. Compare
	copy2=recursiveCopy(top2);
	cout<<endl<<endl;
	cout<<"Compare"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List1: ";
	printList(copy1);
	cout<<"\tLinked List2: ";
	printList(copy2);
	int test=compare(copy1,copy2);
	cout<<"\t\tReturn Value: "<<test;
	
	//6. NonRecursivePrint
	cout<<endl<<endl;
	cout<<"Non-Recursive Print"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(copy1);
	cout<<"\t\tOutput Linked List from End: ";
	nonRecursivePrint(copy1);
	
	//7. nthNodeFromEnd
	int n=1+rand()%10;
	cout<<endl<<endl;
	cout<<"nth Node from End, where n="<<n<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(copy1);
	Node* temp= nthNodeFromEnd(copy1, n);
	if(temp==NULL)
		cout<<"\t\tInvalid nth node supplied";
	else
		cout<<"\t\tnth Node from End is : ->"<<temp->data;
		
	//8.*segregateEvenOdd
	cout<<endl<<endl;
	cout<<"Segregate Even and Odd"<<endl;
	cout<<"==================="<<endl;
	cout<<"Input Linked List: ";
	printList(copy2);
	cout<<"\t\tOutput Linked List with segregated Even and Odd: ";
	copy2=segregateEvenOdd(copy2);
	printList(copy2);

	cout<<endl<<endl;
	
	
	
}


