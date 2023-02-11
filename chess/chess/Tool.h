#pragma once
#include <string>

//std library.
using namespace std;

//fix circular reference.
class Board;

class Tool
{
public:
	//constructor and destructor.
	Tool(const string type, const string color, const string place,  Board* p_board);
	~Tool();

	//Pure method(founction that check if tool can move).
	virtual bool move(string dst) = 0;
	
	//getters
	string get_type() const;
	string get_place()const;   
	string get_color()const;
	
	//Setter.
	void set_place(string place);

protected:
	string _type;
	string _color;
	string _place;
	Board* _b;
};

