#include <iostream>
   using namespace std;

#define MAX_VERTICES 100
#define INFINITY 	 INT_MAX

enum Colour {
	WHITE,
	GRAY,
	BLACK
};

struct Edge {
	int child;
	int weight;
	Edge * nextEdge;
};

struct Vertex {
	string ID;
	Colour colour;
	Edge * firstEdge;
};

struct Graph {
	int numVertices;
	Vertex vertices[MAX_VERTICES];
};

Graph * buildGraph (char fileName[]);
void displayGraph (Graph * graph);
int findVertex (Graph * graph, string ID);

void depthFirstTraversal (Graph * graph, int source);
void breadthFirstTraversal (Graph * graph, int source);

bool addEdge (Graph * graph, string u, string v);
bool deleteEdge (Graph * graph, string u, string v);
bool hasEdge (Graph * graph, string u, string v);
bool hasVertex (Graph * graph, string v);
int outDegree (Graph * graph, string v);
int adjacentTo (Graph * graph, string v, string adj[]);

void printAllPaths (Graph * graph, string sourceID, string destID);
