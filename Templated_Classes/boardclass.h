// written by Miray Dicle
// used Visual Studio 2012 version

//header guard
#ifndef BOARDCLASS_H
#define BOARDCLASS_H

template <class T>
struct cell
{
	int owner;
	T value;

	//default constructor
	cell()
	{}

	//constructor
	cell(const T & v, int o)
		:value(v), owner(o)
	{}
};

template <class T>
class Board
{

private:

	//Data Members
	cell<T>**matrix;
	int rows;
	int cols;

public:
	Board(int,int);//parametric constructor
	Board(const Board<T>&);//deep copy constructor
	cell<T>** createClone() const;

	//Member functions
	void displayBoard();
	void updateBoardCells(int,T);
	int getPlayerCellsCount(int);
	int knowTheOwner(int,int);
	void updateValue(int,int,T);
	void updateOwner(int,int,int);
	//getters
	int GetRows() const;
	int GetColumns() const;
	~Board();//destructor
};
#include "miraydicle_Dicle_Miray_hw6_boardmemfunc.cpp"
#endif