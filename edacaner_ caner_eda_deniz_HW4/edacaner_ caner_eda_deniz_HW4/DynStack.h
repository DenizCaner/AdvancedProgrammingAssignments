#ifndef _DYNSTACK_H
#define _DYNSTACK_H
#include <string>

using namespace std;

struct StackNode
{
	int X, Y;
	StackNode *next;
};

class DynStack
{
private:
	StackNode *top;

public:
	DynStack(void);
	void push(int a, int b);
	void pop(int & a, int & b);
	bool isEmpty(void);
};

#endif