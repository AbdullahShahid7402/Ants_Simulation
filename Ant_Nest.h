//
// Created by Abdullah Shahid on 5/27/2023.
//
#include "Ants.cpp"

#ifndef ANT_NEST_H
#define ANT_NEST_H


class Ant_Nest
{
private:
	Ants *Queen;
	Ants *Workers;
	Ants *Fighters;
public:
	Ant_Nest(int, int);
};


#endif //ANT_NEST_H
