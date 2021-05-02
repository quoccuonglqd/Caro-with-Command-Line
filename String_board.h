#pragma once
#include "Indicate_board.h"
#include <cstring>
class String_board:public Indicate_board
{
public:
	void change_to_choosing_state(short Color);
	String_board(char* src,short x,short y,short Color);
	String_board();
	~String_board();
};



inline void String_board::change_to_choosing_state(short Color)
{
	for (auto element : matrix)
		element->change_to_choosing_state(Color);
}

inline String_board::String_board(char * src,short x,short y,short Color)
{
	short len = (short)strlen(src);
	for (short i = 0; i < len; ++i)
		matrix.emplace_back(new Indicate_character(*(src + i), x + i, y, Color,Indicate_character::Black));
}

String_board::String_board()
{
}


String_board::~String_board()
{
}
