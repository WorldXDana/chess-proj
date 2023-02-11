#pragma once

//includes
#include "Tool.h"
#include "Board.h"

class Bishop : public Tool
{
public:
	//constructor and destructor.
	Bishop(string type, string color, string place, Board* p_board);
	~Bishop();

	//Pure method(founction that check if Bishop can move).
	virtual bool move(string dst);
};

