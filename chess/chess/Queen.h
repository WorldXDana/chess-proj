#pragma once

//includes
#include "Tool.h"
#include "Board.h"


class Queen : public Tool
{
public:
	//constructor and destructor.
	Queen(string type, string color, string place, Board* p_board);
	~Queen();

	//Pure method(founction that check if Queen can move).
	virtual bool move(string dst);
};

