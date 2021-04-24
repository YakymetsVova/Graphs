#include "Header.h"

int getHash(List* arr) 
{
	int prime = 97;
	ListNode* curr = arr->head;

	int length = 0;

	while (curr != NULL) {
		length++;
		curr = curr->next;
	}
	curr = arr->head;

	int result = length % prime;
	while (curr != NULL) {
		result = (curr->dest + result) % prime;
		curr = curr->next;
	}

	return result;
}



