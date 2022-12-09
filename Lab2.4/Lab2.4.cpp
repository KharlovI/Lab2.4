#include"Utilities.h"
#include"Table.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Random");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("NotCourierSans.otf");
	while (window.isOpen())
	{
		sf::Event event;
		
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		UI(window, font);

		window.clear();
		window.display();
	}

	return 0;
}