#include <iostream>
#include <fstream>
#include <cstring>
#include "NodeTypes.h"
#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"
#include "BinarySearchTree.h"

#define MaxWordSize 50
using namespace std;


int main () {
	void menu();

 	menu();
	cout<<endl;

	return 0;
}

void menu(){
	BTNode* createBST();
	BTNode* addWordToBST(BTNode*);
	BTNode* deleteWordFromBST(BTNode*);
	void search(BTNode*);
	void traversals(BTNode*);
	void predecessor(BTNode*);
	void successor(BTNode*);
	void compareBSTs(BTNode*);
	void statistics(BTNode*);
	
	char c[3];
	BTNode* bst;
	bst=NULL;

	
	cout<<"Binary Search Tree (BST)"<<endl;
	cout<<"------------------------------------------------------------------------"<<endl<<endl;	
	cout<<"1.	Create BST from Passage"<<endl;
	cout<<"2.	Add Word to BST"<<endl;
	cout<<"3.	Delete Word from BST"<<endl;
	cout<<"4. 	Delete Smallest Word from BST"<<endl;
	cout<<"5.	Delete Largest Word from BST"<<endl;
	cout<<"6.	Search for Word in BST"<<endl;
	cout<<"7.	Traverse BST"<<endl;
	cout<<"8.	What Comes Before Word in BST"<<endl;
	cout<<"9.	What Comes After Word in BST"<<endl;
	cout<<"10.	Compare BSTs"<<endl;
	cout<<"11. 	Statistics"<<endl;
	cout<<"Q. 	Quit"<<endl<<endl;
	
	cout<<"Please enter an option: ";
	cin>>c;
	
	cout<<endl<<endl;
	
	while(strcmp(c,"Q")!=0){
		if(strcmp(c,"1")==0){
			if(bst==NULL)	
				bst=createBST();
			else
				cout<<"BST already exists. Current BST will remain active."<<endl<<endl;
		} 
		else if(strcmp(c,"2")==0){
			bst=addWordToBST(bst);
		}
		else if(strcmp(c,"3")==0){
			bst=deleteWordFromBST(bst);
		}
		else if(strcmp(c,"4")==0){
			bst=deleteMin(bst);
		}
		else if(strcmp(c,"5")==0){
			bst=deleteMax(bst);
		}
		else if(strcmp(c,"6")==0){
			search(bst);
		}
		else if(strcmp(c,"7")==0){
			traversals(bst);
		}
		else if(strcmp(c,"8")==0){
			predecessor(bst);
		}
		else if(strcmp(c,"9")==0){
			successor(bst);
		}
		else if(strcmp(c,"10")==0){
			compareBSTs(bst);
		}
		else if(strcmp(c,"11")==0){
			statistics(bst);
		}
		else if(strcmp(c,"Q")!=0){
			cout<<"Invalid Input. Please re-enter."<<endl<<endl;
		}
		
		cout<<endl<<endl;
		
		cout<<"Binary Search Tree (BST)"<<endl;
		cout<<"------------------------------------------------------------------------"<<endl<<endl;
		cout<<"1.	Create BST from Passage"<<endl;
		cout<<"2.	Add Word to BST"<<endl;
		cout<<"3.	Delete Word from BST"<<endl;
		cout<<"4. 	Delete Smallest Word from BST"<<endl;
		cout<<"5.	Delete Largest Word from BST"<<endl;
		cout<<"6.	Search for Word in BST"<<endl;
		cout<<"7.	Traverse BST"<<endl;
		cout<<"8.	What Comes Before Word in BST"<<endl;
		cout<<"9.	What Comes After Word in BST"<<endl;
		cout<<"10.	Compare BSTs"<<endl;
		cout<<"11. 	Statistics"<<endl;
		cout<<"Q. 	Quit"<<endl<<endl;
		
		cout<<"Please enter an option: ";
		cin>>c;
		cout<<endl<<endl;
		
	}

	
}

BTNode* createBST(){
	bool getWord(ifstream&,char[]);
	BTNode* insert(BTNode*, string);
	BTNode* bst=NULL;
	char choice[40];
	cout<<"Please enter the name of file containing the passage or M (Menu): ";
	cin>>choice;
	
	if(strcmp(choice,"M")!=0){
		ifstream fin(choice);
		
		if(!fin.is_open()){
			cout<<"File not found."<<endl<<endl;
			return NULL;
		}
		
		string word;
		char cstr[MaxWordSize+1];

		while(getWord(fin,cstr)){
			word=cstr;
			bst=insert(bst,word);
		}
		
		fin.close();
	}
	
	return bst;				
}

bool getWord(ifstream& fin, char cstr[]){
	
	char c;
	fin>>c;
	int i=0;
	
	fin>>noskipws;
	while(!fin.eof() && !((c>='A' && c<='Z') || (c>='a' && c<='z'))){
		fin>>c;
	}
	if(fin.eof()){
		cstr[i]='\0';
		return false;
	}
	
	while(!fin.eof() && ((c>='A' && c<='Z') || (c>='a' && c<='z'))){
		cstr[i++]=tolower(c);
		fin>>c;
	}
	cstr[i]='\0';
	
	return true;
	
}

BTNode* addWordToBST(BTNode* bst){
	char temp[MaxWordSize+1];
	char c;
	string word;
	
	cin>>noskipws;
	cout<<"Please enter the word to insert in the BST or M (Menu): ";
	cin>>c;
	

	while(!((c>='A' && c<='Z') || (c>='a' && c<='z')))
		cin>>c;
	
	bool flag=false;
	if(c=='M')
		flag=true;
	
	int i=0;
	while(i<MaxWordSize && ((c>='A' && c<='Z') || (c>='a' && c<='z'))){
		temp[i++]=tolower(c);
		cin>>c;
	}	

	temp[i]='\0'; 
	
	word=temp;
	if(!(flag && word=="m"))
		bst=insert(bst,word);
	cin.sync();   // ignore any other word inputted, since we can only accept one at a time
	cin>>skipws; //set back flag
	
	return bst;
}

BTNode* deleteWordFromBST(BTNode* bst){
	string word;
	cout<<"Please enter the word to delete from the BST or M (Menu): ";
	cin>>word;
	if(word!="M")
		bst=deleteNode(bst,word);
	return bst;
}

void search(BTNode* bst){
	string word;
	cout<<"Please enter a word to search for or M (Menu): ";
	cin>>word;
	cout<<endl;
	if(word!="M"){
		if(contains(bst,word))
			cout<<word<<" is present in the BST."<<endl<<endl;
		else
			cout<<word<<" is not present in the BST."<<endl<<endl;
	}
	
}

void traversals(BTNode* bst){
	cout<<endl<<endl<<endl;
	cout << "PreOrder Traversal of BST (Non-recursive version): " << endl;	
	preOrderIterative(bst);
	cout << endl << endl;
		
	cout << "InOrder Traversal of BST (Non-recursive version): " << endl;
	inOrderIterative (bst);
	cout<<endl<<endl;
	
	cout << "PostOrder Traversal of BST (Non-recursive version): " << endl;
	postOrderIterative (bst);
	cout << endl << endl;
	
	cout << "LevelOrder Traversal of BST (Non-recursive version): " << endl;
	levelOrder(bst);
	cout << endl << endl;
	
	
}

void predecessor(BTNode* bst){
	string word;
	cout<<"Please enter a word to search for: ";
	cin>>word;
	cout<<endl;
	if(contains(bst,word))
		cout<<word<<" is present in the BST."<<endl<<endl;
		
	else if (BTNode* pred=floor(bst,word))
		cout<<"The word that comes immediately before "<< word<<" is: "<<pred->data<<endl<<endl;
		
	else
		cout<<word<<" is not found, and there is no word that comes before it in the BST."<<endl<<endl;
}


void successor(BTNode* bst){
	string word;
	cout<<"Please enter a word to search for: ";
	cin>>word;
	cout<<endl;
	if(contains(bst,word))
		cout<<word<<" is present in the BST."<<endl<<endl;
		
	else if (ceiling(bst,word))
		cout<<"The word that comes immediately after "<< word<<" is: "<<ceiling(bst,word)->data<<endl<<endl;
		
	else
		cout<<word<<" is not found. And there is no word that comes after it in the BST."<<endl<<endl;
	
}

void compareBSTs(BTNode* bst){
	BTNode* bst2=createBST();
	cout<<endl<<endl;
	if(bst2){  // if was equal to NULL, then user would have chosen M to return to main menu
		if(isEqual(bst,bst2)){
			cout<<"BSTs are identical."<<endl<<endl;
		} else {
			
			cout<<"BSTs are not identical."<<endl<<endl;
			cout<<"A list of words that are common to both BSTs: ";
			BTNode* curr;		
			
			int num=0;
			bool found=false;
			curr=min(bst2);
			while(curr){
				if(contains(bst,curr->data)){
					cout<<curr->data<<" ";
					found=true;
					num++;
				} 
				curr=inOrderSuccessor(curr);
			}
			if(!found)
				cout<<"No words are common to both BSTs."<<endl<<endl;
			else
				cout<<endl<<endl;
		
			cout<<"The number of words that are common to both BSTs: "<<num<<endl<<endl;
			if(weight(bst)>weight(bst2))
				cout<<"the 'current' BST is heavier than the other BST."<<endl<<endl;
			else
				cout<<"the 'current' BST is NOT heavier than the other BST."<<endl<<endl;
			

		}
		
	}
		
	
}


void statistics(BTNode* bst){
	cout<<endl;
	
	cout<<"The number of nodes in the tree is: "<<moment(bst)<<endl;
	cout<<"The height of the tree is: "<<height(bst)<<endl;
	cout<<"The width of the tree is: "<<width(bst)<<endl;
	cout<<"The weight of the tree is: "<<weight(bst)<<endl;
	
	cout<<"The smallest word in alphabetical order stored in the binary tree is: ";
	if(min(bst))
		cout<<min(bst)->data<<endl;
	else
		cout<<"Invalid! There is no such word."<<endl;
	
	cout<<"The biggest word in alphabetical order stored in the binary tree is: ";
	if(max(bst))
		cout<<max(bst)->data<<endl;
	else
		cout<<"Invalid! There is no such word."<<endl;
	
	
	
}
