#include <iostream>
#include <fstream>
#include "DataTypes.h"
#include "Queue.h"
#include "Graph.h"
#include "Dijkstra.h"
   using namespace std;
   
int time=0;

Vertex newVertex (string ID) {
	
	Vertex vertex;
	
	vertex.ID = ID;
	vertex.colour = WHITE;
	vertex.firstEdge = NULL;
	
	return vertex;
}


Edge * newEdge (int child, int weight) {
	
	Edge * edge = new Edge;
	
	edge->child = child;
	edge->weight = weight;
	edge->nextEdge = NULL;
	
	return edge;
}


int findVertex (Graph * graph, string ID) {
	
	for (int i = 1; i <= graph->numVertices; i = i + 1) {
		if (graph->vertices[i].ID == ID)
			return i; 	// return location of vertex in array
	}
	
	return -1;			// -1 indicates that a vertex with the ID was not found.
}


// This function adds an edge X->Y to a graph, with a given weight.

void addEdge (Graph * graph, string X_ID, string Y_ID, int weight) {
	
	int X_Location, Y_Location;
	Edge * edge;
	
	X_Location = findVertex (graph, X_ID);
	Y_Location = findVertex (graph, Y_ID);
	
	if (X_Location == -1 || Y_Location == -1) {
		cout << "Edge does not exist: " << X_ID << "->" << Y_ID << endl;
		exit(1);
	}
	
	edge = newEdge (Y_Location, weight);
	
	Edge * firstEdge;
	Edge * previous;
	Edge * current;
	
	firstEdge = graph->vertices[X_Location].firstEdge;
	previous = current = firstEdge;
	
	while (current != NULL && Y_ID > graph->vertices[current->child].ID) {
		previous = current;
		current = current->nextEdge;
	}
	
	if (previous == current) {
		edge->nextEdge = graph->vertices[X_Location].firstEdge;
		graph->vertices[X_Location].firstEdge = edge;
	}
	else {
		edge->nextEdge = current;
		previous->nextEdge = edge;
	}
	
}

	
Graph * buildGraph (char fileName[]) {
	
	ifstream graphFile;
	
	graphFile.open (fileName);
	
	if (!graphFile.is_open()) {
		cout << "Error opening graph input file : " << fileName;
		cout << ". Aborting ..." << endl;
		return NULL;
	}
	
	Graph * newGraph = new Graph;
	
	// Read number of vertices from the first line of the file.

	int numVertices;
	
	graphFile >> numVertices;

	newGraph->numVertices = numVertices;
	
	// Read name of each vertex (vertexID) from the second line of the file
	//  and store in array of vertices.
	
	string vertexID; 
	
	for (int v = 1; v <= numVertices; v = v + 1) {
		graphFile >> vertexID;
		newGraph->vertices[v] = newVertex (vertexID);
	}
	
	// Read edges from each vertex from remaining lines of the file and
	//  store in linked list of edges connected to array location for the
	//  "parent" vertex. 
	
	int numEdges;			// number of edges from vertexID
	string adjacentID;		// ID of adjacent vertex
	int edgeWeight;			// weight of edge
	
	for (int v = 1; v <= numVertices; v = v + 1) {
		graphFile >> vertexID >> numEdges;
		for (int e = 1; e <= numEdges; e = e + 1) {
			graphFile >> adjacentID >> edgeWeight;
			addEdge (newGraph, vertexID, adjacentID, edgeWeight);
		}
	}
	
	graphFile.close();
	
	return newGraph;
	
}


void displayGraph (Graph * graph) {
	int numVertices;
	Edge * edge;
	
	cout << "The following are the nodes and edges of the graph:" << endl << endl;
	
	numVertices = graph->numVertices;
	
	for (int v = 1; v <= numVertices; v = v + 1) {
		cout << graph->vertices[v].ID << ": ";
		edge = graph->vertices[v].firstEdge;
		while (edge != NULL) {
			cout << graph->vertices[edge->child].ID << " " << edge->weight << " ";
			edge = edge->nextEdge;
		}
		cout << endl;
	}
	
}


void dfs (Graph * graph, int vertex) {

	cout<<graph->vertices[vertex].ID<<" ";
	
	graph->vertices[vertex].colour=GRAY;
	Edge* e=graph->vertices[vertex].firstEdge;
	while(e!=NULL){
		if(graph->vertices[e->child].colour==WHITE)
			dfs(graph,e->child);
		e=e->nextEdge;
	}
	graph->vertices[vertex].colour=BLACK;
	
}


void depthFirstTraversal (Graph * graph, int source) {
	int j;
	int s=source;
	for(j=1;j<=graph->numVertices;j++){
		graph->vertices[j].colour=WHITE;
	}
	
	cout<<"Depth-first traversal starting from "<<graph->vertices[s].ID<<": ";
	
	dfs(graph,s);
	
	for(j=1;j<=graph->numVertices;j++){
		if(graph->vertices[j].colour==WHITE)
			dfs(graph,j);
	}
	
	cout<<endl;

}


void breadthFirstTraversal (Graph * graph, int source) {
	int j;
	int s=source;
	
	for(j=1;j<=graph->numVertices;j++){
		graph->vertices[j].colour=WHITE;
	}
	
	graph->vertices[s].colour=GRAY;
	Queue* q=initQueue();
	enqueue(q,s);
	cout<<"Breadth-first traversal starting from "<<graph->vertices[s].ID<<": ";
	
	while(!isEmptyQueue(q)){
		int index=dequeue(q);
		cout<<graph->vertices[index].ID<< " ";
		
		Edge* e=graph->vertices[index].firstEdge;
		while(e!=NULL){
			if(graph->vertices[e->child].colour==WHITE){
				graph->vertices[e->child].colour=GRAY;
				enqueue(q,e->child);
			}
			e=e->nextEdge;
		}
		graph->vertices[index].colour=BLACK;
	}
	cout<<endl;
}


bool hasEdge (Graph * graph, string X_ID, string Y_ID) {
	int u=findVertex(graph, X_ID);
	int v=findVertex(graph, Y_ID);
	
	if(u==-1 || v==-1)
		return false;
	
	Edge* e=graph->vertices[u].firstEdge;

	while(e!=NULL){
		if(e->child==v)
			return true;
		e=e->nextEdge;
	}
	return false;
	
}


bool deleteEdge (Graph * graph, string X_ID, string Y_ID) {
	int u=findVertex(graph, X_ID);
	int v=findVertex(graph, Y_ID);
	
	if(u==-1 || v==-1)
		return false;
	
	Edge* e=graph->vertices[u].firstEdge;
	Edge* prev;

	while(e!=NULL){
		if(e->child==v){
			if(graph->vertices[u].firstEdge ==e){
				graph->vertices[u].firstEdge=e->nextEdge;
			} else {
				prev->nextEdge=e->nextEdge;
			}
			delete e;
			return true;
		} else{
			prev=e;
			e=e->nextEdge;	
		}
	}
	return false;
}


bool hasVertex (Graph * graph, string X_ID) {
	if(findVertex(graph,X_ID)>0)
		return true;
	return false;
}


int outDegree (Graph * graph, string v) {

	int index=findVertex(graph, v); 

	if(index==-1)
		return -1;
	
		
	Edge* e=graph->vertices[index].firstEdge;
	int count=0;
	while(e!=NULL){
		count++;
		e=e->nextEdge;
	} 
	
	return count; 
	
	
}


int adjacentTo (Graph * graph, string X_ID, string adj[]) {
	int v=findVertex(graph, X_ID);
	
	if(v==-1)
		return -1;
	
		
	Edge* e=graph->vertices[v].firstEdge;
	int count=0;
	while(e!=NULL){
		adj[count]=graph->vertices[e->child].ID;
		count++;
		e=e->nextEdge;
	}
	
	return count;		
}
	
int printPaths(Graph* graph, int u, int v, Node vertices[]){
	graph->vertices[u].colour=GRAY;
	Edge* e=graph->vertices[u].firstEdge;
	while(e!=NULL){
		if(graph->vertices[e->child].colour==WHITE){
			vertices[e->child].predecessor=u;
			if(e->child==v){
				cout<<"Path ";
				++time;
				cout<<time<<" : ";
				printPath (graph, vertices, e->child);  // from dijkstras.cpp
				cout<<endl;
			}
				
			printPaths(graph,e->child,v,vertices);                   //recursive call
		} //else 
			
		e=e->nextEdge;
	}
	graph->vertices[u].colour=WHITE;
	
	return time;
	
}
void printAllPaths (Graph * graph, string sourceID, string destID) {
	int u=findVertex(graph, sourceID);
	int v=findVertex(graph, destID);
	
	if(u==-1 || v==-1){
		cout<<"Invalid origin or destination airport. Cannot find path\n";
		return;
	}
	
	Node vertices[MAX_VERTICES];
	for(int i=1;i<=graph->numVertices;i++){
		vertices[i].vertex=i;
		vertices[i].predecessor=0;
	}	
	
	for(int i=0;i<graph->numVertices;i++){
		graph->vertices[i].colour=WHITE;
	}
	time=0;
	int numPaths=printPaths(graph,u,v,vertices);
	
	if(numPaths==0)
		cout<<"No Path from "<<sourceID<<" and "<<destID<<".\n";

}

