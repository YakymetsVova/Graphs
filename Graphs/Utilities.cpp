#include "Header.h"

int getHash(List* arr) 
{
	int prime = 97;
	ListNode* curr = arr->head;
	int result = 1;

	while (curr != NULL) {
		result += (curr->dest << 3) % prime + 11;
		curr = curr->next;
	}
	return result;
}



