#include <iostream>
#include <cstring>
#include "DataTypes.h"
#include "Heap.h"
#include "PriorityQueue.h"
#include "Graph.h"
#include "Dijkstra.h"

using namespace std;


	
int main() {
	void mainMenu();
	
	mainMenu();
	


	return 0;
	
}
void mainMenu(){
	Graph* createGraph(Graph*);
	void checkOutbound(Graph*);
	void calcOutbound(Graph*);
	void printOutbound(Graph*);
	void checkConnection(Graph*);
	void deleteConnection(Graph*);
	void printAllPathsHub(Graph*);
	void printShortestPath(Graph*);
	void traversals(Graph*);
	
	Graph * graph=NULL;
	

	string choice;
	
	cout<<"Assignment 3: Working with Graphs"<<endl;
	cout<<"------------------------------------------------------------"<<endl<<endl;
	
	cout<<"1. Create Graph from File."<<endl;
	cout<<"2. Does the Airline Fly from Location A?"<<endl;
	cout<<"3. How many Direct Flights from Location A"<<endl;
	cout<<"4. What are the Direct Flights from Location A?"<<endl;
	cout<<"5. Is there a Direct Flight from A to B?"<<endl;
	cout<<"6. Delete Flight from A to B"<<endl;
	cout<<"7. Print All Paths from A to B"<<endl;
	cout<<"8. Shortest Path from A to Other Destinations"<<endl;
	cout<<"9. Perform Breadth First and Depth First Traversal"<<endl;
	cout<<"Q. Quit"<<endl<<endl;
	cout<<"Please enter an option: ";
	cin>>choice;
	cout<<endl<<endl;
	
	while(choice!="Q"){
		if(choice=="1"){
			graph=createGraph(graph);
		}
		
		else if(graph){

			if(choice=="2"){
				checkOutbound(graph);
			}
			else if(choice=="3"){
				calcOutbound(graph);
			}
			else if(choice=="4"){
				printOutbound(graph);
			}
			else if(choice=="5"){
				checkConnection(graph);
			}
			else if(choice=="6"){
				deleteConnection(graph);
			}
			else if(choice=="7"){
				printAllPathsHub(graph);
			}
			else if(choice=="8"){
				printShortestPath(graph);
			}
			else if(choice=="9"){
				traversals(graph);
			}
			
		} else{
			cout<<"Invalid selection. Graph must be created before any other menu option is selected.";
		}
		cout<<endl<<endl<<endl;
		
		cout<<"Assignment 3: Working with Graphs"<<endl;
		cout<<"------------------------------------------------------------"<<endl<<endl;
		
		cout<<"1. Create Graph from File."<<endl;
		cout<<"2. Does the Airline Fly from Location A?"<<endl;
		cout<<"3. How many Direct Flights from Location A"<<endl;
		cout<<"4. What are the Direct Flights from Location A?"<<endl;
		cout<<"5. Is there a Direct Flight from A to B?"<<endl;
		cout<<"6. Delete Flight from A to B"<<endl;
		cout<<"7. Print All Paths from A to B"<<endl;
		cout<<"8. Shortest Path from A to Other Destinations"<<endl;
		cout<<"9. Perform Breadth First and Depth First Traversal"<<endl;
		cout<<"Q. Quit"<<endl<<endl;
		cout<<"Please enter an option: ";
		cin>>choice;
		cout<<endl<<endl;
		
		
		
		cout<<endl<<endl;
	}
	
	
}

Graph* createGraph(Graph* graph){
	char fname[50];
	cout<<"Please enter the name of the file or M (Menu): ";
	cin>>fname;
	if(graph)
		cout<<"There is an existing graph already created. It will continue remain active/current.\n";
	if(!graph && strcmp(fname,"M")!=0)
		graph = buildGraph(fname);
//	displayGraph(graph);
	return graph;
}

void checkOutbound(Graph* graph){
	string input;
	cout<<"Please enter the name of the origin airport: ";
	cin>>input;
	cout<<endl;
	
	
	if(outDegree(graph, input)>0){
		cout<<"Yes, there a flights leaving "<<input<<".\n";
	}else {
		cout<<"There are NO flights leaving "<<input<<".\n";
	}  
}

void calcOutbound(Graph* graph){
	string input;
	cout<<"Please enter the name of the origin airport: ";
	cin>>input;
	cout<<endl;
	int numOutbound=outDegree(graph, input);
	if(numOutbound>0){
		cout<<"There are "<<numOutbound<<" flights leaving "<<input<<"."<<endl;
	} else{
		cout<<"There are 0 flights leaving "<<input<<"."<<endl;
	}
}

void printOutbound(Graph* graph){
	string input;
	cout<<"Please enter the name of the origin airport: ";
	cin>>input;
	cout<<endl;
	string adj[50];
	int numOutbound=adjacentTo(graph, input, adj);
	if(numOutbound>0){
		cout<<"All the flights that leaves "<<input<<" arrive at: ";
		for(int i=0;i<numOutbound;i++){
			cout<<adj[i];
			if(i<numOutbound-1)
				cout<<",";
		}
	} else {
		cout<<"There are no flights leaving "<<input<<"."<<endl;
	}
	cout<<endl;
}

void checkConnection(Graph* graph){
	string origin,destin;
	cout<<"Please enter the origin and destination or M (Menu): ";
	cin>>origin;
	if(origin!="M") {
		cin>>destin;
		cout<<endl;	
		string adj[50];
		int numOutbound=adjacentTo(graph, origin, adj);
		
		int i;
		for(i=0;i<numOutbound;i++){
			if(destin==adj[i])
				break;
		}
		if(i==numOutbound){
			cout<<"There is no Direct Flight from "<<origin<<" to "<<destin<<".\n";
		} else {
			cout<<"Yes, there is a Direct Flight from "<<origin<<" to "<<destin<<".\n";
		}
	} else 
		cout<<endl;
	
}

void deleteConnection(Graph* graph){
	string origin,destin;
	cout<<"Please enter the origin and destination or M (Menu): ";
	cin>>origin;
	if(origin!="M"){
		cin>>destin;
		cout<<endl;
		if(deleteEdge(graph,origin,destin))
			cout<<"Flight from "<<origin<<" to "<<destin<<" has been deleted.\n";
		else 
			cout<<"Flight could not be deleted since it does not exist.\n";
	} else
		cout<<endl;
	
	
}



void printAllPathsHub(Graph* graph){
	string origin,destin;
	cout<<"Please enter the origin and final destination or M (Menu): ";
	cin>>origin;
	if(origin!="M"){
		cin>>destin;
		cout<<endl;
		printAllPaths(graph,origin,destin);
	} 
	else
		cout<<endl;
	
}

void printShortestPath(Graph* graph){
	string origin;
	cout<<"Please enter the origin : ";
	cin>>origin;
	if(hasVertex(graph,origin)){
		int k=findVertex(graph,origin);
		Node shortestPaths[MAX_VERTICES + 1];
		dijkstra (graph, shortestPaths, k);
		printPathsAndCosts (graph, shortestPaths, k);
	} else
		cout<<"Origin airport does not exist.\n";
	cout<<endl;	
}

void traversals(Graph* graph){
	string origin;
	cout<<"Please enter the origin : ";
	cin>>origin;
	if(hasVertex(graph,origin)){
		int index=findVertex(graph,origin);
		depthFirstTraversal(graph,index);
		breadthFirstTraversal(graph,index);
	} else {
		cout<<"Origin airport does not exist.\n";
	}
				
	cout<<endl;	

}
