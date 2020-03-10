#include <iostream>
#include "NodeTypes.h"
#include "BinaryTree.h"

using namespace std;

BTNode * ceiling(BTNode * root, string key) {
	if(root==NULL)
		return NULL;
	
	if(root->data==key)
		return root;
	
	if(root->data<key)
		return ceiling(root->right,key);
		
	BTNode* leftSub=ceiling(root->left,key);
	
	if(leftSub)
		if(leftSub->data>=key)    //try with comparison with root
			return leftSub;
			
		
	return root;	
	
}


BTNode * contains(BTNode * root, string key) {
	if(!root)
		return NULL;
	
	if(root->data==key)
		return root;
	
	if(key>root->data)
		return contains(root->right,key);
	
	return contains(root->left,key);
	
}


BTNode * deleteNode(BTNode * root, string key) {   //consider also doing recursively a next time
	BTNode* inOrderSuccessor (BTNode*);
	BTNode* contains(BTNode*, string);
	
	BTNode* replace; //in order successor when node has two substrees
	BTNode* node;
	node=contains(root,key);

		
	if(root==NULL)
		return NULL;
		
	if(!node)
		return root;
	


	if(!node->left && !node->right){
		if(node->parent){
			if(node->parent->left==node)
				node->parent->left=NULL;
			else
				node->parent->right=NULL;
		}
		else {
			root=NULL;
		}
		
		delete node;
	}
	else if(!node->left){
		if(node->parent){
			if(node->parent->left==node){
				node->parent->left=node->right;
				node->right->parent=node->parent;
			}
				
			else{
				node->parent->right=node->right;
				node->right->parent=node->parent;
			}
				
				
		}			
		else {
			root=node->right;
			root->parent=NULL;
		}
		
		delete node;	
	} 
		
	else if(!node->right) {
		if(node->parent){
			if(node->parent->left==node){
				node->parent->left=node->left;
				node->left->parent=node->parent;
			}				
			else{
				node->parent->right=node->left;
				node->left->parent=node->parent;
			}
				
		}		
		else {
			root=node->left;
			root->parent=NULL;	
		}
		
		delete node;	
	} 
	
	else {
		replace=inOrderSuccessor(node);
		node->data=replace->data;

		if(replace->parent->left==replace){
			replace->parent->left=replace->right;
			if(replace->right)
				replace->right->parent=replace->parent;
		}			
		else{
			replace->parent->right=replace->right;
			if(replace->right)
				replace->right->parent=replace->parent;
		}
			
		delete replace;
	}
	
	
	
	return root;
					
}


BTNode * deleteMin(BTNode * root){
	BTNode * min(BTNode*);
	
	if(!root)
		return NULL;
	
	BTNode* toDel=min(root);
	
	root=deleteNode(root,toDel->data);
	

	return root;
}


BTNode * deleteMax(BTNode * root){
	BTNode * max(BTNode *);
	if(!root)
		return NULL;
	
	BTNode* toDel=max(root);

	root=deleteNode(root,toDel->data);	
	
	return root;
	
	
}


BTNode * floor(BTNode * root, string key) {
	if(root==NULL)
		return NULL;
	
	if(root->data==key)
		return root;
		
	if(root->data>key)
		return floor(root->left,key);
	
	BTNode* rightSub=floor(root->right,key);
	
	if(rightSub)
		if(rightSub->data<=key)
			return rightSub;
	
	
	return root;
	
}


BTNode * inOrderPredecessor (BTNode * node) {
	BTNode *max(BTNode*);
	if(!node)
		return NULL;
	
	if(node->left){
		node=max(node->left);
		return node;	
	}
	//else	

	BTNode* parent=node->parent;
	while(parent && parent->left==node){
		node=parent;
		parent=node->parent;
	}
	return parent;
}


BTNode * inOrderSuccessor (BTNode * node) {
	BTNode * min(BTNode*);
	
	if(!node)
		return NULL;
	
	if(node->right){
		node=min(node->right);
		return node;

	} 
	//else 
	
	BTNode* parent=node->parent;
	while(parent && parent->right==node){
		node=parent;
		parent=node->parent;
	}
	return parent;			
	
}


BTNode * insert(BTNode * root, string key) {
	BTNode* btn=createBTNode(key);

	
	if(root==NULL){
		return btn;
	}
	
	
	BTNode* node=root;

	while(node->data!=key){
		
		if(key>node->data){
			if(!node->right){
				node->right=btn;
				btn->parent=node;
				return root;	
			}				
			else node=node->right;
		}			
		else{
			if(!node->left){
				node->left=btn;
				btn->parent=node;
				return root;
			}
			else node=node->left;
		}
	}
	return root;
	
}


BTNode * max(BTNode * root) {
	if(!root)
		return NULL;
	while(root->right)
		root=root->right;
	return root;
}


BTNode * min(BTNode * root) {
	if(!root)
		return NULL;
		
	while(root->left!=NULL)
		root=root->left;
	return root;
}



