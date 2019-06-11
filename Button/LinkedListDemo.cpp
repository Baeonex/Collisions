#include "LinkedListDemo.h"



LinkedList::LinkedList() {
	this->length = 0;
	this->head = NULL;
}

LinkedList::~LinkedList() {
	std::cout << "LIST DELETED";
}

void LinkedList::add(int data) {
	Node* node = new Node();
	node->data = data;
	node->next = this->head;
	this->head = node;
	this->length++;
}

void LinkedList::print() {
	Node* head = this->head;
	int i = 1;
	while (head) {
		std::cout << i << ": " << head->data << std::endl;
		head = head->next;
		i++;
	}
}
int LinkedList::search(int nodeNumber)
{
	Node* head = this->head;
	int i = 1;
	while (i <= nodeNumber) {
		if (i = nodeNumber)
		{
			return head->data;
		}
		head = head->next;

		i++;
	}
	return 0;
}

int LinkedList::size()
{
	return this->length;
}

void LinkedList::clearList()
{
	Node* iterator = this->head;

	while (iterator != 0)
	{
		head = iterator->next;
		delete iterator;
		iterator = head;
	}
}

bool LinkedList::areIdentical(Node *a, Node *b)
{
	while (a != NULL && b != NULL)
	{
		if (a->data != b->data)
			return false;

		/* If we reach here, then a and b are
		not NULL and their data is same, so
		move to next nodes in both lists */
		a = a->next;
		b = b->next;
	}

	// If linked lists are identical, then  
	// 'a' and 'b' must be NULL at this point. 
	return (a == NULL && b == NULL);
}
