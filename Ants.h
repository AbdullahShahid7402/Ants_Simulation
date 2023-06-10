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
	Vector2f NestPosition;
	Sprite sprite;
	float stamina;
	int aggresive, caution, lazy, scared;
	Ants(int, int, float);
	void search(Ants *obj[], int size, bool);
	void goHome(Ants *obj[], int size, bool);
	void Update(Ants *obj[], int size);
	void avoidCollision(Ants *obj[], int size);
	~Ants();
};


#endif //ANTS_H
