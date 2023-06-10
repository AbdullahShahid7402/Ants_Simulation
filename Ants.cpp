//
// Created by Abdullah Shahid on 5/27/2023.
//

#include "Ants.h"

Ants::Ants(int x, int y, float s = 1)
{
	texture.loadFromFile("Sprites/Ant.png");
	sprite.setTexture(texture);
	Vector2u size = texture.getSize();
	stamina = 100;
	sprite.setScale(s, s);
	sprite.setPosition((float)x, (float)y);
	int random = rand();
	NestPosition.x = x;
	NestPosition.y = y;
	random %= 181;
	sprite.setRotation(random);
	sprite.setOrigin(size.x / 2, size.y / 2);
	aggresive = (rand() % 101);
	caution = (rand() % 101);
	lazy = (rand() % 101);
	scared = (rand() % 101);
}
void Ants::Update(Ants *obj[], int size)
{
	bool dont = true;

	Vector2f direction = NestPosition - sprite.getPosition();
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance > 100)
		dont = false;

	if (stamina > 0)
	{
		search(obj, size, dont);
	}
	else
	{
		goHome(obj, size, dont);
	}
}

void Ants::avoidCollision(Ants *obj[], int size)
{
	for (int a = 0; a < size; a++)
	{
		if (obj[a] == nullptr || &(obj[a][0]) == nullptr)
			break;
		if (obj[a] == this)
		{
			continue;
		}
		if (sprite.getGlobalBounds().intersects(obj[a][0].sprite.getGlobalBounds()))
		{
			sprite.rotate((1.61803398875 * 15));
		}
	}
}

void Ants::search(Ants *obj[], int size, bool dont)
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
	Move.y = 1 * sin(angleInRadians);
	Move.x = 1 * cos(angleInRadians);
	if (sprite.getPosition().x + Move.x > 1280 || sprite.getPosition().x + Move.x < 0)
	{
		Move.x = -Move.x;
		sprite.rotate(1.61803398875 * 15);
	}
	if (sprite.getPosition().y + Move.y > 720 || sprite.getPosition().y + Move.y < 0)
	{
		Move.y = -Move.y;
		sprite.rotate(1.61803398875 * 15);
	}
	if (rand() % 201 <= lazy)
		return;
	if (!dont)
		avoidCollision(obj, size);
	sprite.move(Move);
	stamina -= (rand() % 100) / 1000.0;
	if (stamina <= 0)
		stamina = -100;
}

void Ants::goHome(Ants *obj[], int size, bool dont)
{
	float speed = 1;
	if (rand() % 100 < lazy)
		speed /= 2;

	Vector2f direction = NestPosition - sprite.getPosition();
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1)
	{
		float angle = atan2(direction.y, direction.x);
		angle = angle * 180.0f / M_PI;

		if ((rand() % 100) < 85)
			angle += (rand() % 2 == 0) ? ((rand() % 10)) : (-(rand() % 10));
		sprite.setRotation(angle + 90);
		Vector2f Move(cos(angle * M_PI / 180.0f), sin(angle * M_PI / 180.0f));
		if (!dont)
			avoidCollision(obj, size);
		sprite.move(Move * speed);
		stamina -= (rand() % 100) / 1000.0;
	}
	else
	{
		stamina += (rand() % 200) / 1000.0;
		if (stamina >= 0)
			stamina = 100;
	}

}

Ants::~Ants()
{}