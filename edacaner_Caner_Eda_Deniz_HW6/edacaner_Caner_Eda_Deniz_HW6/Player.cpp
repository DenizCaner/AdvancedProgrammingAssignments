#include "Player.h"
#include "Board.h"
#include<iostream>
#include<string>

using namespace std;

Player::Player(	Board & b, char cp) //creates a player object
	:board(b), charPiece(cp)
{
}

bool Player::play(int col) // play function returns true if the playes can play the specified column, false otherwise
{

	return board.dropPieceOn(col, this->charPiece);

}

bool Player :: isWinner() //returns true if one of the players wins the game by connecting three charPieces
{
	return board.isConnect3(this->charPiece);
}
