#pragma once
#include "Indicate_board.h"
#include <stdlib.h>
#include "Animation_source.h"



class Animation
{
protected:
	int step;
	Indicate_board* Map;
public:
	int getstep();
	void setstep(int src);
	Indicate_board* getMap();
	void Init(void (*ptr)(std::vector<Indicate_character*>&));
	void Run(void (*ptr)(std::vector<Indicate_character*>&), int running_period, int finishing_period,bool willbeerase);
	Animation();
	~Animation();
};



inline int Animation::getstep()
{
	return step;
}

inline void Animation::setstep(int src)
{
	step = src;
}

inline Indicate_board * Animation::getMap()
{
	return Map;
}

inline void Animation::Init(void (*ptr)(std::vector<Indicate_character*>&))
{
	ptr(Map->getmatrix());
}

inline void Animation::Run(void (*ptr)(std::vector<Indicate_character*>&),int running_period,int finishing_period, bool willbeerase)
{
	for (int i = 1; i < step; ++i)
	{
		Map->Draw();
		Sleep(running_period);
		if (willbeerase) Map->clrscr();
		ptr(Map->getmatrix());
	}
	Map->Draw();
	Sleep(finishing_period);
	if (willbeerase) Map->clrscr();
}

Animation::Animation()
{
	Map = new Indicate_board();
}


Animation::~Animation()
{
	delete(Map);
}
