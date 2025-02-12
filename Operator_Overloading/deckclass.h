// written by Miray Dicle
// used Visual Studio 2012 version

//header guard
#ifndef DECKCLASS_H
#define DECKCLASS_H

#include <string>

using namespace std;

struct Card
{
	string name;
	int energy;
};

class Deck
{
	//Access specifier
private:

	//Data Members
	Card *card;
	int size;

public:

	Deck(); //Constructor
	Deck(const Deck&); //deep copy constructor
	~Deck(); //destructor

	//Member Functions
	const Deck operator + (const Card &);
	const Deck operator + (const Deck &);
	const Deck operator - (int);
	Deck & operator += (const Deck &);
	Deck & operator = (const Deck &);
	const Card & Deck::operator [] (int) const;
	bool Deck::operator > (int) const;
	string Deck::tostring() const;
	//getter and setters
	int GetSize() const;
	int GetSum() const;
	void SetSize(int);

};

//Free functions
ostream & operator << (ostream &, const Deck &);
bool operator <= (const Card &, const Deck &);
bool operator == (const Deck &, const Deck &);
bool operator < (const Deck &, const Deck &);

#endif