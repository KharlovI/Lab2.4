#include "Utilities.h"
#include<map>
#include<cmath>

double StringToDouble(std::string string)
{
	int length = string.size();
	double answer = 0;

	std::map<char, int> SToD = { {'0',0}, {'1', 1}, {'2',2}, {'3',3}, {'4',4}, 
								 {'5',5}, {'6',6},  {'7',7}, {'8',8}, {'9',9} };

	int commaIndex = -1;
	for (int i = 0; i < length; i++)
	{
		if (string[i] == ',')
			commaIndex = i;
	}

	if (commaIndex == -1)
		commaIndex = length;

	for (int i = 0; i < commaIndex; i++)
	{
		auto pointer = SToD.find(string[i]);

		answer += (double)pointer._Ptr->_Myval.second * pow(10, commaIndex - i - 1);
	}

	for (int j = commaIndex + 1; j < length; j++)
	{
		auto pointer = SToD.find(string[j]);

		answer += (double)pointer._Ptr->_Myval.second / pow(10, j - commaIndex);
	}
	return answer;
}

void SetDiagramConfigs(Diagram& d, Dice& e)
{
	int frequentIndex = e.RarestAndFrequent()[1] - 1;

	d.SetCountOfShapes(e.GetCountEvent());
	d.SetScale(e.CountEveryValu()[frequentIndex]);
	d.SetWidth(e.GetCountEvent());
	d.SetHeight(e.CountEveryValu());
	d.SetDiagram();
}

void DrawDiagram(Diagram& d, sf::RenderWindow& w)
{
	d.Print(w);
}

char& IntToChar(sf::Keyboard::Key& key)
{
	char answer = ' ';

	switch (key)
	{
	case 0:
		answer = 'A';
		break;
	case 1:
		answer = 'B';
		break;
	case 2:
		answer = 'C';
		break;
	case 3:
		answer = 'D';
		break;
	case 4:
		answer = 'E';
		break;
	case 5:
		answer = 'F';
		break;
	case 6:
		answer = 'G';
		break;
	case 7:
		answer = 'H';
		break;
	case 8:
		answer = 'I';
		break;
	case 9:
		answer = 'J';
		break;
	case 10:
		answer = 'K';
		break;
	case 11:
		answer = 'L';
		break;
	case 12:
		answer = 'M';
		break;
	case 13:
		answer = 'N';
		break;
	case 14:
		answer = 'O';
		break;
	case 15:
		answer = 'P';
		break;
	case 16:
		answer = 'Q';
		break;
	case 17:
		answer = 'R';
		break;
	case 18:
		answer = 'S';
		break;
	case 19:
		answer = 'T';
		break;
	case 20:
		answer = 'U';
		break;
	case 21:
		answer = 'V';
		break;
	case 22:
		answer = 'W';
		break;
	case 23:
		answer = 'X';
		break;
	case 24:
		answer = 'Y';
		break;
	case 25:
		answer = 'Z';
		break;
	case 26:
		answer = '0';
		break;
	case 27:
		answer = '1';
		break;
	case 28:
		answer = '2';
		break;
	case 29:
		answer = '3';
		break;
	case 30:
		answer = '4';
		break;
	case 31:
		answer = '5';
		break;
	case 32:
		answer = '6';
		break;
	case 33:
		answer = '7';
		break;
	case 34:
		answer = '8';
		break;
	case 35:
		answer = '9';
		break;
	case 49:
		answer = ',';
		break;
	case 58:
		answer = 'e';
		break;
	case 59:
		answer = 'b';
		break;
	default:
		answer = 'e';
	}

	return answer;
}

std::vector<Event2> Event(int countOfSimpleEvent, sf::RenderWindow& window, sf::Event& event, sf::Font& font)
{
	std::vector<Event2> temp;
	double currentMaxProb = 1;

	double prob = 0;

	Field field({200,200}, 10, font );
	Panel panel("Enter probability", { 200, 200 - 18 * (CHAR_SIZE_PANEL - 7) }, font);

	for (int i = 0; i < countOfSimpleEvent; i++)
	{
		std::cout << currentMaxProb << std::endl;

		while (window.isOpen())
		{
			window.clear();
			field.Draw(window);
			panel.Draw(window);
			window.display();

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					if (field.OnClick(mousePosition))
					{
						field.SetSring(window, event);
						prob = StringToDouble(field.GetInput());
						temp.push_back({ prob, i });
					}
				}
			}
		}
	}

	return temp;
}

void StartDiceMenu(sf::RenderWindow& window, sf::Event& event, sf::Font& font, Dice& original)
{
	Field enterProb({200, 200 - (CHAR_SIZE_Button - 7) * 7 }, 5, font);
	Panel text("Choose option:",{200, 200}, font);
	Button eaquelProb("Set equiprobable events", { 200,200 + (CHAR_SIZE_Button - 7) * 4 }, font);
	Button userProb("Enter probability", { 200, 200 + (CHAR_SIZE_Button - 7) * 7 }, font);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				eaquelProb.SetIsPressed(mousePosition);
				userProb.SetIsPressed(mousePosition);

				if (eaquelProb.IsPressed())
				{
					int countOfSimpleEvent = -1;

					eaquelProb.Delete();
					userProb.Delete();
					text.SetText("Enter count of toss");

					while (countOfSimpleEvent == -1 && window.isOpen())
					{
						window.pollEvent(event);

						if (event.type == sf::Event::Closed)
						{
							window.close();
						}

						if (event.type == sf::Event::MouseButtonPressed)
						{
							mousePosition = sf::Mouse::getPosition(window);
							if (enterProb.OnClick(mousePosition))
							{
								enterProb.SetSring(window, event);
								countOfSimpleEvent = StringToDouble(enterProb.GetInput());
							}
						}

						window.clear();
						enterProb.Draw(window);
						window.display();
					}

					text.Clean();
					Dice dice(countOfSimpleEvent, 1, window,event,font);
					original = dice;
					return;
				}

				if (userProb.IsPressed())
				{
					int countOfSimpleEvent = -1;

					while (countOfSimpleEvent == -1 && window.isOpen())
					{
						window.pollEvent(event);

						if (event.type == sf::Event::Closed)
						{
							window.close();
							return;
						}

						if (event.type == sf::Event::MouseButtonPressed)
						{
							mousePosition = sf::Mouse::getPosition(window);
							if (enterProb.OnClick(mousePosition))
							{
								enterProb.SetSring(window, event);
								countOfSimpleEvent = StringToDouble(enterProb.GetInput());
							}
						}

						window.clear();
						enterProb.Draw(window);
						window.display();
					}

					text.Clean();

					Dice dice(countOfSimpleEvent, 0, window, event, font);
					original = dice;
					return;
				}
			}
		}
		window.clear();
		text.Draw(window);
		eaquelProb.Draw(window);
		userProb.Draw(window);

		window.display();
	}
}
