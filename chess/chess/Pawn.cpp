#include "Pawn.h"

//Pawn constractor.
Pawn::Pawn(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

Pawn::~Pawn()
{
}

//Checks for legal moves in pawn.
bool Pawn::move(string dst)
{	
	bool can_move = false, make_queen = false;
	int src_col = (this->get_place()[0] - 97), src_line = 7 - (this->get_place()[1] - 49), dst_col = (dst[0] - 97), dst_line = 7 - (dst[1] - 49);
	if (0 == this->get_color().compare("black"))
	{
		if (src_col == dst_col && dst_line - src_line == 1 && this->_b->have_tool(dst_line, dst_col) == false)
			can_move = true;
		if (dst_col == src_col && src_line == 1 && dst_line == 3 && this->_b->have_tool(dst_line, dst_col) == false)
			can_move =  true;
		if (dst_line - src_line == 1 && this->_b->have_tool(dst_line, dst_col) && abs(dst_col - src_col) == 1)
			can_move = true;
	}
	if (0 == this->get_color().compare("white"))
	{
		if (src_col == dst_col && src_line - dst_line == 1 && this->_b->have_tool(dst_line, dst_col) == false) 
			can_move = true;
		if (dst_col == src_col && src_line == 6 && dst_line == 4 && this->_b->have_tool(dst_line, dst_col) == false)
			can_move = true;
		if (src_line - dst_line == 1 && this->_b->have_tool(dst_line, dst_col) && abs(dst_col - src_col) == 1)
			can_move = true;
	}	
	if (can_move)
	{
		if (this->_b->with_turn() && dst_line == 0 && src_line == 1)
		{
			make_queen = true;
		}
		else if(!this->_b->with_turn() && dst_line == 7 && src_line == 6)
		{
			make_queen = true;
		}
	}
	if (make_queen)
	{
		this->_b->make_queen(src_line, src_col, this->get_color());	
	}
	return can_move;
}
