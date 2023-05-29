//
// Created by Abdullah Shahid on 5/27/2023.
//
#include "Ants.cpp"
#include <pthread.h>
#include <ctime>

#ifndef ANT_NEST_H
#define ANT_NEST_H


class Ant_Nest
{
private:
	Texture texture;
public:
	Sprite sprite;
	Ants **Queen;
	Ants **Workers;
	Ants **Fighters;
	int WorkersCap, FightersCap;

	Ant_Nest(int, int, RenderWindow *, bool *);
	void Update(RenderWindow *);
	~Ant_Nest();
};


#endif //ANT_NEST_H
