//Miray Dicle

#include <iostream>
#include "stack.h"

using namespace std;

//default constructor for stack class
template <class T>
Stack<T>::Stack()
{
    topOfStack = NULL;
}

//returns true if the stack is empty
template <class T>
bool Stack<T>::isEmpty()
{
    return topOfStack == NULL;
}

//returns the top element of the stack if not empty
template <class T>
T Stack<T>::top()
{

	if (isEmpty())
	{
		exit(1);
	}
	else
	{
		return topOfStack->coor;
	}
}

//pops element from the stack if not empty
template <class T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		exit(1);
	}
	else
	{
		ListNode* oldTop = topOfStack;
		topOfStack = topOfStack->next;
		delete oldTop;
	}
}

//pushes element into the stack
template <class T>
void Stack<T>::push(T coor)
{
    topOfStack = new ListNode(coor, topOfStack);
}