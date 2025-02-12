// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include <string>
#include <sstream>
#include "TwoDLinkedList.h"

using namespace std;

//default constructor for class
TwoDLinkedList::TwoDLinkedList ()
{
	head = NULL;
}

//Adds the words in text files as sorted rows into 2d linked list
void TwoDLinkedList::add_row_sorted (string s)
{
	char ch;
	stringstream ss(s);
	node * row=head;
	node * col=head;
	node * prev;
	node * ptr;
	int charno=0;
	static int lineno=0;
    bool firstrow=false;
	bool lastrow=false;

	while(ss >> ch)
	{
		if(lineno==0) //filling the first row of the 2d linked list
		{
			if(head == NULL) //if linkedlist is empty
		    {
				col = new node(ch,NULL,NULL); //add a new node to the list
			    head = col;                   //update the head
				row = col;
		    }
		    else
	    	{
				(*col).right = new node(ch,NULL,NULL);
			    col = (*col).right;
		    }
		}
		//checking for the words to be inserted to already created 2d linkedlist with first word
		else if(charno==0) //if first character of a word is read
		{
				prev = row;
				col = row;
				if((row->data>ch)&&(row==head)) //if first character of the new word is smaller than that of word in first row
				{
					col = new node(ch,NULL,head); //add a new node upon the previous first row
			        head = col;                   //update the head
			        row = col;
		         	charno++;
		        	firstrow=true;
                }
				else if((row->data<ch)&&(row->down==NULL)) //if first character of the new word is larger than that of word in first row and no other row exists
				{
					col = new node(ch,NULL,NULL); //add a new node under the existing row
					prev->down = col;
					prev = prev->right;
				    charno++;
				    lastrow=true;
				}
				else //if the word to be added will not be in first or last row
				{
					while(row!=NULL)
					{
		
						if(row->data<ch) //if first character is larger than that of currently checked row
						{
							prev = row;
							row = row->down;
                        }
						else
						{
							row = NULL;
						}	
                    }
					col = new node(ch,NULL,prev->down);
					prev->down = col;
					prev = prev->right;
					charno++;
                }
		}
		else if(firstrow) //if it is not the first character of the word to be inserted and it will be in first row
		{
			(*col).right = new node(ch,NULL,prev->right);
			col = (*col).right;
			prev = prev->right;
        }
		else if(!lastrow)//if it is not the first character of the word to be inserted and it will be in a middle row
		{
		
			(*col).right = new node(ch,NULL,prev->down);
			prev->down = (*col).right;
			prev = prev->right;
			col = (*col).right;
        }
		else //if it is not the first character of the word to be inserted and it will be in last row
		{
			(*col).right = new node(ch,NULL,NULL);
			prev->down = (*col).right;
			prev = prev->right;
			col = (*col).right;
        }
	}

	lineno++;
	firstrow=false;
	lastrow=false;
}

//Displays all the words in 2d linked list
void TwoDLinkedList::displayFullMatrix ()
{
	node * row=head;
	node * col=head;

	while(row != NULL) //scannig the rows
	{
		while(col != NULL) //scanning the columns
		{
			cout << col->data << "";
		    col = col->right;
		}
		cout << endl;
		row = row->down;
		col = row;
	}
}

//Displays all the words in 2d linkedlist in a reverse order
void TwoDLinkedList::displayFullMatrixReversed ()
{
	static node*row=head;
	node*col=head;
	static int count = 0;

	while(row != NULL)
	{
		if(count!=0) //if it is not the first row
		{
			row=row->down;
		}
		col = row;
		count++;
		displayFullMatrixReversed(); //recursion function
		while(col != NULL)
		{
			cout << col->data << "";
		    col = col->right;
		}
		cout << endl;
	}
}

//Displays the rows starting with a given character
void TwoDLinkedList::display_rows_starting_with (char ch)
{
	node * row=head;
	node * col=head;

	while(row != NULL)//scanning the rows
	{
		if(row->data==ch)//If the node with the given character is found
		{
			while(col != NULL) //scanning the columns
			{
				cout << col->data << "";
		        col = col->right;
            }
			cout << endl;
			row = row->down;
			col = row;
		}
		else
		{
			row = row->down;
			col = row;
		}
	}
}

//Displays the columns starting with a given character
void TwoDLinkedList::display_cols_starting_with (char ch)
{
	node * row=head;
	node * col=head;

	while(col != NULL) //scanning the columns
	{
		if(row->data==ch)//If the node with the given character is found
		{
			while(row != NULL) //scanning the rows
			{
				cout << row->data << "";
				cout << endl;
		        row = row->down;
            }
			col = col->right;
			row = col;
		}
		else
		{
			col = col->right;
			row = col;
		}
	}
}

//Deletes and counts the deleted the rows starting with a given character
int TwoDLinkedList::delete_rows_starting_with (char ch)
{
	node * row=head;
	node * col=head;
	node * toBeDeleted;
	node * prev=head;
	node * ptr;
	int delno=0;

	while(row != NULL)
	{
		if(row->data==ch) //If the node with the given character is found
		{
			delno++; //update the deleted row number
			ptr = prev;
			if(row==head) //If the node to be deleted is head
			{
				head = row->down; //Updates the head node
			    prev = row->down;
			}
			row = row->down;
			while(col != NULL)
			{
				toBeDeleted = col;
				col = col->right;
				ptr->down = toBeDeleted->down;
				ptr = ptr->right;
				delete toBeDeleted;
            }
			
			col = row;
		}
		else //check for next rows
		{
			prev = row;
			row = row->down;
			col = row;
		}
	}
	return delno; //return the number of deleted rows
}

//Deletes columns starting with a given character
int TwoDLinkedList::delete_cols_starting_with (char ch)
{
	node * row=head;
	node * col=head;
	node * toBeDeleted;
	node * prev=head;
	node * ptr;
	node*nextcol;
	int delno=0;

	while(col != NULL)
	{
		if(col->data==ch) //If the node with the given character is found
		{
			delno++; //update the deleted column number
			ptr = prev;	

			if(col==head) //If the node to be deleted is head
			{
				head = col->right; //Updates the head node
			    prev = col->right;

				if(col->right!=NULL) //if it is not the last column
			{
				col = col->right;
				nextcol = col;
            }
			else
			{
				nextcol = col;
				col = col->right;
            }
				while(row != NULL)
			{

				toBeDeleted = row;
				nextcol->down = toBeDeleted->right;
				row = row->down;
				ptr->right = toBeDeleted->right;
				ptr = ptr->down;
				nextcol = nextcol->down;
				delete toBeDeleted;
			}

            }
			else //If the node to be deleted is not head
			{
				col = col->right;

				while(row != NULL)
			{
				
				toBeDeleted = row;
				ptr->right = toBeDeleted->right;
				if(ptr->down!=NULL)
				{
					ptr = ptr->down;
				    ptr->right=toBeDeleted->down;
				}
				
				else
				{
					ptr = ptr->down;
				}
				row = row->down;
				delete toBeDeleted;
			}
			}

			row = col;
		}
		else //check for next columns
		{
			prev = col;
			col = col->right;
			row = col;
		}
	}
	return delno; //return the number of deleted columns
}

//Clears all of the elements in the list
void TwoDLinkedList::clear ()
{
	node * row=head;
	node * col=head;
	node * toBeDeleted;

	while(row != NULL)
	{
		if(row==head) //when head is to be deleted
		{
			head = row->down; //updates the head
		}
		row = row->down;
		while(col != NULL)
		{
			toBeDeleted = col;
			col = col->right;
			delete toBeDeleted;
        }
		col = row;
	}
}
