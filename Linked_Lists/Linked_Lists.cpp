// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include <sstream>
#include <fstream> // for ifstream
#include <cctype>  // for islower(), isalpha()
#include <string>
#include <crtdbg.h> //for _CrtDumpMemoryLeaks()

using namespace std;

struct node
{
	char ch;
	node * next;

	//default constructor
	node ()
	{}

	//constructor
	node (char c,node *n)
		:ch(c), next(n)
	{}	
};

//Displays all the characters in a list
void DisplayList (node * myList)
{
	node * ptr = myList;
	while (ptr != NULL)
	{
		cout << ptr->ch << "";
		ptr = ptr->next;
	}
}

//Finds the number of character similarities between two lists
void Sim (node * myList1, node * myList2, int & count)
{
	node * p = myList1;
	node * r = myList2;
	count = 0;

	while ((p != NULL) && (r != NULL))
	{
		if((p->ch) == (r->ch))
		{
			count++;
        }
		p = p->next;
		r = r->next;
	}
}

//Deletes given character from a list
void Delete (node *& myList, node * toBeDeleted, char & argument)
{
	node * ptr = myList;

	while (ptr != NULL)
	{
		if(ptr->ch == argument) //If the node with the given character is found
		{
			toBeDeleted = ptr;
			if (toBeDeleted==myList) //If the node to be deleted is head
	        {
				myList = myList->next; //Updates the head node
				ptr = myList;
		        delete toBeDeleted;
            }
	        else //Updates the pointer if the node to be deleted is not head
	        {
				ptr = myList;
		        while (ptr->next != toBeDeleted)
		        {
					ptr = ptr->next;
		        }
				ptr->next = toBeDeleted->next;
		        delete toBeDeleted;
	        }
        }
		else
		{
			ptr = ptr->next;
		}
	}
}

//Inserts first argument to the position after second argument in a list
void Insert(node *& myList, char & argument1, char & argument2, bool & isFound)
{
	node * ptr = myList;

	if((myList==NULL) || (!isFound)) //If the list is empty or argument is not found in the list
	{
		node * temp = new node(argument1,myList); //Inserts the character as a head
		myList = temp;
    }
	else
	{
		while((ptr!=NULL) && (ptr->ch!=argument2))
	    {
			ptr = ptr->next;
        }
        ptr->next = new node(argument1,ptr->next); //Add a new node between p and its next node
	}
}

/* Begin: code taken from linkedList.cpp and updated*/
//Deletes all of the elements in the list
void ClearList(node *myList)
{
	node *ptr;
	while(myList!=NULL)
	{
		ptr = myList;
		myList = myList->next;
		delete ptr;
	}
}
/* End: code taken from linkedList.cpp and updated*/

//Check if the character is valid(alphabetic (a-z) and lower case)
bool CheckInput(string & argument, char & argchar)
{
	stringstream arg(argument);
	while ( arg.get(argchar) )
    {
		if ( !isalpha(argchar) || !islower(argchar))
        {
			return true;
			arg.str("");
        }	
    }
	return false;
}

/* Begin: code taken from linkedList.cpp and updated*/
//Searches the list for a character and returns true or false
bool SearchList(node * myList, char & argument)
{
	node * ptr=myList;
	while(ptr != NULL)
	{
		if(ptr->ch == argument) //If the node with the given character is found
		{
			return true;
			ptr = NULL;
		}
		else
		{
		    ptr = ptr->next;
		}
    }
	// If the code proceeds from here, it means the node could not be found.
	return false;
}
/* End: code taken from linkedList.cpp and updated*/

int main()
{
	node *myList1; //linkedlist1
	node *myList2; //linkedlist2
	
	node *p = NULL;
	node *r = NULL;

	node *toBeDeleted = NULL;

	int count;
	bool isFound;
	bool isInvalid;

	string		filename1, filename2, line1, line2, command, argument1, argument2;
	ifstream    input1, input2;

	cout << "Please enter the file 1 name: ";
	cin >> filename1;

	input1.open(filename1);

	while ( input1.fail() )
    {   
		cout << "Please enter the file 1 name: "<<endl;
		cin >> filename1;
		input1.open(filename1);
    }

	cout << "Please enter the file 2 name: ";
	cin >> filename2;

	input2.open(filename2);

	while ( input2.fail() )
    {   
		cout << "Please enter the file 2 name: "<<endl;
		cin >> filename2;
		input2.open(filename2);
    }

	char ch1, ch2;

	//Fills the linked list1 with characters in the first text file
	while(!input1.eof())
	{
		getline(input1,line1);
		stringstream ss1(line1);
		while (ss1 >> ch1)
		{
			if (p==NULL) //If linkedlist is empty
			{
				p = new node(ch1,NULL); //Add a new node to the list
				myList1 = p;
			}
			else
			{
				(*p).next = new node(ch1,NULL);
				p = (*p).next;
            }
		}
	}

	//Fills the linked list2 with characters in the second text file
	while(!input2.eof())
	{
		getline(input2,line2);
		stringstream ss2(line2);
		while (ss2 >> ch2)
		{
			if (r==NULL) //If linkedlist is empty
			{
				r = new node(ch2,NULL); //Add a new node to the list
				myList2 = r;
			}
			else
			{
				(*r).next = new node(ch2,NULL);
				r = (*r).next;
            }
		}
	}

	//Displays contents of the lists
	cout << "List1: ";
	DisplayList(myList1);
	cout << endl<<"List2: ";
	DisplayList(myList2);

	// Ask for a command from the user
	cout << endl<< "Enter a command and its corresponding argument(s), if any: " <<endl;
	
	while(cin >> command)
	{
	//Check if entered command is valid
	if ((command!="sim") && (command!="exit") && (command!="del1") && (command!="del2") && (command!="insert1") && (command!="insert2"))
	{
		cin.sync();
		cout << "Invalid command." <<endl;
		cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
	}
	else if(command == "sim")
	{	
		cout<<"Displaying the contents of the two lists: "<<endl;
		cout << "List1: ";
	    DisplayList(myList1);
	    cout << endl<<"List2: ";
	    DisplayList(myList2);
		Sim(myList1,myList2,count);
		cout<<endl<<"There is/are "<<count<<"letter(s) matched in the same positions in both lists."<<endl;
		cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
    }
	else if(command == "exit")
	{
		cout<<"Clearing the two lists and saying Goodbye!"<<endl;
		ClearList(myList1);
		ClearList(myList2);
    }
	/* Ask for corresponding argument(s) from the user. After the user enters argument(s), 
	search for it in the list. If a node with this argument exists in the list,
	delete or insert node according to the command. */
	else if(cin>>argument1)
	{
		char argch = argument1[0];
		isInvalid=CheckInput(argument1,argch);

			if (isInvalid)
			{
				cin.sync();
				cout << "Invalid argument." <<endl;
		        cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
			}
			else
			{
				if(command=="del1")
			    {
					isFound = SearchList(myList1,argch);
					if(isFound) //Delete the argument from the list1 if found
					{
						Delete(myList1,toBeDeleted,argch);
                        cout << "Deleting all occurrences of "<<argument1<<" in List1."<<endl;
                        cout << "The current content of List1 is: "<<endl;
	                    DisplayList(myList1);
						cout << endl<<"Enter a command and its corresponding argument(s), if any: " <<endl;
					}
					else
					{
						cout<< "No deletion as the value "<<argch<<" was not found in the list."<<endl;
						cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
				    }
                }
				else if(command=="del2")
			    {
					isFound = SearchList(myList2,argch);
					if(isFound) //Delete the argument from the list2 if found
					{
						Delete(myList2,toBeDeleted,argch);
                        cout << "Deleting all occurrences of "<<argument1<<" in List2."<<endl;
                        cout << "The current content of List2 is: "<<endl;
	                    DisplayList(myList2);
						cout <<endl<< "Enter a command and its corresponding argument(s), if any: " <<endl;
					}
					else
					{
						cout<< "No deletion as the value "<<argch<<" was not found in the list."<<endl;
						cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
				    }
                }
				else if(cin>>argument2)
				{
					char argch2 = argument2[0];
		            isInvalid=CheckInput(argument2,argch2);

			if (isInvalid)
			{
				cout << "Invalid argument." <<endl;
		        cout << "Enter a command and its corresponding argument(s), if any: " <<endl;
			}
			else
			{
				if(command=="insert1")
				{
				isFound = SearchList(myList1,argch2); //Insert the first argument if the second is found in the list 1
				if(isFound)
				{
					cout<<"Inserting "<<argument1<<" after "<<argument2<<" in List1."<<endl;
					Insert(myList1,argch,argch2,isFound);
                    cout<<"The node with "<<argument1<<" has been inserted after the first occurrence of a node with "<<argument2<<" value."<<endl;
                    cout<<"The current content of List1 is: "<<endl;
	                DisplayList(myList1);
					cout <<endl<< "Enter a command and its corresponding argument(s), if any: " <<endl;
				}
				else
				{
					cout<<"Inserting "<<argument1<<" after "<<argument2<<" in List1."<<endl;
					cout<<"The node with "<<argument2<<" value does not exist. Therefore, Inserting "<<argument1<<" at the beginning of the list."<<endl;
					Insert(myList1,argch,argch2,isFound);
					cout<<"The current content of List1 is: "<<endl;
					DisplayList(myList1);
					cout << endl<<"Enter a command and its corresponding argument(s), if any: " <<endl;
				}
				}
				else if(command=="insert2")
				{
				isFound = SearchList(myList2,argch2); //Insert the first argument if the second is found in the list 2
				if(isFound)
				{
					cout<<"Inserting "<<argument1<<" after "<<argument2<<" in List2."<<endl;
					Insert(myList2,argch,argch2,isFound);
                    cout<<"The node with "<<argument1<<" has been inserted after the first occurrence of a node with "<<argument2<<" value."<<endl;
                    cout<<"The current content of List2 is: "<<endl;
	                DisplayList(myList2);
					cout <<endl<< "Enter a command and its corresponding argument(s), if any: " <<endl;
				}
				else
				{
					cout<<"Inserting "<<argument1<<" after "<<argument2<<" in List2."<<endl;
					cout<<"The node with "<<argument2<<" value does not exist. Therefore, Inserting "<<argument1<<" at the beginning of the list."<<endl;
					Insert(myList2,argch,argch2,isFound);
					cout<<"The current content of List2 is: "<<endl;
					DisplayList(myList2);
					cout << endl<<"Enter a command and its corresponding argument(s), if any: " <<endl;
				}
				}
				}
				}
			}
	}
	}

	//Remove all the nodes from the linked list to avoid any memory leakage
	ClearList(myList1);
	ClearList(myList2);

	cin.get();
	cin.ignore();

	_CrtDumpMemoryLeaks();

	return 0;	
}