#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

class Indicate_character
{
protected:
	char ch;
	COORD pivot;
	short color;
	short bg_color;
public:
	static const short Black                =    0;
	static const short Blue                 =    1;                              
    static const short Green                =    2;                            
    static const short Cyan                 =    3;                             
    static const short Red                  =    4;                                 
    static const short Purple               =    5;                     
    static const short Yellow               =    6;                      
    static const short White                =    7;                    
    static const short Gray                 =    8;                   
    static const short Brightblue           =    9;                         
    static const short Brigthgreen          =   10;                          
    static const short Brightcyan           =   11;                          
    static const short Brightred            =   12;                         
    static const short Pink                 =   13;                    
    static const short Brightyellow         =   14;                      
    static const short Brightwhite          =   15;                           

	char get_ch();
	COORD getpivot();
	short getcolor();
	short getbg_color();

	void set_ch(char src);
	void setpivot(COORD src);
	void setcolor(short src);
	void setbg_color(short src);

	void draw();
	void Erase();
	void twinkling(int period,int waiting_period);
	void change_to_choosing_state(short Color);
	Indicate_character();
	Indicate_character(char z,short x, short y, short Color, short bg_Color);
	~Indicate_character();
};



inline char Indicate_character::get_ch()
{
	return ch;
}

inline COORD Indicate_character::getpivot()
{
	return COORD(pivot);
}

inline short Indicate_character::getcolor()
{
	return color;
}

inline short Indicate_character::getbg_color()
{
	return bg_color;
}

inline void Indicate_character::set_ch(char src)
{
	ch = src;
}

inline void Indicate_character::setpivot(COORD src)
{
	pivot = src;
}

inline void Indicate_character::setcolor(short src)
{
	color = src;
}

inline void Indicate_character::setbg_color(short src)
{
	bg_color = src;
}

inline void Indicate_character::draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pivot);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + bg_color*16 );
	putchar(ch);
}

inline void Indicate_character::Erase()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pivot);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	putchar(' ');
}

inline void Indicate_character::twinkling(int period, int waiting_period)
{
	draw();
	Sleep(period);
	Erase();
	Sleep(waiting_period);
}

inline void Indicate_character::change_to_choosing_state(short Color)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pivot);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	putchar(ch);
}

Indicate_character::Indicate_character()
{
}

inline Indicate_character::Indicate_character(char z,short x, short y, short Color, short bg_Color)
{
	ch = z;
	pivot = { x,y };
	color = Color;
	bg_color = bg_Color;
}


Indicate_character::~Indicate_character()
{
}
