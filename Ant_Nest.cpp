//
// Created by Abdullah Shahid on 5/27/2023.
//

#include "Ant_Nest.h"

void *queenThread(void *args)
{
	void **arr = (void **)args;
	RenderWindow *window = (RenderWindow *)arr[0];
	Ant_Nest *obj = (Ant_Nest *)arr[1];
	bool *running = (bool *)arr[3];
	delete[] arr;
	sleep(seconds(5));
	int fighters = 0, workers = 0;
	while (running)
	{
		int random = rand();
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
		sleep(seconds((rand() % 3) + 1));
	}
	return 0;
}

Ant_Nest::Ant_Nest(int x, int y, RenderWindow *window, bool *running)
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
	WorkersCap %= 10;
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
	pthread_t id;
	void **args = new void *[3];
	args[0] = (void *)window;
	args[1] = (void *)this;
	args[3] = running;
	pthread_create(&id, NULL, queenThread, (void *)args);
}

void Ant_Nest::Update(RenderWindow *window)
{
	window->draw(sprite);
	for (int a = 0; a < FightersCap; a++)
	{
		if (Fighters[a] == nullptr)
			break;
		Fighters[a]->Update();
		window->draw(Fighters[a]->sprite);
	}
	for (int a = 0; a < WorkersCap; a++)
	{
		if (Workers[a] == nullptr)
			break;
		Workers[a]->Update();
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