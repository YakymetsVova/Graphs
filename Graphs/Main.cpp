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
	getCycles(graph, cycles);

	if (cycles->head != NULL) {
		printf("\nGraph contains at least one cycle");
		printf("\n\nYour cycles:\n\n");
		printCycles(graph, cycles);
	}
	else
	{
		printf("\n Graph doesn't contain a cycle");
	}
	
	freeGraph(&graph);
	freeDict(&cycles);
}

void printCycles(Graph* graph, Dictionary* cycles)
{
	DictionaryItem* tempDictItem = cycles->head;
	ListNode* longestPath = cycles->head->value->head;
	int max = -1;

	while (tempDictItem != NULL) {
		ListNode* node = tempDictItem->value->head;
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
			longestPath = tempDictItem->value->head;
		}
		printf("{%d->[%d]->%d} - Path weight = %d\n\n", node->dest, tmp->weight, tempDictItem->value->head->dest, sumPath);
		tempDictItem = tempDictItem->next;
	}

	printf("\nThe longest path was  found. Take a look :)\n");
	ListNode* crawl = longestPath;
	while (crawl->next != NULL) {
		printf("%d -> ", crawl->dest);
		crawl = crawl->next;
	}
	printf("%d -> %d - Path weight = %d\n\n", crawl->dest, longestPath->dest, max);
}

