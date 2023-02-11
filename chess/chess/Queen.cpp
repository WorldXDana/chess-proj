#include "Queen.h"

//Queen constarctor according to tools.
Queen::Queen(string type, string color, string place, Board* p_board) : Tool(type, color, place, p_board)
{
}

//Destractor.
Queen::~Queen()
{
}

//Checks for queen moves(using algorithems of Rook & Bishop).
bool Queen::move(string dst)
{
	string type1, type2;
	if (this->get_type().compare("q") == 0)
	{
		type1 = "b";
		type2 = "r";
	}
	else
	{
		type1 = "B";
		type2 = "R";
	}
	Rook r(type2, this->get_color(), this->get_place(), this->_b);
	Bishop b(type1, this->get_color(), this->get_place(), this->_b);
	if (r.move(dst) || b.move(dst))
		return true;
	return false;
}
