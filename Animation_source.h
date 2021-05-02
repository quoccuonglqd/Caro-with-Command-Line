#pragma once

char Map[13][35] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					 {' ',' ',' ','=','=','=',' ',' ',' ',' ',' ','=','=','=','=','=',' ',' ',' ','=','=','=','=','=','=',' ',' ',' ',' ',' ','=','=','=',' ',' '},
					 {' ',' ','=','=','=','=','=',' ',' ',' ','=','=','=','=','=','=','=',' ',' ','=','=','=','=','=','=','=',' ',' ',' ','=','=','=','=','=',' '},
					 {' ','=','=',' ',' ',' ','=','=',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ',' ','=',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ','=','=',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ',' ','=',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ',' ','=',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ',' ',' ',' ',' ',' ','=','=','=','=','=','=',' ',' ','=','=','=','=','=','=','=',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ',' ','=','=',' ',' ','=','=','=',' ',' ',' ',' ',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ',' ','=','=',' ',' ','=','=','=','=','=',' ',' ',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ',' ',' ',' ',' ','=','=',' ',' ',' ','=','=',' ',' ','=','=',' ',' ','=','=',' ',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ','=','=',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ','=','=',' ',' ','=','=',' ',' ',' ','=','='},
					 {' ',' ','=','=','=','=','=',' ',' ',' ','=','=','=','=','=','=','=',' ',' ','=','=',' ',' ',' ',' ','=',' ',' ',' ','=','=','=','=','=',' '},
					 {' ',' ',' ','=','=','=',' ',' ',' ',' ',' ','=','=','=','=','=','=',' ',' ','=','=',' ',' ',' ',' ','=',' ',' ',' ',' ','=','=','=',' ',' '} };

bool avail[13][35];

void(*ptr)(std::vector<Indicate_character*>&);

short row[4] = { -1,0,1,0 }, col[4] = { 0,-1,0,1 };

void f1(std::vector<Indicate_character*>& vt)
{
	vt.emplace_back(new Indicate_character('X', 25, 14, Indicate_character::Purple, Indicate_character::Black));
	vt.emplace_back(new Indicate_character('O', 96, 14, Indicate_character::Brightyellow, Indicate_character::Black));
}

void g1(std::vector<Indicate_character*>& vt)
{
	vt.emplace_back(new Indicate_character('X', vt[0]->getpivot().X + 1, vt[0]->getpivot().Y, Indicate_character::Purple, Indicate_character::Black));
	vt.emplace_back(new Indicate_character('O', vt[1]->getpivot().X - 1, vt[0]->getpivot().Y, Indicate_character::Brightyellow, Indicate_character::Black));
	delete(vt[0]);
	delete(vt[1]);
	vt.erase(vt.begin(), vt.begin() + 2);
}

void f2(std::vector<Indicate_character*>& vt)
{
	vt.emplace_back(new Indicate_character(' ', 60, 14, Indicate_character::White, Indicate_character::Brightblue));
}

void g2(std::vector<Indicate_character*>& vt)
{

	int len = abs(vt.back()->getpivot().X - 60) + abs(vt.back()->getpivot().Y - 14);
	++len;
	if (len > 15) return;
	for (int i = -len + 1; i < len; ++i) if (i)
	{
		vt.emplace_back(new Indicate_character(' ', 60 - i, 14 - (len - abs(i)), Indicate_character::White, Indicate_character::Brightblue));
		vt.emplace_back(new Indicate_character(' ', 60 - i, 14 + (len - abs(i)), Indicate_character::White, Indicate_character::Brightblue));
	}

	vt.emplace_back(new Indicate_character(' ', 60 - len, 14, Indicate_character::White, Indicate_character::Brightblue));
	vt.emplace_back(new Indicate_character(' ', 60 + len, 14, Indicate_character::White, Indicate_character::Brightblue));
	vt.emplace_back(new Indicate_character(' ', 60, 14 - len, Indicate_character::White, Indicate_character::Brightblue));
	vt.emplace_back(new Indicate_character(' ', 60, 14 + len, Indicate_character::White, Indicate_character::Brightblue));
}

void f3(std::vector<Indicate_character*>& vt)
{
	vt.emplace_back(new Indicate_character(' ', 44, 14, Indicate_character::White, Indicate_character::Red)); avail[7][2] = true;
	vt.emplace_back(new Indicate_character(' ', 52, 14, Indicate_character::White, Indicate_character::Red)); avail[7][10] = true;
	vt.emplace_back(new Indicate_character(' ', 63, 14, Indicate_character::White, Indicate_character::Red)); avail[7][21] = true;
	vt.emplace_back(new Indicate_character(' ', 71, 14, Indicate_character::White, Indicate_character::Red)); avail[7][29] = true;
}

void g3(std::vector<Indicate_character*>& vt)
{
	int len = vt.size();
	Indicate_character* element;
	for (int i = 0; i < len; ++i)
	{
		element = vt[i];
		for (short k = 0; k < 4; ++k)
		{
			short xx = element->getpivot().X + row[k] - 42;
			short yy = element->getpivot().Y + col[k] - 7;
			if (avail[yy][xx] == 0 && yy > 0 && yy <= 13 && xx > 0 && xx <= 34 && Map[yy][xx] == '=')
			{
				avail[yy][xx] = true;
				vt.emplace_back(new Indicate_character(' ', 42 + xx, 7 + yy, Indicate_character::White, Indicate_character::Red));
			}
		}
	}
}