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
		printf("\n Adjacency list of vertex %d\n head -> ", v);
		while (pCrawl) {
			printf("%d[%d];  ", pCrawl->dest, pCrawl->weight);
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



void getCycles(Graph* graph, Dictionary* cycles)
{
	for (int i = 0; i < graph->V; i++) {
		List* cycleVertexes = newList();
		bool* visited = newVisitedVertexArr(graph);
		getCyclesUtil(graph, cycles, i, i, visited, cycleVertexes);
		free(visited);
	}
}

//function to get cycle from given vertex if exists
void getCyclesUtil(Graph* graph, Dictionary* dict, int startNode, int currNode, bool visited[], List* cycleVertexes)
{
	if (visited[currNode]) {
		if (currNode == startNode) {
			/*List* temp = newList();
			ListNode* curr = cycleVertexes->head;*/
			/*while (curr != NULL) {
				addToList(temp, curr->dest);
				curr = curr->next;
			}*/
			/**temp = *cycleVertexes;*/
			int key = getHash(cycleVertexes);
			if (!containsKey(dict, key)) {
				DictionaryItem* tmp = newDictItem(key, cycleVertexes);
				addToDict(dict, tmp);
			}

		}
		return;
	}
	
	visited[currNode] = true; 

	addToList(cycleVertexes, currNode);
	ListNode* temp = graph->array[currNode].head;

	//dfs algotithm
	while (temp != NULL) {
		getCyclesUtil(graph, dict, startNode, temp->dest, visited, cycleVertexes);
		temp = temp->next;
	}

	visited[currNode] = false;
	removeLastItem(cycleVertexes);
}

void freeGraph(Graph** graph)
{
	for (int i = 0; i < (*graph)->V; i++) {
		freeList(&(*graph)->array[i].head);
	}
	free((*graph)->array);
	free(*graph);
}

void freeList(ListNode** headRef)
{
	if (headRef && *headRef) {
		ListNode* next = (*headRef)->next;
		while (next) {
			ListNode* tmp = next;
			next = next->next;
			free(tmp);
		}
		free(*headRef);
		*headRef = NULL;
	}
}

void freeDict(Dictionary** dict)
{
	DictionaryItem* next = (*dict)->head;
	while (next) {
		DictionaryItem* tmp = next;
		next = next->next;
		freeList(&tmp->value->head);
		free(tmp);
	}
	free(*dict);
}