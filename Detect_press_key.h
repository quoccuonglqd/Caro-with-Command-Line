#pragma once
#include <conio.h> 
class Detect_press_key
{
public:
	static const int ARROW_UP = 72;
	static const int ARROW_DOWN = 80;
	static const int ARROW_LEFT = 75;
	static const int ARROW_RIGHT = 77;
	static const int ENTER = 13;
	static const int ARROW_NONE = 0;
	static const int EXIT = 113;

	int return_press_key();
	Detect_press_key();
	~Detect_press_key();
};



inline int Detect_press_key::return_press_key()
{
	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ENTER || ch==EXIT)
			return ch;
		if (ch == 0 || ch == 224)
		{
			ch = _getch();
			if (ch == 72 || ch == 80 || ch == 75 || ch == 77)
				return ch;
		}
		return 0;
	}
	return 0;
}

Detect_press_key::Detect_press_key()
{
}


Detect_press_key::~Detect_press_key()
{
}
