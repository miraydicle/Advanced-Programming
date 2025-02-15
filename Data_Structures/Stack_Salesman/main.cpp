//Miray Dicle

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "stack.h"

using namespace std;

int main()
{
    Stack<Coord> myStack1; //stack for uploading the coordinates from text file and visited cities
    Stack<Coord> myStack2; //stack for reversing the order of the coordinates
    Stack<Coord> myStack3; //stack for checking the visited cities

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
    int count = 0;
    int a, b;
    int k = 0;
    int l = 0;

    while (getline(myfile, line))
    {
        stringstream ss(line);

        while (ss >> ch)
        {
            if (count==0)
            {
                a = ch - '0'; //converting into integer
                count++;
            }
            else
            {
                b = ch - '0';
                count--;
            }
        }

       Coord temp1(a, b);
       myStack1.push(temp1);

    }

    myfile.close();

    //reversing order
    while (!myStack1.isEmpty())
    {
        myStack2.push(myStack1.top());
        myStack1.pop();
    }


    while (!myStack2.isEmpty())
    {
        if (myStack1.isEmpty())
        {
            cout << "Moving to (" << myStack2.top().x << "," << myStack2.top().y << ")" << endl;

            while ((k != myStack2.top().x) || (l != myStack2.top().y))
            {
                if (k < myStack2.top().x)
                {
                    k++;
                    cout << "(" << k << "," << l << ")" << endl;
                }

                else if (l < myStack2.top().y)
                {
                    l++;
                    cout << "(" << k << "," << l << ")" << endl;
                }

                Coord temp2(k, l);
                myStack1.push(temp2);

            }
            cout << "Arrived to (" << myStack2.top().x << "," << myStack2.top().y << ")" << endl;
            myStack2.pop();
        }
        
        //if visited cities stack is not empty, checks if a time travel is needed
        else
        {
            while ((!myStack1.isEmpty()) && ((myStack1.top().x != myStack2.top().x) || (myStack1.top().y != myStack2.top().y)))
            {
                myStack3.push(myStack1.top());
                myStack1.pop();
            }

            if (!myStack1.isEmpty())
            {
                cout << "Time travel back to (" << myStack2.top().x << "," << myStack2.top().y << ")" << endl;
                myStack2.pop();
                while (!myStack3.isEmpty())
                {
                    myStack3.pop();
                }
            }
            else
            {
                while (!myStack3.isEmpty())
                {
                    myStack1.push(myStack3.top());
                    myStack3.pop();
                }

                cout << "Moving to (" << myStack2.top().x << "," << myStack2.top().y << ")" << endl;

                k = myStack1.top().x;
                l = myStack1.top().y;

                while ((k != myStack2.top().x) || (l != myStack2.top().y))
                {
                    if (k < myStack2.top().x)
                    {
                        k++;
                        cout << "(" << k << "," << l << ")" << endl;
                    }

                    else if (l < myStack2.top().y)
                    {
                        l++;
                        cout << "(" << k << "," << l << ")" << endl;
                    }

                    else if (k > myStack2.top().x)
                    {
                        k--;
                        cout << "(" << k << "," << l << ")" << endl;
                    }

                    else if (l > myStack2.top().y)
                    {
                        l--;
                        cout << "(" << k << "," << l << ")" << endl;
                    }

                    Coord temp3(k, l);
                    myStack1.push(temp3);

                }
                cout << "Arrived to (" << myStack2.top().x << "," << myStack2.top().y << ")" << endl;
                myStack2.pop();
            }
        }
    }

    cout << "Back to (0,0)" << endl;

    if (!myStack1.isEmpty())
    {
        k = myStack1.top().x;
        l = myStack1.top().y;

        while (k > 0 || l > 0)
        {
            if (k > 0)
            {
                k--;
                cout << "(" << k << "," << l << ")" << endl;
            }

            else if (l > 0)
            {
                l--;
                cout << "(" << k << "," << l << ")" << endl;
            }

            myStack1.pop();
        }
        
    }

    cout << "Home sweet home" << endl;


    cin.get();
    cin.ignore();
    return 0;
}