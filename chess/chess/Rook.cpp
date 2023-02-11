#include "Rook.h"

//builds a Rock according to type tool.
Rook::Rook(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

Rook::~Rook()
{
}

//checks for moves according to rook moves.
bool Rook::move(string dst)
{
	int src_col = (this->get_place()[0] - 97), src_line = 7 - (this->get_place()[1] - 49), dst_col = (dst[0] - 97), dst_line = 7 - (dst[1] - 49);
	if (dst_col != src_col && dst_line != src_line)
		return false;
	if (dst_col == src_col)
	{
		if (dst_line < src_line)
		{
			dst_line += src_line;
			src_line = dst_line - src_line;
			dst_line -= src_line;
		}
		for (int i = src_line + 1; i < dst_line; i++)
		{
			if (this->_b->have_tool(i, src_col)) return false;
		}
		return true;
	}
	if (dst_line == src_line)
	{
		if (dst_col < src_col)
		{
			dst_col += src_col;
			src_col = dst_col - src_col;
			dst_col -= src_col;
		}
		for (int i = src_col + 1; i < dst_col; i++)
		{
			if (this->_b->have_tool(src_line, i)) return false;
		}
		return true;
	}
}
