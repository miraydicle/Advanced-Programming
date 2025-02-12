// written by Miray Dicle
// used Visual Studio 2012 version

//header guard
#ifndef TWODLINKEDLIST_H
#define TWODLINKEDLIST_H

#include <string>

struct node
{
	char data;
	node *right;
	node *down;

	//default constructor
	node ()
	{}

	//constructor
	node (char c,node *r, node*d)
		:data(c), right(r), down(d)
	{}	


};

class TwoDLinkedList
{
	//Access specifier
private:

	//Data Members
	node *head;

public:

	//Member Functions
	TwoDLinkedList(); //Constructor

	void add_row_sorted(std::string str);
	void displayFullMatrix();
	void displayFullMatrixReversed();
	void display_rows_starting_with(char ch);
	void display_cols_starting_with(char ch);
	int delete_rows_starting_with(char ch);
	int delete_cols_starting_with(char ch);
	void clear();
};

#endif