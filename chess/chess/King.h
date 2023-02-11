#pragma once

//includes
#include "Tool.h"
#include "Board.h"

class King : public Tool
{
public:
	//constructor and destructor.
	King(string type, string color, string place, Board* p_board);
	~King();

	//Pure method(founction that check if King can move).
	virtual bool move(string dst);
};

