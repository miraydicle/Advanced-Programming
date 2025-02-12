// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include <iomanip> // for setw
#include <sstream>
#include <fstream> // for ifstream
#include <cctype>  // for islower(), isalpha()
#include <string>
#include <vector>

using namespace std;

void Count(stringstream & ss, int & total);
void Duplicate(stringstream & guess, vector<int> & counts);
void Print(const vector<vector<struct cell>> & mat);

struct cell
{
	char letter; // letter inside the cell
	char color; // color of the cell
};

int main()
{
	int j, k, rows;
	int cols = 0; // counter for letters in original word
	string		filename, line, word, original;

	ifstream    input;

	cout << "Welcome to SWordle!"<<"\n"<<"Please enter the file name: ";
	cin >> filename;

	input.open(filename);

	while ( input.fail() )
    {   
		cout << "Couldn't find the file!" <<"\n"<<"Please enter the file name: "<<endl;
		cin >> filename;
		input.open(filename);
    }

	while(!input.eof())
	{
		for (int lineno = 1; getline(input,line) && lineno < 3; lineno++) //scan line nos while getting lines
		{
			stringstream ss(line);
			if (lineno == 1) // first line is attempt no
			{
				ss >> rows;
			}
			else
			{
				Count(ss, cols);
				original = line; // second line is the word itself
			}
		}
	}

	cout << "The word that you will guess has "<<cols<<" letters and you have "<<rows<<" attempts."<<"\n"<<"What's your guess?"<<endl;

	vector<vector<struct cell>> mat(rows, vector<struct cell>(cols)); // matrix is constructed

	// default values for cell
	cell mycell;
	mycell.letter = '-';
	mycell.color = '-';

	for (j = 0; j < rows; j++)	// fill matrix
	{
		for (k = 0; k < cols; k++)
		{
			mat[j][k] = mycell;
		}
	}

	j=0;

	while (cin >> word)
	{
		// word length is checked
		if (word.length()>cols)
		{
			cout << "The word is too long!"<<"\n"<<"What's your guess?"<<endl;
		}
		else if (word.length()<cols)
		{
			cout << "The word is too short!"<<"\n"<<"What's your guess?"<<endl;
		}
		else if (word.length() == cols)
		{
			char ch;
		    bool ilgate = false;
		    stringstream ilguess(word);

		    while ( ilguess.get(ch) )
            {   
		    	if ( !isalpha(ch) || !islower(ch)) // illegal letter is checked
                {
			    	ilguess.str("");
			    	ilgate = true;
			    	cout << "Your input has illegal letters!"<<"\n"<<"What's your guess?"<<endl;
                }
            }

            if (ilgate == false)
		    {
				bool dupgate = false;
		        stringstream guess(word);

				// 0 for 'a', 1 for 'b', 2 for 'c', so on, 25 for 'z'
                // all initialized to 0
		        vector<int> charCounts(26);
		        Duplicate(guess,charCounts);

		        for (int m = 0; m <= 25; m++) // every no of character is checked
                {
					if (charCounts[m] > 1)
	                {
						m = 25;
		                dupgate = true;
		                cout << "Your input has a duplicate letter!"<<"\n"<<"What's your guess?"<<endl;
		            }
		        }
		        if (dupgate == false)
		        {
					bool samegate = false;
				    for (int n=0; n<rows; n++)
				    {
					    for (int p=0; p<cols; p++)
					    {
							if (word[p] == mat[n][p].letter) // check if word characters are the same as in previous attempts
				            {
								samegate = true;
					            if (p == cols-1)
					            {
									n = rows-1;
					            }
					        }
					        else
					        {
								p = cols-1;
						        samegate = false;
                            }
				        }
				    }
					if (samegate == true)
					{
						cout << "You've already tried this word!"<<"\n"<<"What's your guess?"<<endl;
                    }
					else
					{
						bool greengate = false;
				        for (int r=0; r<rows; r++)
			            {
							for (int s=0; s<cols; s++)
				            {
								if ((mat[r][s].color == 'G') && (word[s] != mat[r][s].letter)) // check if green letter is used in the same position
					            {
									r = rows-1;
						            s = cols-1;
						            greengate = true;
						            cout << "You did not use the green letter in your word!"<<"\n"<<"What's your guess?"<<endl;
					            }
					        }
				        }
				        if (greengate == false)
				        {
							for (k=0; k<cols; k++)
			                 {
								 mat[j][k].letter = word[k]; // fill matrix with the characters of the word
					             if ( word[k] == original[k]) // green letter case
					             {
									 mat[j][k].color = 'G';
                                 }
				                 else
					             {
									 for (int l=0; l<cols; l++) // check if any character is used in the word in any position
				                     {
										 if (word[k] == original[l]) // yellow letter case
					    	             {
											 mat[j][k].color = 'Y';
					                     }
				                     }
                                     if (mat[j][k].color == '-') // otherwise black case
				                     {
										 mat[j][k].color = 'B';
                                     }
                                 }   
				             }
				             Print(mat);
				             if (word == original) // word is same in text file
			                 {
								 cout <<"You win!"<<endl;
                             }
		                     else if (j == rows-1) // after all tried attempts word is not the same
                             {
								 cout <<"You lose!"<<endl;
                             }
				             else // attempts have not been completed, ask again
				             {
								 j++;
					             cout <<"What's your guess?"<<endl;
			               	 }
                        }
				    }
			    }	
		    }
		}
	}

	cin.get();
	cin.ignore();
    return 0;
}
/* Begin: code taken from letters.cpp and updated*/
void Count(stringstream & ss, int & total)
{
    char ch;

    while ( ss.get(ch) )        // read a character
    {   
		if ( isalpha(ch) )      // is alphabetic (a-z) or (A-Z)?
        {
			total++;
		}
	}
}

void Duplicate(stringstream & guess, vector<int> & counts)
{
	char ch;

    while ( guess.get(ch) )        // read a character
    {   
		if ( isalpha(ch) )         // is alphabetic (a-z) or (A-Z)?
        {
            counts[ch - 'a']++;    // count all characters (calculation done with ASCII values)
		}
	}
}
/* End: code taken from letters.cpp and updated*/

/* Begin: code taken from MatrixDemo1.cpp and updated*/
void Print(const vector<vector<struct cell>> & mat)
{
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
        {   
			cout << setw(4) << mat[j][k].letter<<","<<mat[j][k].color;
        }
        cout << endl;
    }
}
/* End: code taken from MatrixDemo1.cpp and updated*/