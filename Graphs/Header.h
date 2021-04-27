#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNodeTag {
	int dest;
	int weight;
	ListNodeTag* next;
} ListNode;


/*A structure to represent an adjacency list*/
typedef struct ListTag {
	ListNode* head;
}List;


/*A structure to represent a graph. A graph is an array
of adjacency lists. Size of array will be V
(number of vertices in graph)*/
typedef struct GraphTag{
	int V;
	List* array;
} Graph;



typedef struct DictItemTag {
	int key;
	List* value;
	DictItemTag* next;
}DictionaryItem;


typedef struct DictTag {
	DictionaryItem* head;
}Dictionary;


ListNode* newListNode(int dest, int weight);
ListNode* newListNode(int dest);
List* newList();
void AddToList(List* list, int item);
void removeLastItem(List* list);


Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest, int weight);
void printGraph(Graph* graph);
bool* newVisitedVertexArr(Graph* graph);
void GetCycle(Graph* graph, Dictionary* dict, int start, int node, bool visited[], List* mark);
void printCycles(Graph* graph, Dictionary* cycles);


int getHash(List* arr);

DictionaryItem* newDictItem(int key, List* value);
Dictionary* newDictionary();
void addToDict(Dictionary* dict, DictionaryItem* item);
bool containsKey(Dictionary* dict, int key);






