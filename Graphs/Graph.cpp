#include "Header.h"

/*A utility function to create a new adjacency list node*/



Graph* createGraph(int V)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;


	//create an array of adjaency lists
	graph->array = (List*)malloc(V * sizeof(List));

	// Initialize each adjacency list as empty by
	// making head as NULL
	for (int i = 0; i < V; ++i) {
		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight)
{
	// Add an edge from src to dest.  A new node is
	// added to the adjacency list of src.  The node
	// is added at the beginning
	ListNode* node = newListNode(dest, weight);
	node->next = graph->array[src].head;
	graph->array[src].head = node;

}

//An utility function to print the adjaency list 
// representation of the graph
void printGraph(Graph* graph)
{
	for (int v = 0; v < graph->V; v++) {
		ListNode* pCrawl = graph->array[v].head; //crawl -повзунок))
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

//create bool array based on vertex count
bool* newVisitedVertexArr(Graph* graph)
{
	bool* result = (bool*)malloc(sizeof(bool) * graph->V);
	for (int i = 0; i < graph->V; i++) {
		result[i] = false;
	}
	return result;
}

//function to detect cycle in graph
bool isCyclic(Graph* graph)
{
	bool* visited = newVisitedVertexArr(graph);
	bool* recStack = newVisitedVertexArr(graph);
	for (int i = 0; i < graph->V; i++) {
		if (isCyclicUtil(graph, i, visited, recStack)) {
			return true;

		}
	}
	return false;
}

bool isCyclicUtil(Graph* graph, int startVertex, bool visited[], bool recStack[])
{
	if (recStack[startVertex])
		return true;
	if (visited[startVertex])
		return false;
	visited[startVertex] = recStack[startVertex] =  true;
	ListNode* adjList = graph->array[startVertex].head;
	ListNode* temp = adjList;
	while (temp != NULL) {
		if (isCyclicUtil(graph, temp->dest, visited, recStack)) {
			return true;
		}
		temp = temp->next;
	}
	recStack[startVertex] = false;

	return false;
}

//function to get cycle from given vertex if exists
void GetCycle(Graph* graph, Dictionary* dict, int start, int node, bool visited[], List* mark)
{
	static int pos = 0;
	if (visited[node]) {
		if (node == start) {
			List* temp = newList();
			ListNode* curr = mark->head;
			while (curr != NULL) {
				AddToList(temp, curr->dest);
				curr = curr->next;
			}

			int key = getHash(temp);
			if (!containsKey(dict, key)) {
				DictionaryItem* tmp = newDictItem(key, mark);
				addToDict(dict, tmp);
			}

		}
		return;
	}
	
	visited[node] = true;
	ListNode* curr = mark->head;


	AddToList(mark, node);
	ListNode* adjList = graph->array[node].head;
	ListNode* temp = adjList;

	//dfs algotithm
	while (temp != NULL) {
		GetCycle(graph, dict, start, temp->dest, visited, mark);
		temp = temp->next;
	}

	visited[node] = false;
	removeLastItem(mark);
}
