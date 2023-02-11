#pragma once

//includes
#include "Tool.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include <string>

//fix circular reference.
class Tool;

class Board
{
public:
	//constructor and destructor.
	Board(string my_board);
	~Board();
	
	//Main functions.
	int goodMove(const string src, const string dst, bool bonus);
	void make_turn(const string src, const string dst);
	
	//Secondary functions.
	bool have_tool(int line, int col);
	void printBoard();
	bool chess_test(bool yourself, const string src, const string dst);
	string king_place(bool yourself);
	Tool* making_move(const string src, const string dst);
	
	bool with_turn();
	bool matt(string src, string dst);
	void make_queen(int line, int col, string color);
	

private:
	Tool* _board[8][8];
	bool white_turn;
};

