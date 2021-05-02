#pragma once
#include "String_board.h"
#include "Detect_press_key.h"
class Menu
{
protected:
	short avail_horizon;
	short avail_ver;
	short choosing_number;
	Detect_press_key key;
	std::vector <String_board*> vt;
public:
	short getavail_horizon();
	short getavail_ver();
	short getchoosing_number();

	void setavail_horizon(short src);
	void setavail_ver(short src);
	void setchoosing_number(short src);

	void Add(char* src,short Color);
	void Choose();
	void Draw();

	Menu(short x, short y);
	Menu();
	~Menu();
};



inline short Menu::getavail_horizon()
{
	return avail_horizon;
}

inline short Menu::getavail_ver()
{
	return avail_ver;
}

inline short Menu::getchoosing_number()
{
	return choosing_number;
}

inline void Menu::setavail_horizon(short src)
{
	avail_horizon = src;
}

inline void Menu::setavail_ver(short src)
{
	avail_ver = src;
}

inline void Menu::setchoosing_number(short src)
{
	choosing_number = src;
}

inline void Menu::Add(char * src,short Color)
{
	vt.emplace_back(new String_board(src, avail_ver, avail_horizon, Color));
	avail_horizon += 2;
}

inline void Menu::Choose()
{
	while (true)
	{
		int result = key.return_press_key();
		vt[choosing_number]->Draw();
		switch (result)
		{
		case Detect_press_key::ARROW_UP:
			choosing_number = (choosing_number - 1 + (short) vt.size()) % (short)vt.size();
			break;
		case Detect_press_key::ARROW_DOWN:
			choosing_number = (choosing_number + 1) % vt.size();
			break;
		case Detect_press_key::ENTER:
			for (auto element : vt) element->clrscr();
 			return;
		default:
			break;
		}
		vt[choosing_number]->change_to_choosing_state(4);
	}
}

inline void Menu::Draw()
{
	for (auto element : vt)
		element->Draw();
}

inline Menu::Menu(short x, short y)
{
	avail_horizon = y;
	avail_ver = x;
}

Menu::Menu()
{
}


Menu::~Menu()
{
	for (auto element : vt)
		delete(element);
	vt.erase(vt.begin(), vt.end());
}
