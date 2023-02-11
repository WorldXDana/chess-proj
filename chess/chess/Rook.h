#pragma once

//includes
#include "Tool.h"
#include "Board.h"

class Rook : public Tool
{
public:
	//constructor and destructor.
	Rook(string type, string color, string place, Board* p_board);
	~Rook();
	
	//Pure method(founction that check if Rooc can move).
	virtual bool move(string dst);

};

