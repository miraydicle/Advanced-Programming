// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include <string>
#include <sstream>
#include "deckclass.h"

using namespace std;

// constructor
Deck::Deck ()
{
	card = NULL;
	size = 0;
}

/* Begin: code taken from MathVector.cpp and updated*/
// copy constructor - deep copy
Deck::Deck (const Deck & copy)
{
	size = copy.size;
	card = new Card [size]; // deep copy

	for(int i=0; i<size; i++)
	{
		card[i] = copy.card[i];
	}
}
/* End: code taken from MathVector.cpp and updated*/

// destructor
Deck::~Deck()
{
	size = 0;
	delete [] card;
}

// + operator
const Deck Deck::operator + (const Card & rhs)
{
	Deck deck; //create new deck object
	deck.SetSize(size+1); //set size of the object
	
	for(int i = 0; i < size; i++)
	{
		deck.card[i] = card[i]; //copy the content of previous deck
	}

	deck.card[size] = rhs; //add card to deck

	return deck; //return as new deck object
}

// + operator
const Deck Deck::operator + (const Deck & rhs)
{
	int lhssize = size;

	Deck deck; //create new deck object
	deck.SetSize(lhssize+rhs.size); //set size of the object

	for(int i = 0; i < lhssize; i++)
	{
		deck.card[i] = card[i]; //copy the content of previous deck
	}

	for(int i = 0; i < rhs.size; i++)
	{
		deck.card[i+lhssize] = rhs.card[i]; //add deck to deck
	}

	return deck; //return as new deck object
}

// += operator
Deck & Deck::operator += (const Deck & rhs)
{
	int lhssize = size;
	size = lhssize + rhs.size; //define total size

	Card*temp = new Card[size]; //temporary deck for new size

	for(int i = 0; i < lhssize; i++)
	{
		temp[i] = card[i]; //copy previous content
	}

	delete [] card; //delete previous object
    card = temp; //define card as new object

	for(int i = 0; i < rhs.size; i++)
	{
		card[i+lhssize] = rhs.card[i]; //add remaining deck
	}

	return *this;
}

// - operator
const Deck Deck::operator - (int rhs)
{
	Deck deck; //create new deck object

	if(!((rhs>size) || (size==rhs))) //if card number is greater than or equal to size of the deck
	{
		deck.SetSize(size-rhs); //set size of the new deck

	    for(int i = 0; i < size-rhs; i++)
	    {
			deck.card[i] = card[rhs+i]; //copy the remaining cards to deck
	    }
	}

	return deck;
}

// assignment operator
Deck & Deck::operator = (const Deck & rhs)
{
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		size = 0;
		delete[] card;

		// create new vector for left hand side
		size = rhs.size;
		card = new Card[size];

		for(int i = 0; i < size; i++)
		{
			card[i] = rhs.card[i]; // assign content
		}
	}

	return *this;
}

//check if total energy of two decks are the same
bool operator == (const Deck &lhs, const Deck &rhs)
{
	int sum1 = lhs.GetSum(); //calculate total energy of first deck
	int sum2 = rhs.GetSum(); //calculate total energy of second deck

	return(sum1==sum2); //return true if same
}

//check if total energy of second deck is greater
bool operator < (const Deck &lhs, const Deck &rhs)
{

	int sum1 = lhs.GetSum(); //calculate total energy of first deck
	int sum2 = rhs.GetSum(); //calculate total energy of second deck

	return(sum1<sum2); //return true if greater
}

//check if size of the deck is greater than given integer
bool Deck::operator > (int rhs) const
{
	return(size>rhs); //return true if greater
}

//check if the card exists in the deck
bool operator <= (const Card & lhs, const Deck & rhs)
{
	for(int j=0; j<rhs.GetSize(); j++)
	{
		return ((lhs.name==rhs[j].name) && (lhs.energy==rhs[j].energy)); //return true if card exists
	}
}

// << operator
ostream & operator << (ostream & os, const Deck & deck)
{
	os<<deck.tostring();
	return os;
}

//turn content of decks into string and print as a list
string Deck::tostring() const
{
	ostringstream os;
	for(int i=0; i<size; i++)
	{
		os<<i+1<<": "<<card[i].name<<" - "<<card[i].energy<<endl;
	}

	return os.str();
}

// [] operator
const Card & Deck::operator [] (int rhs) const
{
	return card[rhs];
}

// get size of the vector
int Deck::GetSize() const
{
	return size;
}

// set size of the vector
void Deck::SetSize(int newsize)
{
	card = new Card[newsize];
	size = newsize;
}

// get the total energy of a deck
int Deck::GetSum() const
{
	int sum = 0;
	for(int i=0; i<size; i++)
	{
		sum+=card[i].energy;
	}

	return sum;
}