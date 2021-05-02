#pragma once
#include "Indicate_board.h"

class Game_board : public Indicate_board
{
public:
	void Addborder(short left, short right, short up, short bottom, char ch);
	void Init_border(short row, short col);

	Game_board();
	Game_board(short x, short y, short Height, short Width);
	~Game_board();
};

inline void Game_board::Addborder(short left, short right, short bottom, short up, char ch)
{
	for (short i = left; i <= right; ++i)
		for (short j = bottom; j <= up; ++j)
		{
			Indicate_character* x = new Indicate_character(ch, i, j, Indicate_character::Gray, Indicate_character::Black);
			matrix.emplace_back(x);
		}
}

inline void Game_board::Init_border(short row, short col)
{
	for (short i = 0; i <= row; ++i)
		Addborder(pivot.X, pivot.X + width - 1, pivot.Y - 1 + i * 3, pivot.Y - 1 + i * 3, '_');

	for (short i = 0; i <= col; ++i)
		Addborder(pivot.X - 1 + i * 5, pivot.X - 1 + i * 5, pivot.Y, pivot.Y + height - 1, '|');
}

inline Game_board::Game_board()
{
}

inline Game_board::Game_board(short x, short y, short Height, short Width):Indicate_board(x, y, Height, Width)
{
}

inline Game_board::~Game_board()
{
}
