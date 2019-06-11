#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;


class Node
{
public:
	Node* next;
	int data;
};

class LinkedList
{
public:
	int length;
	Node* head;

	LinkedList();
	~LinkedList();
	bool areIdentical(Node *a, Node *b);
	void add(int data);
	void print();
	int search(int nodeNumber);
	int size();
	void clearList();
};

