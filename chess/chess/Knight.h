#pragma once

//includes
#include "Tool.h"
#include "Board.h"


class Knight : public Tool
{
public:
	//constructor and destructor.
	Knight(string type, string color, string place, Board* p_board);
	~Knight();

	//Pure method(founction that check if Knight can move).
	virtual bool move(string dst);
};

