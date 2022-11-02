#include"Utilities.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lesson 1. kychka-pc.ru");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("NotCourierSans.otf");

	while (window.isOpen())
	{
		sf::Event event;
		
		UI(window, font);

		window.clear();

		window.display();
	}

	return 0;
}