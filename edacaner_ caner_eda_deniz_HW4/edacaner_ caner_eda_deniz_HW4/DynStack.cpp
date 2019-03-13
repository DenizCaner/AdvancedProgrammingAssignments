#include <iostream>
#include <cctype>
#include <string>
#include "DynStack.h"

using namespace std;

DynStack::DynStack()
{
	top = NULL; 
}

void DynStack::push(int a, int b)
{
	StackNode *newNode;
	newNode = new StackNode;
	newNode->X = a;
	newNode->Y = b;

	if (isEmpty()) // If there are no nodes in the list make newNode the first node
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

void DynStack::pop(int & a, int & b)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		a = top->X;
		b = top->Y;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
