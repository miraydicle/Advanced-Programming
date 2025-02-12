#include <iostream>
#include "PrintQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
PrintQueue::PrintQueue()
{
	front = NULL;
	rear = NULL;
	currentSize = 0;
}



//************************************************
// Copy Constructor.                             *
//************************************************
PrintQueue::PrintQueue(const PrintQueue& rhs)
{
	front = NULL;
	rear = NULL;
	currentSize = 0;

	if (!rhs.isEmpty())
	{
		currentSize = 0;
		PrintJobNode* tmp = rhs.front;
		while (tmp != NULL)
		{
			enqueue(tmp->PrintJobId, tmp->numberOfPages);
			tmp = tmp->next;
		}
	}
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void PrintQueue::enqueue(int num, int numberOfPages)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new PrintJobNode(num, numberOfPages);
		rear = front;
		currentSize++;

	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new PrintJobNode(num, numberOfPages);
		rear = rear->next;
		currentSize++;

	}

}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void PrintQueue::dequeue(int& num, int & pages)
{
	PrintJobNode* temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->PrintJobId;
		pages = front->numberOfPages;
		temp = front;
		front = front->next;
		delete temp;
		currentSize--;
	}
}

//*********************************************
// Function getCurrentSize returns current    *
// size of the queue.						  *
//*********************************************
int PrintQueue::getCurrentSize() const
{
	return currentSize;
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool PrintQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}

//*********************************************
// Assignment Operator						  *
//*********************************************
PrintQueue& HW7PrintQueue::operator=(const PrintQueue& rhs)
{
	if (this != &rhs) //self assignment check
	{

		int value, pages;   // Dummy variable for dequeue
		while (!isEmpty())
			dequeue(value, pages); //delete all elements

		front = NULL;
		rear = NULL;
		currentSize = 0;

		PrintJobNode* tmp = rhs.front;
		while (tmp != NULL)
		{
			enqueue(tmp->PrintJobId, tmp->numberOfPages);
			tmp = tmp->next;
		}

	}
	return *this;
}
//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
PrintQueue::~PrintQueue()
{
	int value, pages;   // Dummy variable for dequeue

	while (!isEmpty())
		dequeue(value, pages); //delete all elements
}

