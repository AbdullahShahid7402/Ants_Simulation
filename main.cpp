#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	RenderWindow *window = new RenderWindow(sf::VideoMode(800, 600), "SFML Window");
	Clock clock;

	while (window->isOpen())
	{
		Time elapsed = clock.getElapsedTime();
		int frameLimit = 60;
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		window->clear(Color::Black);
		// Draw SFML objects here
		window->display();

		sleep(milliseconds(1000 / frameLimit));
	}

	return 0;
}
