#include "King.h"

//king's constructor
King::King(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

King::~King()
{
}

//checks for kings moves according to dst.
bool King::move(string dst)
{
	int src_col = (this->get_place()[0] - 97), src_line = 7 - (this->get_place()[1] - 49), dst_col = (dst[0] - 97), dst_line = 7 - (dst[1] - 49);
	if (abs(dst_col - src_col) > 1 || abs(dst_line - src_line) > 1)
		return false;
	return true;
}

