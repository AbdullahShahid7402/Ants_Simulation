//
// Created by Abdullah Shahid on 5/27/2023.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

#ifndef ANTS_H
#define ANTS_H


class Ants
{
private:
	Texture texture;
public:
	Sprite sprite;
	int aggresive,caution,lazy,scared;
	Ants(int, int, float);
	void Update();
	~Ants();
};


#endif //ANTS_H
