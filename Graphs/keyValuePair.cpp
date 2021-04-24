#include "Header.h"


/// <summary>
/// initialize new dict item
/// </summary>
/// <param name="key">hash of the value</param>
/// <param name="value">List of vertexes</param>
/// <returns></returns>
DictionaryItem* newDictItem(int key, List* value)
{
	DictionaryItem* item = (DictionaryItem*)malloc(sizeof(DictionaryItem));
	List* temp = newList();
	ListNode* curr = value->head;
	while (curr!= NULL)
	{
		AddToList(temp, curr->dest);
		curr = curr->next;
	}
	item->value = temp;
	item->key = key;
	item->next = NULL;
	return item;
}


//creates new dictionary
Dictionary* newDictionary() 
{
	Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
	dict->head = NULL;
	return dict;
}


// function to add at the end of dictionary
void addToDict(Dictionary* dict, DictionaryItem* item)
{
	DictionaryItem* current = dict->head;
	if (current == NULL) {
		dict->head = item;
		return;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = item;
	return;
}

//check if hash already exists
bool containsKey(Dictionary* dict, int key) 
{
	if (dict->head == NULL)
		return false;
	DictionaryItem* current = dict->head;
	while (current != NULL) {
		if (current->key == key)
			return true;
		current = current->next;
	}
	return false;
}