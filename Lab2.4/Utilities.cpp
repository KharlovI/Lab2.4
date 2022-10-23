#include "Utilities.h"
#include<map>
#include<cmath>
#include<sstream>

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

std::string DoubleToString(const double& value)
{
	std::ostringstream answer;
	answer << value;
	return answer.str();
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

std::vector<Event2> SetEventProbabilitys(sf::RenderWindow& w, sf::Font& font, int eventCount)
{
	std::vector<Event2> answer(0);
	Panel panel1("Enter probability:", {200,200}, font);
	Panel panel2("Max probability: 1", { 200,200 - (CHAR_SIZE_FIELD - 7) * 3 }, font);
	Field field({200 + (CHAR_SIZE_FIELD - 7) * 20 ,200}, 10, font );

	double maxValue = 1;
	double currentProbability = 0;
	int counter = 1;

	std::string temp;

	while (w.isOpen())
	{
		sf::Event event;

		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return answer;
			}

			if (answer.size() == eventCount)
				return answer;

			if (maxValue == 0)
			{
				for (int i = counter; i <= eventCount; i++)
				{
					answer.push_back({ 0, i });
				}
				return answer;
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				if (field.OnClick(mousePosition))
				{
					field.SetSring(w, event);
					temp = field.GetInput();				
					currentProbability = StringToDouble(temp);

					if (currentProbability <= 1 || currentProbability <= maxValue)
					{
						maxValue -= currentProbability;
						panel2.SetText("Max probability:" + DoubleToString(maxValue));
						answer.push_back({ currentProbability, counter });
						counter++;

					}
					
				}
			}
		}
		w.clear();
		panel1.Draw(w);
		panel2.Draw(w);
		field.Draw(w);
		w.display();
	}
}


void DiceMenu(sf::RenderWindow& w, sf::Font& font, Dice& dice)
{
	Panel panel("Select variant:", { 200, 200 }, font);
	Button button1("Set equel probability", { 200 + (CHAR_SIZE_Button - 7) * 17, 200 }, font);
	Button button2("Set probability", { 200 + (CHAR_SIZE_Button - 7) * 17, 200 + (CHAR_SIZE_Button - 7) * 3 }, font);

	bool flag = 0;

	while (w.isOpen())
	{
		sf::Event event;

		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);
				button1.SetIsPressed(mousePosition);
				button2.SetIsPressed(mousePosition);
				int count = 0;

				if (button1.IsPressed())
				{
					count = EventCount(w, font);
					Dice newDice(count, 1, w, event, font);
					dice = newDice;
					flag = 1;
					break;
				}
				else if (button2.IsPressed())
				{
					count = EventCount(w, font);
					Dice newDice(count, 0, w, event, font);
					dice = newDice;
					flag = 1;
					break;
				}
			}
		}

		w.clear();
		panel.Draw(w);
		button1.Draw(w);
		button2.Draw(w);
		w.display();

		if (flag)
			break;
	}

	dice.MakeEvent(w, font);
}

int EventCount(sf::RenderWindow& w, sf::Font& font)
{
	int count = 0;
	Panel panel("Enter event count:", { 200,200 }, font);
	Field field({ 200 + (CHAR_SIZE_FIELD - 7) * 20 , 200 }, 10, font);

	while (w.isOpen())
	{
		sf::Event event;

		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return count;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				if (field.OnClick(mousePosition))
				{
					field.SetSring(w, event);
					count = StringToDouble(field.GetInput());
					return count;
				}
			}
		}

		w.clear();
		panel.Draw(w);
		field.Draw(w);
		w.display();
	}
}
int Value(sf::RenderWindow& w, sf::Font& font)
{
	int value = -1;

	Panel panel("Enter integer value:", {200,200}, font);
	Field field({200,200 + (CHAR_SIZE_FIELD - 7) * 21},10,font);

	while (w.isOpen())
	{
		sf::Event event;

		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return value;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				if (field.OnClick(mousePosition))
				{
					field.SetSring(w, event);
					value = StringToDouble(field.GetInput());
					return value;
				}
			}
		}

		w.clear();
		panel.Draw(w);
		field.Draw(w);
		w.display();
	}
}

bool VectoreContainValue(std::vector<Event2> v, int value)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].GetValue() == value)
			return 1;
	}

	return 0;
}

std::vector<Event2> DifferentEvents(std::vector<Event2> e1, std::vector<Event2> e2)
{
	std::vector<Event2> answer(0);

	int size1 = e1.size();
	int size2 = e2.size();
	int answerSize = 0;

	for (int i = 0; i < size1; i++)
	{
		if (VectoreContainValue(answer, e1[i].GetValue()) == 0)
			answer.push_back(e1[i]);
	}
	for (int i = 0; i < size2; i++)
	{
		if (VectoreContainValue(answer, e2[i].GetValue()) == 0)
			answer.push_back(e2[i]);
	}

	return answer;
}
std::vector<Event2> SameEvents(std::vector<Event2> e1, std::vector<Event2> e2)
{
	int size1 = e1.size();
	int size2 = e2.size();

	std::vector<Event2> answer(0);

	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (e1[i].GetValue() == e2[j].GetValue())
			{
				if (VectoreContainValue(answer, e1[i].GetValue()) == 0)
					answer.push_back(e1[i]);
			}
		}
	}

	return answer;
}