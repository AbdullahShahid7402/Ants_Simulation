//
// Created by Abdullah Shahid on 5/27/2023.
//

#include "Ants.h"

Ants::Ants(int x, int y, float s = 1)
{
	texture.loadFromFile("Sprites/Ant.png");
	sprite.setTexture(texture);
	Vector2u size = texture.getSize();
	sprite.setScale(s, s);
	sprite.setPosition((float)x, (float)y);
	int random = rand();
	random %= 181;
	sprite.setRotation(random);
	sprite.setOrigin(size.x / 2, size.y / 2);
	aggresive = (rand() % 101);
	caution = (rand() % 101);
	lazy = (rand() % 101);
	scared = (rand() % 101);
}
void Ants::Update()
{
	Vector2f Move;
	int random = rand() % 1000;
	if (random > 805)
	{
		random = rand();
		random %= 10;
		random++;
		if (rand() % 2 == 0)
			random *= -1;
		sprite.rotate(random);
	}
	float angleInRadians = (sprite.getRotation() - 90) * M_PI / 180.0;
	Move.y = 0.5 * sin(angleInRadians);
	Move.x = 0.5 * cos(angleInRadians);
	if (sprite.getPosition().x + Move.x > 1280 || sprite.getPosition().x + Move.x < 0)
	{
		Move.x = -Move.x;
		sprite.setRotation((1.61803398875 * 15) + sprite.getRotation());
	}
	if (sprite.getPosition().y + Move.y > 720 || sprite.getPosition().y + Move.y < 0)
	{
		Move.y = -Move.y;
		sprite.setRotation((1.61803398875 * 15) + sprite.getRotation());
	}
	if (rand() % 201 <= lazy)
		return;
	sprite.move(Move);
}
Ants::~Ants()
{}