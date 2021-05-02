#pragma once
#include "Indicate_character.h"
#include "Detect_press_key.h"

enum Point_State {NONE,SYMBOL1,SYMBOL2};

class Player
{
protected:
	Indicate_character* point;
public:
	Indicate_character* getpoint();
	void human_choose(bool& isexit, bool isplayer1,COORD pivot, Point_State ** arr,short row,short col);
	void computer_choose(COORD pivot, Point_State** arr, short row, short col);
	Player();
	~Player();
};



inline Indicate_character * Player::getpoint()
{
	return point;
}

void Player::human_choose(bool& isexit, bool isplayer1,COORD pivot, Point_State ** arr, short row,short col)
{
	short i, j;
	point->setpivot({ -1,-1 });
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j) if (arr[i][j] == NONE)
		{
			point->setpivot({ pivot.X + 1 + 5 * j, pivot.Y + 1 + 3 * i });
			break;
		}
		if (point->getpivot().X != -1) break;
	}

	if (point->getpivot().X == -1) return;

	Detect_press_key xx;
	while (true)
	{
		point->setpivot({ pivot.X + 1 + 5 * j, pivot.Y + 1 + 3 * i });
		bool flag = false;
		if (arr[i][j] != NONE)
		{
			point->set_ch(arr[i][j] == SYMBOL1 ? 'X' : 'O'); 
			point->change_to_choosing_state(4);
			flag = true;
		}
		else
		{
			point->set_ch(isplayer1 ? 'X' : 'O');
			point->twinkling(400,80);
		}

		int result = xx.return_press_key();
		switch (result)
		{
		case Detect_press_key::ARROW_DOWN:
		{
			if (flag) point->draw();
			i = (i + 1) % row;
			break;
		}
		case Detect_press_key::ARROW_UP:
		{
			if (flag) point->draw();
			i = (i - 1 + row) % row;
			break;
		}
		case Detect_press_key::ARROW_LEFT:
		{
			if (flag) point->draw();
			j = (j - 1 + col) % col;
			break;
		}
		case Detect_press_key::ARROW_RIGHT:
		{
			if (flag) point->draw();
			j = (j + 1) % col;
			break;
		}
		case Detect_press_key::EXIT:
		{
			isexit = true;
			return;
		}
		case Detect_press_key::ENTER:
		{
			if (arr[i][j] == NONE)
			{
				if (isplayer1) arr[i][j] = SYMBOL1;
				else arr[i][j] = SYMBOL2;
				point->draw(); 
				return;
			}
		}
		}
	}
}

inline void Player::computer_choose(COORD pivot, Point_State ** arr, short row, short col)
{
	return ;
}


Player::Player()
{
	point = new Indicate_character(' ', -1, -1, 11, 0);
}


Player::~Player()
{
	delete(point);
}
