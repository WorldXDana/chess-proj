#include "Knight.h"

//Knight constractor.
Knight::Knight(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

Knight::~Knight()
{
}

//Knight moves (algorithem).
bool Knight::move(string dst)
{
	int src_col = (this->get_place()[0] - 97), src_line = 7 - (this->get_place()[1] - 49), dst_col = (dst[0] - 97), dst_line = 7 - (dst[1] - 49);
	if (abs(dst_line - src_line) == 1 && abs(dst_col - src_col) == 2)
		return true;
	if (abs(dst_line - src_line) == 2 && abs(dst_col - src_col) == 1)
		return true;
	return false;
}