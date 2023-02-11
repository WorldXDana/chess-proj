#include "Board.h"
#include <iostream>

//Boards constructor. Board --> 64 placses
//of a two dimentional array consists of *Tool
//pointers. Constructor also allcoates memory
//for tools and allocates them on board.
Board::Board(const string my_board)
{
	string place, color, type;
	char row, col;
	if (my_board[64] == '0') this->white_turn = true;
	else this->white_turn = false;
	for (int i = 0; i < 64; i++)
	{
		if (my_board[i] != '#')
		{
			place = "";
			type = my_board[i];
			row = (i % 8 + 'a');
			col = 8 - (i / 8) + 48;
			place += row;
			place += col;
			if (my_board[i] > 97 && my_board[i] < 122) color = "black";
			else if (my_board[i] > 65 && my_board[i] < 90) color = "white";
			else color = "Error";
			if (type == "R" || type == "r")
			{
				this->_board[i / 8][i % 8] = new  Rook(type, color, place, this);
			}
			else if (type == "p" || type == "P")
			{
				this->_board[i / 8][i % 8] = new  Pawn(type, color, place, this);
			}
			else if (type == "N" || type == "n")
			{
				this->_board[i / 8][i % 8] = new  Knight(type, color, place, this);
			}
			else if (type == "B" || type == "b")
			{
				this->_board[i / 8][i % 8] = new  Bishop(type, color, place, this);
			}
			else if (type == "K" || type == "k")
			{
				this->_board[i / 8][i % 8] = new  King(type, color, place, this);
			}
			else if (type == "Q" || type == "q")
			{
				this->_board[i / 8][i % 8] = new  Queen(type, color, place, this);
			}
		}
		else this->_board[i / 8][i % 8] = nullptr;
	}
}

//board destructor.
Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int g = 0; g < 8; g++)
		{
			if (this->_board[i][g] != nullptr)
				this->_board[i][g] = nullptr;
		}
	}
}

//Function translates game states to chosen protocol between frontend & backend.
int Board::goodMove(string src, string dst, bool bonus)
{
	int src_col = src[0] - 97, src_line = 7 - (src[1] - 49), dst_col = dst[0] - 97, dst_line = 7 - (dst[1] - 49);
	
	if (src_col < 0 || src_col > 7 || dst_col < 0 || dst_col > 7 || src_line < 0 || src_line > 7 || dst_line < 0 || dst_line > 7)
		return 5;
	else if (src.compare(dst) == 0)
		return 7;
	else if (this->_board[src_line][src_col] == nullptr || (this->white_turn && this->_board[src_line][src_col]->get_color().compare("black") == 0) || (!(this->white_turn) && this->_board[src_line][src_col]->get_color().compare("white") == 0))
		return 2;
	else if (this->have_tool(dst_line, dst_col) && ((this->white_turn && this->_board[dst_line][dst_col]->get_color().compare("white") == 0) || (!this->white_turn && this->_board[dst_line][dst_col]->get_color().compare("black") == 0)))
		return 3;
	//move not legal.
	else if (this->_board[src_line][src_col]->move(dst) == false)
		return 6;
	//if your move making chess on hemself.
	else if (this->chess_test(true, src, dst))
		return 4;
	//if there is a victory(shahmat)
	else if(false)
		return 8;
	//if you made a chess on the other player.
	else if (this->chess_test(false, src, dst))
	{
		if (bonus)
		{
			if (matt(src, dst)) return 8;
		}
		return 1;
	}
	else return 0;
}

//checks if a tool exist in place
//of board.
bool Board::have_tool(int line, int col)
{
	if (this->_board[line][col] != nullptr)
		return true;
	else return false;
}

//Prints board state(replaces front-end graphics).
void Board::printBoard()
{
	cout << "This is the board!!\n====================================================================\n";
	for (int i = 0; i < 8; i++)
	{
		for (int g = 0; g < 8; g++)
		{
			if (this->_board[i][g] == nullptr)
				cout << "# ";
			else
			{
				cout << this->_board[i][g]->get_type() << " ";
			}
		}
		cout << "\n";
	}
}

string Board::king_place(bool yourself)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(this->have_tool(i, j) && this->white_turn && yourself && this->_board[i][j]->get_color().compare("white") == 0 && this->_board[i][j]->get_type().compare("K") == 0)
			{
				return this->_board[i][j]->get_place();
			}
			if(this->have_tool(i, j) && this->white_turn && !yourself && this->_board[i][j]->get_color().compare("black") == 0 && this->_board[i][j]->get_type().compare("k") == 0)
			{
				return this->_board[i][j]->get_place();
			}
			if(this->have_tool(i, j) && !this->white_turn && yourself && this->_board[i][j]->get_color().compare("black") == 0 && this->_board[i][j]->get_type().compare("k") == 0)
			{
				return this->_board[i][j]->get_place();
			}
			if(this->have_tool(i, j) && !this->white_turn && !yourself && this->_board[i][j]->get_color().compare("white") == 0 && this->_board[i][j]->get_type().compare("K") == 0)
			{
				return this->_board[i][j]->get_place();
			}
		}
	}
}

//actually moves the pieces on board.
// in case there's a tool in this place  
//it changes the tools and "eats" it.
Tool* Board::making_move(const string src, const string dst)
{
	int src_col = src[0] - 97, src_line = 7 - (src[1] - 49), dst_col = dst[0] - 97, dst_line = 7 - (dst[1] - 49);
	Tool* t = this->_board[dst_line][dst_col];
	this->_board[dst_line][dst_col] = this->_board[src_line][src_col];
	this->_board[dst_line][dst_col]->set_place(dst);
	this->_board[src_line][src_col] = nullptr;
	return t;
}

void Board::make_turn(const string src, const string dst)
{
	this->making_move(src, dst);
	this->white_turn = !this->white_turn;
}

//checks for chess according move (virtual function that each tool has).
bool Board::chess_test(bool yourself, const string src, const string dst)
{
	int src_col = src[0] - 97, src_line = 7 - (src[1] - 49), dst_col = dst[0] - 97, dst_line = 7 - (dst[1] - 49);
	bool chess = false;
	Tool* t = nullptr;
	t = making_move(src, dst);
	string place = king_place(yourself);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (yourself)
			{
				if (this->have_tool(i, j) && this->_board[i][j]->move(place) && ((this->white_turn && this->_board[i][j]->get_color().compare("black") == 0) || (!this->white_turn && this->_board[i][j]->get_color().compare("white") == 0)))
				{
					chess = true;
				}
			}
			else
			{
				if (this->have_tool(i, j) && this->_board[i][j]->move(place) && ((this->white_turn && this->_board[i][j]->get_color().compare("white") == 0) || (!this->white_turn && this->_board[i][j]->get_color().compare("black") == 0)))
				{
					chess = true;
				}

			}
		}
	}
	
	this->_board[src_line][src_col] = this->_board[dst_line][dst_col];
	this->_board[dst_line][dst_col] = t;
	this->_board[src_line][src_col]->set_place(src);

	return chess;
}



bool Board::with_turn()
{
	return this->white_turn;
}

bool Board::matt(string src, string dst)
{
	int src_col = src[0] - 97, src_line = 7 - (src[1] - 49), dst_col = dst[0] - 97, dst_line = 7 - (dst[1] - 49);
	string king_place;
	string tool_place;
	char row, col;
	Tool* t = nullptr;
	t = making_move(src, dst);
	this->white_turn = !this->white_turn;
	king_place = this->king_place(true);
	int number = 9;

	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			for (int g = 0; g < 8; g++)
			{
				for (int h = 0; h < 8; h++)
				{
					tool_place = "";
					row = 7 - g + 49;
					col = h + 'a';
					tool_place += col;
					tool_place += row;
					if(this->have_tool(i, j)) number = this->goodMove(this->_board[i][j]->get_place(), tool_place, false);
					if (number == 0 || number == 1)
					{
						this->_board[src_line][src_col] = this->_board[dst_line][dst_col];
						this->_board[dst_line][dst_col] = t;
						this->_board[src_line][src_col]->set_place(src);
						this->white_turn = !this->white_turn;
						return false;
					}
				}
			}
		}
	}
	this->_board[src_line][src_col] = this->_board[dst_line][dst_col];
	this->_board[dst_line][dst_col] = t;
	this->_board[src_line][src_col]->set_place(src);
	this->white_turn = !this->white_turn;
	return true;
}

void Board::make_queen(int line, int col, string color)
{
	string type, place;
	char col2, line2;
	if (color.compare("black") == 0) type = "q";
	if (color.compare("white") == 0) type = "Q";
	line2 = 7 - line + 49;
	col2 = col + 'a';
	place += col2;
	place += line2;
	this->_board[line][col] = new Queen(type, color, place, this);
}