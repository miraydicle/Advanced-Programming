//Miray Dicle

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "worditem.h"

using namespace std;

//checks if the word is string or not
bool isString(string str)
{
    for (int i = 0; i <str.length(); i++)
    {
        if (!isalpha((unsigned char)str[i]))
        {
            return false;
        }
    }

    return true;
}

//makes a word lower case
string makeLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
        {
            str[i] = str[i] + 32;
        }
    }

    return str;
}

int main()
{
    AVLSearchTree<string, WordItem*> myTree; //creates a tree

    string str, filename, line, line2, word;
    vector<string>words; //reads words from cin
    vector<string>filenames; //reads file names from cin
    ifstream myfile;
    int fileNo;
    int exist = 0;

    do
    {
        //checks if correct input is entered or not
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "Enter number of input files:" << endl;
        cin >> fileNo;
        
    } while (cin.fail());
    

    for (int k = 0; k < fileNo; k++)
    {
        do
        {
            cout << "Enter " << k + 1 << ". file name: ";
            cin >> filename;

            filenames.push_back(filename); //stores file names into vector

            myfile.open(filename);

        } while (myfile.fail());

        string line, word;

        //text file processing starts here
        while (getline(myfile, line))
        {
            stringstream ss(line);

            while (ss >> word)
            {
                if (isString(word))
                {
                    word = makeLower(word);

                    //if alreadys exists in tree
                    if (myTree.find(word) != "notFound")
                    {
                        DocumentItem* ptr2 = myTree.findHead(word);
                        DocumentItem* prev = NULL;

                        while (ptr2 != NULL)
                        {
                            if (ptr2->documentName != filename) //checks if new document is being processed
                            {
                                prev = ptr2;
                                ptr2 = ptr2->next;
                            }
                            else //if not, updates the count
                            {
                                int counter = ptr2->count;
                                counter++;
                                ptr2->count = counter;
                                break;
                            }
                        }

                        if (ptr2 == NULL) //if document is different, creates a new item
                        {
                            prev->next = new DocumentItem(filename, 1, NULL);
                        }

                    }
                    else //if word does not exist in tree or tree is empty
                    {
                        DocumentItem* temp;
                        temp = new DocumentItem(filename, 1, NULL);
                        WordItem* ptr;
                        ptr = new WordItem(word, temp);
                        myTree.insert(word, ptr);
                    }
                }
            }
        }
        myfile.close();
    }
    
    cout << "Enter queried words in one line:" << endl;

    cin.ignore();
    while(getline(cin,line2))
    {
        stringstream ss2(line2);

            while(ss2>>str)
            {
                str = makeLower(str);

                //stores words that exist in tree
                if (myTree.find(str) != "notFound")
                {
                    words.push_back(str);
                }
            }
            DocumentItem* txtptr = NULL;

            if (words.size() == 0)
            {
                cout << "No document contains the given query" << endl;
            }
            else
            {
                for (int k = 0; k < filenames.size(); k++)
                {
                    for (int l = 0; l < words.size(); l++)
                    {

                        txtptr = myTree.findHead(words[l]);
                        //loops until documentname is the same as head
                        while (txtptr->documentName != filenames[k] && txtptr->next != NULL)
                        {
                            txtptr = txtptr->next;
                        }
                        //if found and it is the first time
                        if (exist == 0 && txtptr->documentName == filenames[k])
                        {
                            cout << "in Document " << txtptr->documentName;
                            cout << ", " << words[l] << " found " << txtptr->count << " times";
                            exist++;
                        }
                        //if not the first time that it is found
                        else if (txtptr->documentName == filenames[k])
                        {
                            cout << ", " << words[l] << " found " << txtptr->count << " times";
                        }  
                    }
                    cout << endl;
                    exist = 0;
                }
            }  
    }
    
    cin.get();
    cin.ignore();
    return 0;
}