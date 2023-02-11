#include "Bishop.h"

//Bishop constructor.
Bishop::Bishop(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

//Bishop destructor.
Bishop::~Bishop()
{
}

//move algorithem for Bishop.
bool Bishop::move(string dst)
{
	int src_col = (this->get_place()[0] - 97), src_line = 7 - (this->get_place()[1] - 49), dst_col = (dst[0] - 97), dst_line = 7 - (dst[1] - 49);
	int length = src_col - dst_col;
	if (abs(dst_col - src_col) != abs(dst_line - src_line))
		return false;
	if (dst_col > src_col && dst_line > src_line)
	{
		for (int i = 1; i < length; i++)
		{
			if (this->_b->have_tool(src_line + i, src_col + i)) return false;
		}
	}
	if (dst_col < src_col && dst_line < src_line)
	{
		for (int i = 1; i < length; i++)
		{
			if (this->_b->have_tool(src_line - i, src_col - i)) return false;
		}
	}
	if (dst_col > src_col&& dst_line < src_line)
	{
		for (int i = 1; i < length; i++)
		{
			if (this->_b->have_tool(src_line - i, src_col + i)) return false;
		}
	}
	if (dst_col < src_col && dst_line > src_line)
	{
		for (int i = 1; i < length; i++)
		{
			if (this->_b->have_tool(src_line + i, src_col - i)) return false;
		}
	}
	return true;
}
