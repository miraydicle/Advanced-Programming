// written by Miray Dicle
// used Visual Studio 2012 version

//header guard
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "boardclass.h"

template <class T>
class Player
{

private:

	//Data Members
	int id;
	static int next_id;
	Board<T> & board;
public:

	Player(Board<T>&);//parametric constructor

	//Member functions
	bool updateCell(int,int,T);
	bool unclaimOwnership(int,int);
	void updateMyCells(int);
	void unclaimOwnerships();
};

//initialize id
template <class T>
int Player<T>::next_id=1;

#include "miraydicle_Dicle_Miray_hw6_playermemfunc.cpp"
#endif