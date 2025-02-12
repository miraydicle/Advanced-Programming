// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include "boardclass.h"

using namespace std;

//parametric constructor
template <class T>
Board<T>::Board(int row,int col)
{
	rows = row; //initiate rows and columns
	cols = col;


	//construct the matrix
	matrix=new cell<T>*[rows];

	for(int i=0;i<rows;i++)
	{
		matrix[i]=new cell<T>[cols];
	}

	for(int j=0;j<rows;j++)
	{
		for(int k=0;k<cols;k++)
		{
			matrix[j][k].owner=0; //initiate owner
		}
	}
}

//deep copy constructor
template <class T>
Board<T>::Board(const Board<T>&copy)
{
	matrix=copy.createClone();
	rows=copy.rows;
	cols=copy.cols;
}

//function for deep copy constructor
template <class T>
cell<T>** Board<T>::createClone() const
{
	if(matrix==NULL)
	{
		return NULL;
	}

	cell<T>**matrixClone=new cell<T>*[rows];

	for(int i=0;i<rows;i++)
	{
		matrixClone[i]=new cell<T>[cols];
	}

	for(int j=0;j<rows;j++)
	{
		for(int k=0;k<cols;k++)
		{
			matrixClone[j][k].owner = matrix[j][k].owner;
			matrixClone[j][k].value = matrix[j][k].value;
		}
	}

	return matrixClone; //return head

}

//destructor
template <class T>
Board<T>::~Board()
{
	for(int i=0;i<rows;i++)
	{
		delete [] matrix[i];
	}

	rows = 0;
	cols = 0;

	delete [] matrix;
	matrix = NULL;

}

//displays the content of the matrix
template <class T>
void Board<T>::displayBoard()
{
	cout<<"Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE):"<<endl;
	for(int k=0;k<cols;k++)
	{
		cout<<"    "<<k;
	}
	cout<<endl;

	for(int i=0;i<rows;i++)
	{
		cout<<i<<" ";
		for(int j=0;j<cols;j++)
		{
			cout<<"("<<matrix[i][j].owner<<","<<matrix[i][j].value<<")";
		}
		cout<<endl;
	}
}

//updates value of a cell for given id
template <class T>
void Board<T>::updateBoardCells(int id,T upvalue)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(matrix[i][j].owner==id)
			{
				matrix[i][j].value = upvalue;
			}
		}
	}
}

//counts total number of cells of a given id
template <class T>
int Board<T>::getPlayerCellsCount(int id)
{
	int count=0;

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(matrix[i][j].owner==id)
			{
				count++;
			}
		}
	}

	return count;
}

//returns the owner of a given cell
template <class T>
int Board<T>::knowTheOwner(int r,int c)
{
	return matrix[r][c].owner;
}

//updates the value of a given cell
template <class T>
void Board<T>::updateValue(int r,int c,T val)
{
	matrix[r][c].value=val;
}

//updates the owner of a given cell
template <class T>
void Board<T>::updateOwner(int r,int c,int upowner)
{
	matrix[r][c].owner=upowner;
}

//gets the number of rows
template <class T>
int Board<T>::GetRows() const
{
	return rows;
}

//gets the number of columns
template <class T>
int Board<T>::GetColumns() const
{
	return cols;
}