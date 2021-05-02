#pragma once
#include "Indicate_character.h"
#include <vector>
#include <fstream>

class Indicate_board
{
protected:
	std::vector<Indicate_character*> matrix;
	short height;
	short width;
	COORD pivot;
public:
	short getheight();
	short getwidth();
	COORD getpivot();
	std::vector<Indicate_character*>& getmatrix();

	void setheight(short src);
	void setwidth(short src);
	void setpivot(COORD src);

	void Add(Indicate_character* src);
	void Draw();
	void clrscr();
	void read_from_file(char* file_name);
	void save_into_file(char* file_name);

	Indicate_board(short x, short y, short Height, short Width);
	Indicate_board();
	~Indicate_board();
};



inline short Indicate_board::getheight()
{
	return height;
}

inline short Indicate_board::getwidth()
{
	return width;
}

inline COORD Indicate_board::getpivot()
{
	return COORD(pivot);
}

inline std::vector<Indicate_character*>& Indicate_board::getmatrix()
{
	return matrix;
}

inline void Indicate_board::setheight(short src)
{
	height = src;
}

inline void Indicate_board::setwidth(short src)
{
	width = src;
}

inline void Indicate_board::setpivot(COORD src)
{
	pivot = src;
}

inline void Indicate_board::Add(Indicate_character * src)
{
	matrix.emplace_back(src);
}

inline void Indicate_board::Draw()
{
	for (Indicate_character* element : matrix)
		element->draw();
}

inline void Indicate_board::clrscr()
{
	for (Indicate_character* element : matrix)
		element->Erase();
}

inline void Indicate_board::read_from_file(char * file_name)
{
	std::ifstream is;
	is.open(file_name, std::ifstream::in);
	is >> height >> width;
	is >> pivot.X >> pivot.Y;
	short x, y, z;
	char ch;
	while (is >> ch >> x >> y >> z)
	{
		Indicate_character* tmp = new Indicate_character(ch, x, y, z, Indicate_character::Black);
		matrix.emplace_back(tmp);
	}
}

inline void Indicate_board::save_into_file(char * file_name)
{
	std::ofstream os;
	os.open(file_name, std::ofstream::trunc);
	os << height << ' ' << width << ' ' << pivot.X << ' ' << pivot.Y << '\n';
	for (Indicate_character* element : matrix)
		os << element->get_ch() << ' ' << element->getpivot().X << ' ' << element->getpivot().Y << ' ' << element->getcolor() << '\n';

}

inline Indicate_board::Indicate_board(short x, short y, short Height, short Width)
{
	pivot = { x,y };
	height = Height;
	width = Width;
}

Indicate_board::Indicate_board()
{
}


Indicate_board::~Indicate_board()
{
	for (auto &element : matrix)
		delete(element);
	matrix.clear();
}
