#pragma once
#include "Animation.h"
#include "Menu.h"
#include "Game_board.h"
#include "Player.h"
#include <stdio.h>
#include <MMSystem.h>
//#include <mciapi.h>

class Game_manager
{
protected:
	Animation* ani1 = new Animation, *ani2 = new Animation, *ani3 = new Animation;
	Menu* Start_menu;
	Menu* Pausing_menu;
	Game_board* Map;
	Point_State** arr;
	Player *player1 = new Player , *player2=new Player;
	int col, row;
	short d[8] = { -1,1,0,0,-1,1,-1,1 }, c[8] = { 0,0,-1,1,-1,1,1,-1 };

	void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}
public:
	void showmenu();
	void showPausing_menu();
	void init();
	void run_animation();
	void Play();
	bool iswin(bool isplayer1);
	Game_manager();
	~Game_manager();
};



inline void Game_manager::showmenu()
{
	Start_menu = new Menu(45, 10);
	Start_menu->Add((char*)"NEW GAME", Indicate_character::Brightcyan);
	Start_menu->Add((char*)"RESUME", Indicate_character::Brightcyan);
	//Start_menu->Add((char*)"OPTION", Indicate_character::Brightcyan);
	Start_menu->Draw();
	PlaySound(TEXT("melody.wav"), NULL, SND_LOOP | SND_ASYNC);
	Start_menu->Choose();
	PlaySound(NULL, NULL, 0);

	switch (Start_menu->getchoosing_number())
	{
	case 0:
	{
		std::vector<int> vt;
		String_board a((char*)"Size of map: [     ,     ]", 15, 15, Indicate_character::Brightcyan);
		a.Draw();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 30,15 });
		scanf_s("%d", &row); int tmp = row;
		while (tmp)
		{
			vt.emplace_back(tmp % 10);
			tmp /= 10;
		}
		for (int id = vt.size() - 1; id >= 0; --id)
			a.Add(new Indicate_character((char)(vt[id] - '0'), 30 + (short)vt.size() - 1 - id, 15, Indicate_character::Brightcyan, Indicate_character::Black));
		vt.clear();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 36,15 });
		scanf_s("%d", &col);
		tmp = col;
		while (tmp)
		{
			vt.emplace_back(tmp % 10);
			tmp /= 10;
		}
		for (int id = vt.size() - 1; id >= 0; --id)
			a.Add(new Indicate_character((char)(vt[id] - '0'), 36 + (short)vt.size() - 1 - id, 15, Indicate_character::Brightcyan, Indicate_character::Black));
		a.clrscr();
		Map = new Game_board(1, 1, 3 * row, 5 * col);
		Map->Init_border(row, col);
		break;
	}
	case 1:
	{
		Map = new Game_board;
		Map->read_from_file((char*)"Match.txt");
		row = Map->getheight() / 3;
		col = Map->getwidth() / 5;
		break;
	}
	}
}

inline void Game_manager::showPausing_menu()
{
	Pausing_menu->Draw();
	Pausing_menu->Choose();
	switch (Pausing_menu->getchoosing_number())
	{
	case 0:
	{
		std::vector<int> vt;
		String_board a((char*)"Size of map: [     ,     ]", 15, 15, Indicate_character::Brightcyan);
		a.Draw();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 30,15 });
		scanf_s("%d", &row); int tmp = row;
		while (tmp)
		{
			vt.emplace_back(tmp % 10);
			tmp /= 10;
		}
		for (int id = vt.size() - 1; id >= 0; --id)
			a.Add(new Indicate_character((char)(vt[id] - '0'), 30 + (short)vt.size() - 1 - id, 15, Indicate_character::Brightcyan, Indicate_character::Black));
		vt.clear();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 36,15 });
		scanf_s("%d", &col);
		tmp = col;
		while (tmp)
		{
			vt.emplace_back(tmp % 10);
			tmp /= 10;
		}
		for (int id = vt.size() - 1; id >= 0; --id)
			a.Add(new Indicate_character((char)(vt[id] - '0'), 36 + (short)vt.size() - 1 - id, 15, Indicate_character::Brightcyan, Indicate_character::Black));
		a.clrscr();
		Map = new Game_board(1, 1, 3 * row, 5 * col);
		Map->Init_border(row, col);
		break;
	}
	case 1:
	{
		Map->save_into_file((char*)"Match.txt");
		exit(0);
	}
	}
}

inline void Game_manager::init()
{
	Pausing_menu = new Menu(25,10);
	Pausing_menu->Add((char*)"NEW GAME", Indicate_character::Brightcyan);
	Pausing_menu->Add((char*)"SAVE AND EXIT", Indicate_character::Brightcyan);

	arr = new Point_State*[row];
	for (int i = 0; i < row; ++i)
		arr[i] = new Point_State[col];
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j) arr[i][j] = NONE;

	for (unsigned int i = (row + 1)*Map->getwidth() + (col + 1)*Map->getheight(); i < Map->getmatrix().size(); ++i)
	{
		COORD tmp = Map->getmatrix()[i]->getpivot();
		arr[(tmp.Y - 2) / 3][(tmp.X - 2) / 5] = (Map->getmatrix()[i]->get_ch() == 'X' ? SYMBOL1 : SYMBOL2);
	}
}

inline void Game_manager::run_animation()
{
	PlaySound(TEXT("animation_melody.wav"), NULL, SND_LOOP | SND_ASYNC);
	ani1->setstep(35);
	ptr = f1;
	ani1->Init(ptr);
	ptr = g1;
	ani1->Run(ptr, 60, 0, true);

	ani2->setstep(12);
	ptr = f2;
	ani2->Init(ptr);
	ptr = g2;
	ani2->Run(ptr, 100, 123, false);
	Sleep(500);

	ani3->setstep(16);
	ptr = f3;
	ani3->Init(ptr);
	ptr = g3;
	ani3->Run(ptr, 40, 123, false);
	Sleep(1000);

	ani2->getMap()->clrscr();
	ani3->getMap()->clrscr();

	PlaySound(NULL, NULL, 0);

}

inline void Game_manager::Play()
{
	run_animation();
	showmenu();
	init();
	Map->Draw(); 
	bool isexit=false;
	for (int i = Map->getmatrix().size() - (row+1)*Map->getwidth()-(col+1)*Map->getheight(); i <= row*col; ++i)
		if (i % 2 == 0)
		{
			player1->human_choose(isexit, true, { 1,1 }, arr, row, col);
			if (isexit)
				showPausing_menu();
			Indicate_character* element = new Indicate_character;
			*element = *(player1->getpoint());
			Map->Add(element);
			if (iswin(true))
			{
				Map->clrscr();
				puts("PLAYER1 WIN");
				return;
			}
		}
		else
		{
			player2->human_choose(isexit, false, { 1,1 }, arr, row, col);
			if (isexit)
				showPausing_menu();
			Indicate_character* element = new Indicate_character;
			*element = *(player2->getpoint());
			Map->Add(element);
			if (iswin(false))
			{
				Map->clrscr();
				puts("PLAYER2 WIN");
				return;
			}
		}
}

inline bool Game_manager::iswin(bool isplayer1)
{
	Indicate_character* ptr = (isplayer1 ? player1 : player2)->getpoint();
	int x = (ptr->getpivot().Y - 2) / 3;
	int y = (ptr->getpivot().X - 2) / 5;
	for (short i = 0; i <= 7; i+=2)
	{
		short cnt = 1;
		for (short j = i; j <= i + 1; ++j)
		{
			int x_ = x, y_ = y;
			while (true)
			{
				int xx = x_ + d[j];
				int yy = y_ + c[j];
				if (xx >= 0 && xx < row&&yy >= 0 && yy < col&&arr[xx][yy] == (isplayer1 ? SYMBOL1 : SYMBOL2))
					++cnt, x_ = xx, y_ = yy;
				else break;
			}
		}
		if (cnt == 5) return true;
	}
	return false;
}

Game_manager::Game_manager()
{
	ShowConsoleCursor(false);
}


Game_manager::~Game_manager()
{
	delete(ani1);
	delete(ani2);
	delete(ani3);
	delete(Start_menu);
	delete(Pausing_menu);
	delete(Map);
	for (int i = 0; i < row; ++i)
		delete[] arr[i];
	delete[] arr;
	delete(player1);
	delete(player2);
}
