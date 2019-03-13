#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include<string>
#include<iostream>

using namespace std;

class Player
{
private:
	Board & board;
	char charPiece;

public:
	Player(Board & b, char cp);
	bool Player :: play(int column);
	bool Player :: isWinner();

};

#endif