#include "Header.h"

//node is part of graph adjaency list 
ListNode* newListNode(int dest, int weight)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->dest = dest;
	node->weight = weight;
	node->next = NULL;
	return node;
}

List* newList()
{
	List* list = (List*)malloc(sizeof(List));
	list->head = NULL;
	return list;
}


//just linked list of vertexes
ListNode* newListNode(int dest)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->dest = dest;
	node->next = NULL;
	return node;
}

//add at the end of linked list
void AddToList(List* list, int item)
{
	ListNode* node = newListNode(item);
	ListNode* current = list->head;
	if (current == NULL) {
		list->head = node;
		return;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = node;
	return;
}

//remove last item of the linked list
void removeLastItem(List* list)
{
	if (list->head == NULL) {
		free(list);
		return;
	}
	if (list->head->next == NULL) {
		free(list->head);
		free(list);
		return;
	}

	ListNode* current = list->head;
	while (current->next->next != NULL)
		current = current->next;
	free(current->next);
	current->next = NULL;
}

