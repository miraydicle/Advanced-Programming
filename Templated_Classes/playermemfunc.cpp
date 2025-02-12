// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include "playerclass.h"
#include "boardclass.h"

using namespace std;

//parametric constructor for object sharing
template <class T>
Player<T>::Player(Board<T>& b):board(b)
{
	id = next_id; //incremental ids
	next_id++;
}

//updates the cell value of a given id
template <class T>
bool Player<T>::updateCell(int rows,int cols,T val)
{
	//if no owner exists for that cell
	if(board.knowTheOwner(rows,cols)==0)
	{
		board.updateValue(rows,cols,val); //updates the value
		board.updateOwner(rows,cols,id); //updates the owner
		return true;
	}
	//if given id is the owner of that cell
	else if(id==board.knowTheOwner(rows,cols))
	{
		board.updateValue(rows,cols,val);
		return true;
	}

	return false;
}

//updates value of a cell for given id
template <class T>
void Player<T>::updateMyCells(int val)
{
	board.updateBoardCells(id,val);
}

//unclaims ownership of a given cell
template <class T>
bool Player<T>::unclaimOwnership(int rows, int cols)
{
	if(board.knowTheOwner(rows,cols)==id)
	{
		board.updateOwner(rows,cols,0);
		return true;
	}
	
	return false;
}

//unclaims all ownerships of a given id
template<class T>
void Player<T>::unclaimOwnerships()
{
	for(int i=0;i<board.GetRows();i++)
	{
		for(int j=0;j<board.GetColumns();j++)
		{
			if(board.knowTheOwner(i,j)==id)
			{
				board.updateOwner(i,j,0);
			}
		}
	}
}