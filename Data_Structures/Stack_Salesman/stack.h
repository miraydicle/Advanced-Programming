//Miray Dicle

#ifndef STACK_H //header guards
#define STACK_H

//x and y coordinates constructed
struct Coord
{
	int x;
	int y;

	Coord(const int& xCoord, const int& yCoord)
		: x(xCoord), y(yCoord) { }
};

//stack class
template <class T>
class Stack {
private:
	// Internal data representation
	struct ListNode
	{
		T coor;
		ListNode* next;

		ListNode(const T& theCoor, ListNode* n = NULL)
			: coor(theCoor), next(n) { }
	};

	ListNode* topOfStack;  // list itself is the stack

public:
	Stack();
	void push(T coor);
	void pop();
	T top();
	bool isEmpty();
	const static T noItem;
};

#include "functions.cpp"
#endif
