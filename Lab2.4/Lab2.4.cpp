#include"Utilities.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lesson 1. kychka-pc.ru");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("NotCourierSans.otf");

	Dice dice;

	Field input({ 200,200 }, 10, font);
	Button diceMenu("Chow Dice menu", {200 + (CHAR_SIZE_FIELD - 7) * 10 + CHAR_SIZE_Button, 200 + 2 * CHAR_SIZE_Button}, font);
	Panel output("Choose option:", { 200 + (CHAR_SIZE_FIELD - 7) * 10 + CHAR_SIZE_PANEL, 200 }, font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (input.OnClick(mousePosition))
				{
					input.SetSring(window, event);
				}

				diceMenu.SetIsPressed(mousePosition);
				if (diceMenu.IsPressed())
				{
					DiceMenu(window,  font, dice);
					dice.DoExperiment(1000);
					dice.PrintStatistic();
					window.close();
				}
			}
		}

		window.clear();
		diceMenu.Draw(window);
		output.Draw(window);

		window.display();
	}

	return 0;
}
