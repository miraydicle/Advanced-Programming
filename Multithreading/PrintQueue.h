#ifndef PrintQueue_H
#define PrintQueue_H

struct PrintJobNode 
{
	int PrintJobId, numberOfPages;
	PrintJobNode* next;
	PrintJobNode(int num, int nPages, PrintJobNode* ptr = NULL)
	{
		PrintJobId = num;
		numberOfPages = nPages;
		next = ptr;
	}
};

class PrintQueue 
{
private:
	// These track the front and rear of the queue.
	PrintJobNode* front;
	PrintJobNode* rear;
	int currentSize; 
public:
	// Constructor.
	PrintQueue();
	PrintQueue(const PrintQueue& rhs); // copy constructor
	// Member functions.
	int getCurrentSize() const; 
	PrintQueue& operator=(const PrintQueue& rhs); 
	void enqueue(int id, int numberOfPages);
	void dequeue(int& id, int & pages);
	bool isEmpty() const;
	//Destructor
	~PrintQueue();
};
#endif
