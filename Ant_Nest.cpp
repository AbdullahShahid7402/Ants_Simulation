//
// Created by Abdullah Shahid on 5/27/2023.
//

#include "Ant_Nest.h"

void *queenThread(void *args)
{
	int frameLimit = 60;
	void **arr = (void **)args;
	Ant_Nest *obj = (Ant_Nest *)arr[0];
	bool *running = (bool *)arr[1];
	bool *halt = (bool *)arr[2];
	float t = *(int *)arr[3];
	*halt = false;
	t /= 1000;
	srand(t);
	int fighters = 0, workers = 0;
	while (*running)
	{
		usleep((1000 * 1000) / frameLimit);
		int random = rand();
		if (random % 1000 < 985)
			continue;
		random = rand();
		random %= 100;
		random++;
		if (random > 60)
		{
			if (fighters < obj[0].FightersCap)
			{
				obj[0].Fighters[fighters] =
					new Ants((int)obj[0].sprite.getPosition().x, (int)obj[0].sprite.getPosition().y, 1.5);
				fighters++;
			}
		}
		else
		{
			if (workers < obj[0].WorkersCap)
			{
				obj[0].Workers[workers] =
					new Ants((int)obj[0].sprite.getPosition().x, (int)obj[0].sprite.getPosition().y);
				workers++;
			}
		}
	}

	return 0;
}

Ant_Nest::Ant_Nest(int x, int y, RenderWindow *window, bool *running, pthread_t *id)
{
	string file = "Sprites/Nest";
	int random = rand();
	random %= 4;
	random++;
	file += to_string(random);
	file += ".png";
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setPosition(x, y);
	random = rand();
	random %= 181;
	sprite.setRotation(random);
	FightersCap = rand();
	FightersCap %= 20;
	FightersCap += 5;
	WorkersCap %= 40;
	WorkersCap += 20;
	Queen = new Ants *;
	Queen[0] = new Ants((int)sprite.getPosition().x, (int)sprite.getPosition().y);
	Fighters = new Ants *[FightersCap];
	for (int a = 0; a < FightersCap; a++)
	{
		Fighters[a] = nullptr;
	}
	Workers = new Ants *[WorkersCap];
	for (int a = 0; a < WorkersCap; a++)
	{
		Workers[a] = nullptr;
	}
	void *args[4];
	int temp = x * y;
	bool halt = true;
	args[0] = (void *)this;
	args[1] = running;
	args[2] = &halt;
	args[3] = &temp;

	pthread_create(id, NULL, queenThread, args);

	while (halt);

	sleep(seconds(1));
}

void Ant_Nest::Update(RenderWindow *window, Ant_Nest *obj[], int size)
{
	int nsize = 0;
	for (int a = 0; a < size; a++)
	{
		nsize += obj[a][0].FightersCap;
		nsize += obj[a][0].WorkersCap;
	}
	Ants *nobj[nsize];
	for (int a = 0; a < nsize; a++)
		nobj[a] = nullptr;
	int nindex = 0;
	for (int a = 0; a < size; a++)
	{
		for (int b = 0; b < obj[a][0].FightersCap; b++)
		{
			if (obj[a][0].Fighters[b] == nullptr)
				break;
			else
			{
				nobj[nindex++] = obj[a][0].Fighters[b];
			}
		}
		for (int b = 0; b < obj[a][0].WorkersCap; b++)
		{
			if (obj[a][0].Workers[b] == nullptr)
				break;
			else
			{
				nobj[nindex++] = obj[a][0].Workers[b];
			}
		}
	}
	window->draw(sprite);
	for (int a = 0; a < FightersCap; a++)
	{
		if (Fighters[a] == nullptr)
			break;
		Fighters[a]->Update(nobj, nsize);
		window->draw(Fighters[a]->sprite);
	}
	for (int a = 0; a < WorkersCap; a++)
	{
		if (Workers[a] == nullptr)
			break;
		Workers[a]->Update(nobj, nsize);
		window->draw(Workers[a]->sprite);
	}
}

Ant_Nest::~Ant_Nest()
{
	delete Queen[0];
	delete Queen;
	for (int a = 0; a < FightersCap; a++)
	{
		delete Fighters[a];
	}
	for (int a = 0; a < WorkersCap; a++)
	{
		delete Workers[a];
	}
	delete[] Workers;
	delete[] Fighters;
}