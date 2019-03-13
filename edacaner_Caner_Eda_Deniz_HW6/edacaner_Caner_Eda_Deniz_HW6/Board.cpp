#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() // creates 5*4 char matrix as a board
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			myBoard[i][j] = '_'; // equalizes all the values of matrix to '_'
		}
	}
}

void Board::DisplayBoard()const //Displays the current board
{
	cout << "Board: " << endl;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			cout << myBoard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool Board::cellEmpty(int row, int col) const // Checks if the cell is empty or not 
{
	if(myBoard[row][col] == '_')
	{
		return true; // returns true if the cell is empty
	}

	return false; //returns false if the cell is not empty
}

bool Board::isFull()const // checks if the board is full or not
{
	int countFullCells = 0;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(cellEmpty(i,j)) //calls cellEmpty function for the every cell on the matrix
			{
				return false; // returns false if there is an empty cell
			}
		}
	}
	return true;
}

bool Board::dropPieceOn(int & col, char piece) // drops the specified piece to the speciified column  of the board
{
	int r = 0;
	if(myBoard[r][col] == '_' && myBoard[r+1][col] != '_' )
	{
		myBoard[r][col] = piece; // inserts the charPiece into the empty cell in the specified column
		return true;
	}
	while( r < 4 && myBoard[r+1][col] == '_' ) // check if the r value is smaller than 4 to stay in the range, and if the next cell in the column is empty or not
	{
		r++;
	}
	if(r == 0)
	{
		cout << "There is no emtyp place in this column." << endl;
		return false;
	}
	else 
	{
		myBoard[r][col] = piece; // inserts the charPiece into the empty cell in the specified column
		return true;
	}
}

bool Board::isConnect3(char piece) const // checks if there is three connected pieces in the game
{
	if(myBoard[0][0] == piece)
	{
		if(myBoard[0][1] == piece)
		{
			if(myBoard[0][2] == piece)
			{
				return true;
			}
		}

		if(myBoard[1][1] == piece)
		{
			if(myBoard[2][2] == piece)
			{
				return true;
			}
		}

		if(myBoard[1][0] == piece)
		{
			if(myBoard[2][0] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[0][1] == piece)
	{
		if(myBoard[1][1] == piece)
		{
			if(myBoard[2][1] == piece)
			{
				return true;
			}
		}
		if(myBoard[1][2] == piece)
		{
			if(myBoard[2][3] == piece)
			{
				return true;
			}
		}
		if(myBoard[0][2] == piece)
		{
			if(myBoard[0][3] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[0][2] == piece)
	{
		if(myBoard[1][2] == piece)
		{
			if(myBoard[2][2] == piece)
			{
				return true;
			}
		}

		if(myBoard[1][1] == piece)
		{
			if(myBoard[2][0] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[0][3] == piece)
	{
		if(myBoard[1][3] == piece)
		{
			if(myBoard[2][3] == piece)
			{
				return true;
			}
		}

		if(myBoard[1][2] == piece)
		{
			if(myBoard[2][1] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[1][0] == piece)
	{
		if(myBoard[1][1] == piece)
		{
			if(myBoard[1][2] == piece)
			{
				return true;
			}
		}
		if(myBoard[2][1] == piece)
		{
			if(myBoard[3][2] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[1][1] == piece)
	{
		if(myBoard[2][2] == piece)
		{
			if(myBoard[3][3] == piece)
			{
				return true;
			}
		}
		if(myBoard[2][1] == piece)
		{
			if(myBoard[3][1] == piece)
			{
				return true;
			}
		}
		if(myBoard[1][2] == piece)
		{
			if(myBoard[1][3] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[1][2] == piece)
	{
		if(myBoard[2][2] == piece)
		{
			if(myBoard[3][2] == piece)
			{
				return true;
			}
		}
		if(myBoard[2][1] == piece)
		{
			if(myBoard[3][0] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[1][3] == piece)
	{
		if(myBoard[2][3] == piece)
		{
			if(myBoard[3][0] == piece)
			{
				return true;
			}
		}
		if(myBoard[2][2] == piece)
		{
			if(myBoard[3][1] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[2][0] == piece)
	{
		if(myBoard[2][1] == piece)
		{
			if(myBoard[2][2] == piece)
			{
				return true;
			}
		}
		if(myBoard[3][1] == piece)
		{
			if(myBoard[4][2] == piece)
			{
				return true;
			}
		}
		if(myBoard[3][0] == piece)
		{
			if(myBoard[4][0] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[2][1] == piece)
	{
		if(myBoard[3][1] == piece)
		{
			if(myBoard[4][1] == piece)
			{
				return true;
			}
		}
		if(myBoard[2][2] == piece)
		{
			if(myBoard[2][3] == piece)
			{
				return true;
			}
		}
		if(myBoard[3][2] == piece)
		{
			if(myBoard[4][3] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[2][2] == piece)
	{
		if(myBoard[3][2] == piece)
		{
			if(myBoard[4][2] == piece)
			{
				return true;
			}
		}
		if(myBoard[3][1] == piece)
		{
			if(myBoard[4][0] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[2][3] == piece)
	{
		if(myBoard[3][3] == piece)
		{
			if(myBoard[4][3] == piece)
			{
				return true;
			}
		}
		if(myBoard[3][2] == piece)
		{
			if(myBoard[4][1] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[3][0] == piece)
	{
		if(myBoard[3][1] == piece)
		{
			if(myBoard[3][2] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[3][1] == piece)
	{
		if(myBoard[3][2] == piece)
		{
			if(myBoard[3][3] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[4][0] == piece)
	{
		if(myBoard[4][1] == piece)
		{
			if(myBoard[4][2] == piece)
			{
				return true;
			}
		}
	}

	if(myBoard[4][1] == piece)
	{
		if(myBoard[4][2] == piece)
		{
			if(myBoard[4][3] == piece)
			{
				return true;
			}
		}
	}

	return false;
}