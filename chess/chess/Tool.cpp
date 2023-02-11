#include "Tool.h"

//Base builder to all tools in game.
Tool::Tool(const string type, const string color, const string place, Board* p_board)
{
    this->_type = type;
    this->_color = color;
    this->_place = place;
    this->_b = p_board;
}

//no destructor needed.
Tool::~Tool()
{
}

//getter.
string Tool::get_type() const
{
    return this->_type;
}

string Tool::get_place() const
{
    return this->_place;
}

string Tool::get_color() const
{
    return this->_color;
}

//sets place of tool in board.
void Tool::set_place(string place)
{
    this->_place = place;
}
