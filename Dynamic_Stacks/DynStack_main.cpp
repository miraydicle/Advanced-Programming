// written by Miray Dicle
// used Visual Studio 2012 version

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include "DynStackclass.h"

using namespace std;

int main()
{
	DynStack openStack; //create stack object
	string fileName;
    ifstream myfile;

	do
    {
        cout << "Please enter the file name: ";
        cin >> fileName;
        myfile.open(fileName);
    } while (myfile.fail());

	string line;
	char ch;
	int lineno=0;
	bool iserror=false;

	while(getline(myfile,line))
	{
		lineno++;
		stringstream ss(line);

        while(ss>>ch)
		{
			if((ch=='{') || (ch=='(') || (ch=='[')) //if it is an opening symbol
		    {
				openStack.push(ch,lineno); //add symbol and line number to the stack
				cout<<"Found the opening symbol "<<ch<<" at line "<<lineno<<endl;
		    }
		    else if((ch=='}') || (ch==')') || (ch==']')) //if it is a closing symbol
			{
				
				if(!openStack.isEmpty())
				{
					char ch1;
					int lineno1;
					openStack.pop(ch1,lineno1); //previous data extracted from stack to be compared
					if(((ch1=='{') && (ch=='}')) || ((ch1=='(') && (ch==')')) || ((ch1=='[') && (ch==']'))) //if the symbols match
					{
						cout<<"Found the closing symbol "<<ch<<" at line "<<lineno<< " which closes the opening symbol "<<ch1<< " at line "<<lineno1<<endl;
					}
					else //if the symbols do not match
					{
						cout<<"ERROR!!! Found the closing symbol "<<ch<<" at line "<<lineno<<" but the last unclosed opening symbol is "<<ch1<<" at line "<<lineno1<<endl;
						ss.str("");
						myfile.close();
						iserror=true;
					}
                }
				else //if stack is empty which means no opening symbols exist before the closing symbol
				{
					cout<<"ERROR!!! Found the closing symbol "<<ch<<" but there are no unclosed opening symbols!"<<endl;
					ss.str("");
					myfile.close();
					iserror=true;
				}
		    }
        }
    }
	myfile.close();

	if(!iserror) //if no error occurred and program reached the end of the file
	{
	if(!openStack.isEmpty()) //if opening symbols exist in the stack
	{
		cout<<"ERROR!!! The following opening symbols were not closed: "<<endl;
		while(!openStack.isEmpty())
		{
			openStack.pop(ch,lineno); //extract all the symbols that are not closed
			cout<<"Symbol "<<ch<<" at line "<<lineno<<endl;
		}
    }
	else //if the stack is empty and all symbols are closed
	{
		cout<<"File processed successfully. No errors were found."<<endl;
    }
	}

	openStack.~DynStack(); //clears the stack

	cin.get();
	cin.ignore();
    return 0;
}