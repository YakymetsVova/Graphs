#include "Header.h"
#include <chrono>

int main()
{
	Graph* graph = NULL;

	readData(&graph);

	puts("\n Result of reading data:");
	printGraph(graph);

	Dictionary* cycles = newDictionary();

	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	auto t1 = high_resolution_clock::now();
	getCycles(graph, cycles);
	auto t2 = high_resolution_clock::now();
	if (cycles->head != NULL) {
		printf("\nGraph contains at least one cycle");
		printf("\n\nYour cycles:\n\n");
		printCycles(graph, cycles);
	}
	else
	{
		printf("\n Graph doesn't contain a cycle");
	}

	duration<double, std::milli> ms_double = t2 - t1;
	printf("\n\nTime taken by function to find all cycles: %lfms", ms_double);

	freeGraph(&graph);
	freeDict(&cycles);

	getchar();

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

void readData(Graph** graph)
{
	FILE* fp;
	char path[MAX];
	printf("Enter the path to the file you want to read from\n");
	gets_s(path, MAX);
	if ((fp = fopen(path, "r")) == NULL) {
		puts("\nNo file found");
		exit(EXIT_FAILURE);
	}
	int source, dest, weight, vertexes;
	fscanf(fp, "%d", &vertexes);
	*graph = createGraph(vertexes);
	while (!feof(fp)) {
		if (fscanf(fp, "%d%d%d", &source, &dest, &weight))
			addEdge(*graph, source, dest, weight);
		else {
			puts("Invalid input!");
			exit(EXIT_FAILURE);
		}
	}
	fclose(fp);
}