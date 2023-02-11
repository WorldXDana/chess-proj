#pragma once

//includes
#include "Tool.h"
#include "Board.h"

class Pawn : public Tool
{
public:
	//constructor and destructor.
	Pawn(string type, string color, string place, Board* p_board);
	~Pawn();

	//Pure method(founction that check if Pawn can move).
	virtual bool move(string dst);
	
};

