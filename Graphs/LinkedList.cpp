#include "Header.h"


LinkedList* newLinkedList() 
{
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	return list;
}

LinkedListItem* newLinkedListItem(int value)
{
	LinkedListItem* item = (LinkedListItem*)malloc(sizeof(LinkedListItem));
	item->next = NULL;
	item->value = value;
	return item;
}

void AddToList(LinkedList* list, int item)
{
	LinkedListItem* node = newLinkedListItem(item);
	LinkedListItem* current = list->head;
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

void removeLastItem(LinkedList* list)
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

	LinkedListItem* current = list->head;
	while (current->next->next != NULL)
		current = current->next;
	free(current->next);
	current->next = NULL;

}