#ifndef BOARD_H
#define BOARD_H

#include<string>
using namespace std;

class Board
{
private:
	char myBoard[5][4];
public:
	Board(); //done
	void Board::DisplayBoard() const; //done
	bool Board::dropPieceOn(int & val, char piece);
	bool Board::isFull() const; //done
	bool Board::isConnect3(char piece) const;
	bool Board::cellEmpty(int row, int col)const; //done
};
#endif
