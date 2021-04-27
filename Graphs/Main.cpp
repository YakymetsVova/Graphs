#include "Header.h"

int main()
{
	int V = 7;
	Graph* graph = createGraph(V);
	addEdge(graph, 0, 1, 5);
	addEdge(graph, 1, 2, 6);
	addEdge(graph, 2, 4, 8);
	addEdge(graph, 4, 2, 3);
	addEdge(graph, 2, 6, 5);
	addEdge(graph, 2, 3, 2);
	addEdge(graph, 6, 1, 11);
	addEdge(graph, 1, 6, 12);
	addEdge(graph, 6, 3, 4);
	addEdge(graph, 3, 0, 1);

	/*addEdge(graph, 0, 1, 5);
	addEdge(graph, 1, 2, 6);
	addEdge(graph, 2, 3, 7);*/


	printGraph(graph);
	bool* visited = newVisitedVertexArr(graph);

	Dictionary* cycles = newDictionary();
	for (int i = 0; i < graph->V; i++) {
		List* mark = newList();
		bool* visited = newVisitedVertexArr(graph);
		GetCycle(graph, cycles, i, i, visited, mark);
	}

	if (cycles->head != NULL) {
		printf("\nGraph contains at least one cycle");
		printf("\n\nYour cycles:\n\n");
		printCycles(graph, cycles);
	}
	else
	{
		printf("\n Graph doesn't contain a cycle");
	}
	
	
}

void printCycles(Graph* graph, Dictionary* cycles)
{
	DictionaryItem* curle = cycles->head;
	ListNode* longestPath = cycles->head->value->head;
	int max = -1;

	while (curle != NULL) {
		ListNode* node = curle->value->head;
		ListNode* tmp = graph->array[node->dest].head;
		int sumPath = 0;
		while (node->next != NULL)
		{
			while (tmp->dest != node->next->dest)
			{
				tmp = tmp->next;
			}
			sumPath += tmp->weight;
			printf("{%d->[%d]->%d} - ", node->dest, tmp->weight, tmp->dest);
			node = node->next;
			tmp = graph->array[node->dest].head;
		}
		sumPath += tmp->weight;
		if (sumPath > max) {
			max = sumPath;
			longestPath = curle->value->head;
		}
		printf("{%d->[%d]->%d} - Path weight = %d\n\n", node->dest, tmp->weight, curle->value->head->dest, sumPath);
		curle = curle->next;
	}

	printf("\nThe longest path was  found. Take a look :)\n");
	ListNode* crawl = longestPath;
	while (crawl->next != NULL) {
		printf("%d -> ", crawl->dest);
		crawl = crawl->next;
	}
	printf("%d -> %d - Path weight = %d\n\n", crawl->dest, longestPath->dest, max);
}

