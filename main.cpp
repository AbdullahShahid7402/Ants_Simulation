#include <SFML/Graphics.hpp>
#include "Ant_Nest.cpp"
using namespace sf;

int main()
{
	srand(time(0));
	const int width = 1280;
	const int height = 720;

	RenderWindow window(VideoMode(width, height), "SFML Window");

	const int NestCap = 5;
	pthread_t *threadNo = new pthread_t[NestCap];
	Ant_Nest **Nest = new Ant_Nest *[NestCap]();

	for (int a = 0; a < NestCap; a++)
	{
		Nest[a] = nullptr;
	}

	bool running = true;

	while (running && window.isOpen())
	{
		for (int a = 0; a < NestCap; a++)
		{
			if (Nest[a] == nullptr)
			{
				int x = rand();
				int y = rand();
				x %= width - (64 * 2);
				y %= height - (64 * 2);
				x += 64;
				y += 64;
				Nest[a] = new Ant_Nest(x, y, &window, &running, &threadNo[a]);
				usleep((a * 100 * 1000));
			}
		}
		int frameLimit = 60;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				running = false;
				window.close();
				break;
			}
		}

		window.clear(Color::White);

		for (int a = 0; a < NestCap; a++)
		{

			if (Nest[a] != nullptr)
				Nest[a][0].Update(&window, Nest, NestCap);
		}

		// Draw SFML objects here
		window.display();

		sleep(milliseconds(1000 / frameLimit));
	}

	for (int a = 0; a < NestCap; a++)
	{
		delete Nest[a];
		pthread_join(threadNo[a], NULL);
	}
	delete[] Nest;

	return 0;
}
