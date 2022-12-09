#include "Utilities.h"
#include<map>
#include<cmath>
#include<sstream>

constexpr int NORMALISED_SIZE = CHAR_SIZE_Button - 7;

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


char& IntToChar(sf::Keyboard::Key& key)
{
	char answer = ' ';

	switch (key)
	{
	/*case 0:
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
		break;*/
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
		answer = ' ';
	}

	return answer;
}

std::vector<Event2> SetEventProbabilitys(sf::RenderWindow& w, sf::Font& font, int eventCount)
{
	std::vector<Event2> answer(0);
	Panel panel1("Enter probability:    ", {0,200}, font);
	Panel panel2("Max probability: 1    ", { NORMALISED_SIZE * 23,200 - NORMALISED_SIZE * 6 }, font);
	Panel panel3("Count of probabilitys:" + DoubleToString(eventCount), { NORMALISED_SIZE * 23,200 - NORMALISED_SIZE * 3 }, font);
	Panel panel4("If max probability equal 0, and count > 0 => remaining probabilitys become 0", { 0,75}, font);
	panel4.SetShapeColor(sf::Color(204, 204, 255));

	Field field({NORMALISED_SIZE * 23 ,200}, 10, font );

	double maxValue = 1.0;
	double currentProbability = 0;
	int counter = 1;
	int eventCountTemp = eventCount;

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

			if (maxValue <= 1 && counter == eventCount)
			{
				answer.push_back({ currentProbability, counter });
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

					if (maxValue - currentProbability >= 0 && counter <= eventCount)
					{
						eventCountTemp--;
						maxValue -= currentProbability;
						panel2.SetText("Max probability:      " + DoubleToString(maxValue));
						panel3.SetText("Count of probabilitys:" + DoubleToString(eventCountTemp));
						answer.push_back({ currentProbability, counter });
						counter++;

					}
					else if (maxValue - currentProbability < 0 && counter <= eventCount)
					{
						eventCountTemp--;
						currentProbability = maxValue;
						maxValue = 0;
						panel2.SetText("Max probability:      " + DoubleToString(maxValue));
						panel3.SetText("Count of probabilitys:" + DoubleToString(eventCountTemp));
						answer.push_back({ currentProbability, counter });
						counter++;
					}
				}
			}
		}
		w.clear();
		panel1.Draw(w);
		panel2.Draw(w);
		panel3.Draw(w);
		panel4.Draw(w);
		field.Draw(w);
		w.display();
	}
}

void DiceMenu(sf::RenderWindow& w, sf::Font& font, Dice& dice)
{
	Field field({NORMALISED_SIZE * 23, 200},10 , font);
	Panel description("First variant set (1/count) probability for all events", {0,170},font);
	description.SetShapeColor(sf::Color(204, 204, 255));

	Panel panel	  ("Select variant:", { 0, 200 }, font);
	Button button1("Set equel probability", { NORMALISED_SIZE * 18, 200 + NORMALISED_SIZE * 3 }, font);
	Button button2("   Set probability   ", { NORMALISED_SIZE * 18, 200 + NORMALISED_SIZE * 6 }, font);

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
					if (count >= 1)
					{
						Dice newDice(count, 1, w, event, font);
						dice = newDice;
					}
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
		description.Draw(w);
		panel.Draw(w);
		button1.Draw(w);
		button2.Draw(w);
		w.display();

		if (flag)
			break;
	}

	description.SetText("For continue, make at least 1 event");
	panel.SetText("Select function:");
	button1.SetText("Make event");
	button2.SetText(" Continue ");
	button2.SetEnable(0);

	flag = 0;
	while (w.isOpen())
	{
		sf::Event event;

		while (w.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				w.close();
				return;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				button1.SetIsPressed(mousePosition);

				if (button2.Enable())
				{
					button2.SetIsPressed(mousePosition);
				}

				if (button1.IsPressed())
				{
					dice.MakeEvent(w, font);
					button2.SetEnable(1);
					break;
				}

				if (button2.IsPressed())
				{
					flag = 1;
					break;
				}
			}
		}

		if (flag)
			break;

		w.clear();
		panel.Draw(w);
		description.Draw(w);
		button1.Draw(w);
		button2.Draw(w);
		w.display();
	}
	flag = 0;

	description.SetText("count - number of repetitions of this experiment: 'A dice was thrown 1 time'");
	panel.SetText("Count of Experiment:");
	button1.SetText("Do Experiment");
	button1.SetEnable(0);

	int countExperiment = 0;

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

				if (field.OnClick(mousePosition))
				{
					field.SetSring(w, event);
					countExperiment = StringToDouble(field.GetInput());
					button1.SetEnable(1);
					break;
				}

				if (button1.Enable())
				{
					button1.SetIsPressed(mousePosition);
					if (button1.IsPressed())
					{
						dice.DoExperiment(countExperiment);
						flag = 1;
						break;
					}
				}
			}
		}

		if (flag)
			break;

		w.clear();
		description.Draw(w);
		button1.Draw(w);
		field.Draw(w);
		panel.Draw(w);
		w.display();
	}
}

int EventCount(sf::RenderWindow& w, sf::Font& font)
{
	int count = 0;
	Panel panel("Number of faces:", {0,200 }, font);
	Field field({NORMALISED_SIZE * 20 , 200 }, 10, font);

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
bool EventOnRes(int value, std::vector<int> res)
{
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i] == value)
			return 1;
	}

	return 0;
}
bool EventContainThisValue(int value, std::vector<Event2> event)
{
	for (int i = 0; i < event.size(); i++)
	{
		if (event[i].GetValue() == value)
			return 1;
	}

	return 0;
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

std::vector<ValueIndex> TypeEventCards(sf::RenderWindow& w, sf::Font& f, int countOfSE)
{
	std::vector<ValueIndex> temp(0);
	int value = 0;
	int index = 0;

	Panel maxValue("Max value and position is:" + DoubleToString(countOfSE), { 0,200 - NORMALISED_SIZE * 4}, f);
	maxValue.SetShapeColor(sf::Color(204, 204, 255));
	Panel panel1("Enter value   ", { 0,200 }, f);
	Panel panel2("Enter position", { 0,200 + NORMALISED_SIZE * 4 }, f);
	Panel panel12("Current value is: " + DoubleToString(value), {NORMALISED_SIZE * 30, 200}, f);
	Panel panel22("Current position is: " + DoubleToString(index), { NORMALISED_SIZE * 30, 200 + NORMALISED_SIZE * 4}, f);

	Field userValue({ NORMALISED_SIZE * 17, 200 }, 10, f);
	Field userPosition({ NORMALISED_SIZE * 17, 200 + NORMALISED_SIZE * 4 }, 10, f);

	Button XOnI("Value in position", { 0, 300 }, f);
	XOnI.SetEnable(0);
	Button XNotOnI("Value not in position", { 0, 300 + NORMALISED_SIZE * 3 }, f);
	XNotOnI.SetEnable(0);
	Button NotXOnI("Another value in position", { 0, 300 + NORMALISED_SIZE * 6 }, f);
	NotXOnI.SetEnable(0);
	Button XBeforeI("Value in smaler position", { 0, 300 + NORMALISED_SIZE * 9 }, f);
	XBeforeI.SetEnable(0);
	Button XAfterI("Value in bigger position", { 0, 300 + NORMALISED_SIZE * 12 }, f);
	XAfterI.SetEnable(0);

	while (w.isOpen())
	{
		sf::Event event;

		if (index != 0 && value != 0 && index <= countOfSE && value <= countOfSE)
		{
			XOnI.SetEnable(1);
			XNotOnI.SetEnable(1);
			NotXOnI.SetEnable(1);
			XBeforeI.SetEnable(1);
			XAfterI.SetEnable(1);
		}

		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return temp;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				if (XOnI.Enable())
				{
					XOnI.SetIsPressed(mousePosition);
					XNotOnI.SetIsPressed(mousePosition);
					NotXOnI.SetIsPressed(mousePosition);
					XBeforeI.SetIsPressed(mousePosition);
					XAfterI.SetIsPressed(mousePosition);
				}

				if (userPosition.OnClick(mousePosition))
				{
					userPosition.SetSring(w, event);
					index = StringToDouble(userPosition.GetInput());
					if(index <= countOfSE)
					panel22.SetText("Current position is: " + DoubleToString(index));
					break;
				}
				if (userValue.OnClick(mousePosition))
				{
					userValue.SetSring(w, event);
					value = StringToDouble(userValue.GetInput());
					if (value <= countOfSE)
					panel12.SetText("Current value is: " + DoubleToString(value));
					break;
				}
			
				if (XOnI.IsPressed())
				{
					if (index > countOfSE || index < 1)
					{
						index = 0;
						break;
					}
					if (value < 1 || value > countOfSE)
					{
						value = 0;
						break;
					}
					temp.push_back({ value, index, Status::ThisValueOnThisPosition });		
					return temp;
				}
				if (XNotOnI.IsPressed())
				{
					if (index > countOfSE || index < 1)
					{
						index = 0;
						break;
					}
					if (value < 1 || value > countOfSE)
					{
						value = 0;
						break;
					}
					temp.push_back({ value, index, Status::ThisValueOnEnotherPosition });
					return temp;
				}
				if (NotXOnI.IsPressed())
				{
					if (index > countOfSE || index < 1)
					{
						index = 0;
						break;
					}
					if (value < 1 || value > countOfSE)
					{
						value = 0;
						break;
					}
					temp.push_back({ value, index, Status::AnotherValueOnThisPosition });
					return temp;
				}
				if (XBeforeI.IsPressed())
				{
					if (index > countOfSE || index < 1)
					{
						index = 0;
						break;
					}
					if (value < 1 || value > countOfSE)
					{
						value = 0;
						break;
					}
					temp.push_back({ value, index, Status::IndexIsLower});
					return temp;
				}
				if (XAfterI.IsPressed())
				{
					if (index > countOfSE || index < 1)
					{
						index = 0;
						break;
					}
					if (value < 1 || value > countOfSE)
					{
						value = 0;
						break;
					}

					temp.push_back({ value, index, Status::IndexAbove });
					return temp;
				}
			}
		}

		w.clear();
		maxValue.Draw(w);
		panel1.Draw(w);
		panel2.Draw(w);
		panel12.Draw(w);
		panel22.Draw(w);

		userValue.Draw(w);
		userPosition.Draw(w);

		XOnI.Draw(w);
		XNotOnI.Draw(w);
		NotXOnI.Draw(w);
		XBeforeI.Draw(w);
		XAfterI.Draw(w);

		w.display();
	}

}
std::vector<std::vector<ValueIndex>> MakeEvent(sf::RenderWindow& w, sf::Font& font, int countOfSE)
{
	int currentConnection = 0;
	Button UP(" ^ ", { NORMALISED_SIZE * 47,NORMALISED_SIZE * 3 }, font);
	Button DOWN(" v ", { NORMALISED_SIZE * 47, NORMALISED_SIZE * 28 }, font);

	Panel connectionIndex("Connection index" + DoubleToString(currentConnection), { 4 * NORMALISED_SIZE , 0 }, font);
	Button left(" < ", { 0 * NORMALISED_SIZE , 0 }, font);
	Button right(" > ", { NORMALISED_SIZE * 24, 0 }, font);

	Table table;
	List value("Value", { 0,NORMALISED_SIZE * 3 }, 6, font, 10);
	List position("Position", { NORMALISED_SIZE * 6, NORMALISED_SIZE * 3 }, 9, font, 10);
	List status("Status", { NORMALISED_SIZE * 15, NORMALISED_SIZE * 3 }, 30, font, 10);

	std::vector<std::vector<ValueIndex>> answer;
	
	Panel panel("Choose option:", {0,350}, font);
	Button ORButton("OR", { NORMALISED_SIZE * 17,350 }, font);
	Button ANDButton("AND", { NORMALISED_SIZE * 17, 350 + NORMALISED_SIZE * 3 }, font);
	Button ContinueButton("Continue", { NORMALISED_SIZE * 17, 350 + NORMALISED_SIZE * 9 }, font);

	std::vector<ValueIndex> temp = TypeEventCards(w, font, countOfSE);
	
	int currentIndex = 0;

	for (int i = 0; i < temp.size(); i++)
	{
		answer.push_back(temp);
		value.AddElement(DoubleToString(answer[currentConnection][i].value), font);
		position.AddElement(DoubleToString(answer[currentConnection][i].index), font);
		if (answer[currentConnection][i].status == Status::AnotherValueOnThisPosition)
		{
			status.AddElement("Enother value on this position", font);
		}
		else if (answer[currentConnection][i].status == Status::IndexAbove)
		{
			status.AddElement("Value above this position", font);
		}
		else if (answer[currentConnection][i].status == Status::IndexIsLower)
		{
			status.AddElement("Value under this position", font);
		}

		else if (answer[currentConnection][i].status == Status::ThisValueOnEnotherPosition)
		{
			status.AddElement("Value under this position", font);
		}
		else
		{
			status.AddElement("Value on this position", font);
		}
	}

	table.AddColumn(value);
	table.AddColumn(position);
	table.AddColumn(status);

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				ORButton.SetIsPressed(mousePosition);
				ANDButton.SetIsPressed(mousePosition);
				ContinueButton.SetIsPressed(mousePosition);
				UP.SetIsPressed(mousePosition);
				DOWN.SetIsPressed(mousePosition);
				left.SetIsPressed(mousePosition);
				right.SetIsPressed(mousePosition);

				if (ORButton.IsPressed())
				{
					temp = TypeEventCards(w, font, countOfSE);

					answer.push_back(temp);
					currentIndex++;
					
					value.Clear();
					position.Clear();
					status.Clear();

					temp.clear();
					break;
				}

				if (ANDButton.IsPressed())
				{
					temp = TypeEventCards(w, font, countOfSE);

					for (int i = 0; i < temp.size(); i++)
					{
						value.AddElement(DoubleToString(temp[i].value), font);
						position.AddElement(DoubleToString(temp[i].index), font);
						if (temp[i].status == Status::AnotherValueOnThisPosition)
						{
							status.AddElement("Enother value on this position", font);
						}
						else if (temp[i].status == Status::IndexAbove)
						{
							status.AddElement("Value above this position", font);
						}
						else if (temp[i].status == Status::IndexIsLower)
						{
							status.AddElement("Value under this position", font);
						}

						else if (temp[i].status == Status::ThisValueOnEnotherPosition)
						{
							status.AddElement("Value under this position", font);
						}
						else
						{
							status.AddElement("Value on this position", font);
						}
					}

					table.SetColumnByIndex(0, value);
					table.SetColumnByIndex(1, position);
					table.SetColumnByIndex(2, status);

					answer[currentIndex].push_back(temp[0]);
					temp.clear();
					break;
				}

				if (UP.IsPressed())
				{
					table.ScrollUp();
				}
				if (DOWN.IsPressed())
				{
					table.ScrollDown();
				}
				if (left.IsPressed())
				{
					if (currentConnection > 0)
						currentConnection--;
					else
						currentConnection = answer.size() - 1;

					connectionIndex.SetText("Connection index" + DoubleToString(currentConnection));
					value.Clear();
					position.Clear();
					status.Clear();

					for (int i = 0; i < answer[currentConnection].size(); i++)
					{
						value.AddElement(DoubleToString(answer[currentConnection][i].value), font);
						position.AddElement(DoubleToString(answer[currentConnection][i].index), font);
						if (answer[currentConnection][i].status == Status::AnotherValueOnThisPosition)
						{
							status.AddElement("Enother value on this position", font);
						}
						else if (answer[currentConnection][i].status == Status::IndexAbove)
						{
							status.AddElement("Value above this position", font);
						}
						else if (answer[currentConnection][i].status == Status::IndexIsLower)
						{
							status.AddElement("Value under this position", font);
						}

						else if (answer[currentConnection][i].status == Status::ThisValueOnEnotherPosition)
						{
							status.AddElement("Value under this position", font);
						}
						else
						{
							status.AddElement("Value on this position", font);
						}
					}

					table.SetColumnByIndex(0, value);
					table.SetColumnByIndex(1, position);
					table.SetColumnByIndex(2, status);
				}
				if (right.IsPressed())
				{
					if (currentConnection < answer.size() - 1)
						currentConnection++;
					else
						currentConnection = 0;

					connectionIndex.SetText("Connection index" + DoubleToString(currentConnection));

					value.Clear();
					position.Clear();
					status.Clear();

					for (int i = 0; i < answer[currentConnection].size(); i++)
					{
						value.AddElement(DoubleToString(answer[currentConnection][i].value), font);
						position.AddElement(DoubleToString(answer[currentConnection][i].index), font);
						if (answer[currentConnection][i].status == Status::AnotherValueOnThisPosition)
						{
							status.AddElement("Enother value on this position", font);
						}
						else if (answer[currentConnection][i].status == Status::IndexAbove)
						{
							status.AddElement("Value above this position", font);
						}
						else if (answer[currentConnection][i].status == Status::IndexIsLower)
						{
							status.AddElement("Value under this position", font);
						}

						else if (answer[currentConnection][i].status == Status::ThisValueOnEnotherPosition)
						{
							status.AddElement("Value under this position", font);
						}
						else
						{
							status.AddElement("Value on this position", font);
						}
					}

					table.SetColumnByIndex(0, value);
					table.SetColumnByIndex(1, position);
					table.SetColumnByIndex(2, status);
				}
				if (ContinueButton.IsPressed())
				{
					return answer;
				}
			}
		}

		w.clear();
		UP.Draw(w);
		DOWN.Draw(w);
		left.Draw(w);
		right.Draw(w);
		connectionIndex.Draw(w);

		table.Draw(w);

		panel.Draw(w);
		ORButton.Draw(w);
		ANDButton.Draw(w);
		ContinueButton.Draw(w);

		w.display();
	}
}

std::vector <std::vector<ValueIndex>> CardMenu(sf::RenderWindow& w, sf::Font& f, PlayingCards& c)
{
	c.DoExperiment();
	std::vector <std::vector<ValueIndex>> userEvents(0);
	Button continueButton("Continue", {0,200 + NORMALISED_SIZE * 3 },f);
	continueButton.SetEnable(0);
	Button makeEventButton("Make event", {0,200}, f);

	bool flag = 0;

	while (w.isOpen())
	{
		sf::Event event;
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				return userEvents;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);

				if (continueButton.Enable())
				{
					continueButton.SetIsPressed(mousePosition);
				}
				makeEventButton.SetIsPressed(mousePosition);

				if (continueButton.IsPressed())
				{
					flag = 1;
					break;
				}
				if (makeEventButton.IsPressed())
				{
					userEvents = MakeEvent(w, f, c.GetCountEvent());
					continueButton.SetEnable(1);
					flag = 1;
					break;
				}
			}
		}

		w.clear();
		continueButton.Draw(w);
		makeEventButton.Draw(w);
		w.display();
		if (flag)
		{
			break;
		}
	}

	return userEvents;
}

void UI(sf::RenderWindow& w, sf::Font& f)
{
	std::vector <std::vector<ValueIndex>> cardsEvents(0);

	Dice newDice;
	PlayingCards newCards;
	Panel panel("Types of elements:", { 0,10 }, f);
	Panel description1("Description", { NORMALISED_SIZE * 22 ,10}, f);
	description1.SetShapeColor(sf::Color(204,204,255));
	Panel description2("Enable button or Panel", { NORMALISED_SIZE * 34, 10 }, f);
	description2.SetShapeColor(sf::Color::White);
	Panel description3("Disable button", { NORMALISED_SIZE * 57, 10 }, f);
	description3.SetShapeColor(sf::Color(192, 192, 192));


	Button diceButton("Dice", { 0, 200 }, f);
	Button cardsButton("Cards", { 0, 200 + NORMALISED_SIZE * 3 }, f);
	Button showResultatButton("Show resultat", { 0, 200 + NORMALISED_SIZE * 9 }, f);
	Button EXIT("Exit", { 0,WINDOW_HEIGHT / 2},f);
	Button newExperiment("New experiment", { 0, WINDOW_HEIGHT / 3}, f);
	newExperiment.SetEnable(0);
	EXIT.SetShapeColor(sf::Color(200,0,0));

	showResultatButton.SetEnable(0);


	while (w.isOpen())
	{
		sf::Event event;
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				w.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);
				
				if (diceButton.Enable())
				{
					diceButton.SetIsPressed(mousePosition);
				}
				if (newExperiment.Enable())
				{
					newExperiment.SetIsPressed(mousePosition);
				}
				if (cardsButton.Enable())
				{
					cardsButton.SetIsPressed(mousePosition);
				}
				if (showResultatButton.Enable())
				{
					showResultatButton.SetIsPressed(mousePosition);
				}

				EXIT.SetIsPressed(mousePosition);
				if (EXIT.IsPressed())
				{
					w.close();
					return;
				}
				if (newExperiment.IsPressed())
				{

					PlayingCards temp{};
					newCards = temp;
					Dice tempD{};
					newDice = tempD;

					diceButton.SetEnable(1);
					cardsButton.SetEnable(1);
					showResultatButton.SetEnable(0);
					break;
				}
				if (diceButton.IsPressed())
				{
					DiceMenu(w, f, newDice);
					diceButton.SetEnable(0);
					cardsButton.SetEnable(0);
					showResultatButton.SetEnable(1);
					newExperiment.SetEnable(1);
					break;
				}

				if (cardsButton.IsPressed())
				{
					PlayingCards temp(w,f);
					newCards = temp;
					cardsEvents = CardMenu(w, f, newCards);
					diceButton.SetEnable(0);
					cardsButton.SetEnable(0);
					showResultatButton.SetEnable(1);
					newExperiment.SetEnable(1);
					break;
				}

				if (showResultatButton.IsPressed())
				{
					if (cardsEvents.size() != 0)
					{
						ShowResult( w, f, newCards, cardsEvents);
					}

					else
					{
						ShowResult(newDice, w, f);
					}
					break;
				}
			}
		}
		w.clear();
		panel.Draw(w);
		description1.Draw(w);
		description2.Draw(w);
		description3.Draw(w);
		diceButton.Draw(w);
		cardsButton.Draw(w);
		showResultatButton.Draw(w);
		newExperiment.Draw(w);
		EXIT.Draw(w);
		w.display();
	}
}

void ShowResult(Dice& dice, sf::RenderWindow& w, sf::Font& f)
{
	std::vector<int> countEverySE = dice.CountEveryValu();

	Table result1;
	Table result2;

	const int visibleCount = 10;
	int index = 0;

	List temp1("Step", {0,100}, 8, f, visibleCount);
	for (int i = 0; i < dice.GetResultat().size(); i++)
	{
		temp1.AddElement(DoubleToString(i + 1), f);
	}
	List temp2("Value", { NORMALISED_SIZE * 8,100 }, 8, f, visibleCount);
	for (int i = 0; i < dice.GetResultat().size(); i++)
	{
		temp2.AddElement(DoubleToString(dice.GetResultat()[i]), f);
	}

	List temp3("Value", { NORMALISED_SIZE * 24, 100 }, 5, f, visibleCount);
	for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
	{
		temp3.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetValue()), f);
	}

	List temp4("Probability", { NORMALISED_SIZE * 29, 100 }, 11, f, visibleCount);
	for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
	{
		temp4.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetProbabylity()), f);
	}
	List temp5("Count", { NORMALISED_SIZE * 40, 100 }, 6, f, visibleCount);
	for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
	{
		temp5.AddElement(DoubleToString(countEverySE[dice.GetUserEvent()[index][i].GetValue() - 1]), f);
	}

	result1.AddColumn(temp1);
	result1.AddColumn(temp2);
	result2.AddColumn(temp3);
	result2.AddColumn(temp4);
	result2.AddColumn(temp5);

	Button EXIT("EXIT", { 0,200 + NORMALISED_SIZE * 14 }, f);
	
	Panel countUserEvent("Current event index:", { NORMALISED_SIZE * 23,60},f);
	Panel countUserEvent2(DoubleToString(index + 1), { NORMALISED_SIZE * 43 ,60}, f);
	countUserEvent2.SetWidth(4);

	Button UP(" ^ ", { NORMALISED_SIZE * 17 , 100}, f);
	Button DOWN(" v ", { NORMALISED_SIZE * 17 , 100 + NORMALISED_SIZE * 2 * visibleCount}, f);
	Button UP2(" ^ ", { NORMALISED_SIZE * 48, 100 }, f);
	Button DOWN2(" v ", { NORMALISED_SIZE * 48 ,100 + NORMALISED_SIZE * 2 * visibleCount }, f);

	Button Left(" < ", { NORMALISED_SIZE * 17,60 }, f);
	Button Right(" > ", { NORMALISED_SIZE * 50,60 }, f);

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
				UP.SetIsPressed(mousePosition);
				DOWN.SetIsPressed(mousePosition);
				UP2.SetIsPressed(mousePosition);
				DOWN2.SetIsPressed(mousePosition);
				Left.SetIsPressed(mousePosition);
				Right.SetIsPressed(mousePosition);

				EXIT.SetIsPressed(mousePosition);
				if (UP.IsPressed())
				{
					result1.ScrollUp();
					break;
				}
				if (DOWN.IsPressed())
				{
					result1.ScrollDown();
					break;
				}		
				if (UP2.IsPressed())
				{
					result2.ScrollUp();
					break;
				}
				if (DOWN2.IsPressed())
				{
					result2.ScrollDown();
					break;
				}
				if (Left.IsPressed())
				{
					if (index > 0)
					{
						index--;

						temp3.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp3.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetValue()), f);
						}

						temp4.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp4.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetProbabylity()), f);
						}

						temp5.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp5.AddElement(DoubleToString(countEverySE[dice.GetUserEvent()[index][i].GetValue() - 1]), f);
						}
						result2.SetColumnByIndex(0, temp3);
						result2.SetColumnByIndex(1, temp4);
						result2.SetColumnByIndex(2, temp5);

						countUserEvent2.SetText((DoubleToString(index + 1)));
					}
				}
				if (Right.IsPressed())
				{
					if (index < dice.GetUserEvent().size() - 1)
					{
						index++;

						temp3.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp3.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetValue()), f);
						}

						temp4.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp4.AddElement(DoubleToString(dice.GetUserEvent()[index][i].GetProbabylity()), f);
						}

						temp5.Clear();
						for (int i = 0; i < dice.GetUserEvent()[index].size(); i++)
						{
							temp5.AddElement(DoubleToString(countEverySE[dice.GetUserEvent()[index][i].GetValue() - 1]), f);
						}
						result2.SetColumnByIndex(0, temp3);
						result2.SetColumnByIndex(1, temp4);
						result2.SetColumnByIndex(2, temp5);
						countUserEvent2.SetText((DoubleToString(index + 1)));
					}
				}
				if (EXIT.IsPressed())
				{
					return;
				}
			}
		}

		w.clear();
		result1.Draw(w);
		result2.Draw(w);
		countUserEvent.Draw(w);
		countUserEvent2.Draw(w);
		Left.Draw(w);
		Right.Draw(w);
		UP.Draw(w);
		DOWN.Draw(w);
		UP2.Draw(w);
		DOWN2.Draw(w);
		EXIT.Draw(w);
		w.display();
	}

}

void ShowResult(sf::RenderWindow& w, sf::Font& f, PlayingCards& cards, std::vector<std::vector<ValueIndex>> userEvent)
{
	int index = 0;

	Table t1;
	Button UP1(" ^ ", { NORMALISED_SIZE * 12, NORMALISED_SIZE * 3 }, f);
	Button DOWN1(" v ", { NORMALISED_SIZE * 12, NORMALISED_SIZE * 14 }, f);
	List l11("Step", { 0, NORMALISED_SIZE * 3 }, 5, f, 10);
	List l12("Value", { 5 * NORMALISED_SIZE, NORMALISED_SIZE * 3 }, 5, f, 10);

	for (int i = 0; i < cards.GetResultat().size(); i++)
	{
		l11.AddElement(DoubleToString(i + 1), f);
		l12.AddElement(DoubleToString(cards.GetResultat()[i]), f);
	}


	t1.AddColumn(l11);
	t1.AddColumn(l12);


	Panel finalEvent(DoubleToString(index) + " event that happened", {NORMALISED_SIZE * 24,0}, f);
	Button left(" < ", { 20 * NORMALISED_SIZE,0 }, f);
	Button right(" > ", { 47 * NORMALISED_SIZE,0 }, f);

	std::vector<int> res = cards.GetResultat();

	if (res.size() == 0)
		return;

	std::vector<std::vector<ValueIndex>> winEventIndex;

	bool eventHeppend;

	for (int i = 0; i < userEvent.size(); i++)
	{
		eventHeppend = 1;
		for (int j = 0; j < userEvent[i].size(); j++)
		{
			if (eventHeppend == 0)
				break;

			switch (userEvent[i][j].status)
			{

			case Status::ThisValueOnThisPosition:
				if (res[userEvent[i][j].index - 1] != userEvent[i][j].value)
				{
					eventHeppend = 0;
				}
				break;

			case Status::ThisValueOnEnotherPosition:
				if (res[userEvent[i][j].index - 1] == userEvent[i][j].value)
				{
					eventHeppend = 0;
				}
				break;

			case Status::AnotherValueOnThisPosition:
				if (res[userEvent[i][j].index - 1] == userEvent[i][j].value)
				{
					eventHeppend = 0;
				}
				break;

			case Status::IndexAbove:

				eventHeppend = 0;

				for (int k = userEvent[i][j].index; k < res.size(); k++)
				{
					if (res[k] == userEvent[i][j].value)
					{
						eventHeppend = 1;
						break;
					}
				}
				break;

			case Status::IndexIsLower:	
				eventHeppend = 0;

				for (int k = 0; k < userEvent[i][j].index; k++)
				{
					if (res[k] == userEvent[i][j].value)
					{
						eventHeppend = 1;
						break;
					}
				}
				break;
			}
		}
		
		if(eventHeppend)
		winEventIndex.push_back(userEvent[i]);
	}

	Table t2;
	Button UP2(" ^ ", { NORMALISED_SIZE * 67, NORMALISED_SIZE * 3 }, f);
	Button DOWN2(" v ", { NORMALISED_SIZE * 67, NORMALISED_SIZE * 14 }, f);
	List l21("Value", { 20 * NORMALISED_SIZE, NORMALISED_SIZE * 3 }, 6, f, 10);
	List l22("Position", { 26 * NORMALISED_SIZE, NORMALISED_SIZE * 3 }, 9, f, 10);
	List l23("Status", { 35 * NORMALISED_SIZE, NORMALISED_SIZE * 3 }, 30, f, 10);

	for (int i = 0; i < winEventIndex[index].size(); i++)
	{
		l21.AddElement(DoubleToString(winEventIndex[index][i].value), f);
		l22.AddElement(DoubleToString(winEventIndex[index][i].index), f);

		if (winEventIndex[index][i].status == Status::AnotherValueOnThisPosition)
		{
			l23.AddElement("Enother value on this position", f);
		}
		else if (winEventIndex[index][i].status == Status::IndexAbove)
		{
			l23.AddElement("Value above this position", f);
		}
		else if (winEventIndex[index][i].status == Status::IndexIsLower)
		{
			l23.AddElement("Value under this position", f);
		}

		else if (winEventIndex[index][i].status == Status::ThisValueOnEnotherPosition)
		{
			l23.AddElement("Value under this position", f);
		}
		else
		{
			l23.AddElement("Value on this position", f);
		}
	}

	t2.AddColumn(l21);
	t2.AddColumn(l22);
	t2.AddColumn(l23);

	Button EXIT("EXIT", { 0,200 + NORMALISED_SIZE * 14 }, f);

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

				EXIT.SetIsPressed(mousePosition);
				UP1.SetIsPressed(mousePosition);
				UP2.SetIsPressed(mousePosition);
				DOWN1.SetIsPressed(mousePosition);
				DOWN2.SetIsPressed(mousePosition);
				left.SetIsPressed(mousePosition);
				right.SetIsPressed(mousePosition);

				if (UP1.IsPressed())
				{
					t1.ScrollUp();
				}
				if (UP2.IsPressed())
				{
					t2.ScrollUp();
				}
				if (DOWN1.IsPressed())
				{
					t1.ScrollDown();
				}
				if (DOWN2.IsPressed())
				{
					t2.ScrollDown();
				}
				if (left.IsPressed())
				{
					if (index > 0)
						index--;
					else
						index = winEventIndex.size() - 1;

					finalEvent.SetText(DoubleToString(index) + " event that happened");

					l21.Clear();
					l22.Clear();
					l23.Clear();

					for (int i = 0; i < winEventIndex[index].size(); i++)
					{
						l21.AddElement(DoubleToString(winEventIndex[index][i].value), f);
						l22.AddElement(DoubleToString(winEventIndex[index][i].index), f);

						if (winEventIndex[index][i].status == Status::AnotherValueOnThisPosition)
						{
							l23.AddElement("Enother value on this position", f);
						}
						else if (winEventIndex[index][i].status == Status::IndexAbove)
						{
							l23.AddElement("Value above this position", f);
						}
						else if (winEventIndex[index][i].status == Status::IndexIsLower)
						{
							l23.AddElement("Value under this position", f);
						}

						else if (winEventIndex[index][i].status == Status::ThisValueOnEnotherPosition)
						{
							l23.AddElement("Value under this position", f);
						}
						else
						{
							l23.AddElement("Value on this position", f);
						}
					}

					t2.SetColumnByIndex(0, l21);
					t2.SetColumnByIndex(1, l22);
					t2.SetColumnByIndex(2, l23);
					break;
				}
				if (right.IsPressed())
				{
					if (index < winEventIndex.size() - 1)
						index++;
					else
						index = 0;

					finalEvent.SetText(DoubleToString(index) + " event that happened");

					l21.Clear();
					l22.Clear();
					l23.Clear();

					for (int i = 0; i < winEventIndex[index].size(); i++)
					{
						l21.AddElement(DoubleToString(winEventIndex[index][i].value), f);
						l22.AddElement(DoubleToString(winEventIndex[index][i].index), f);

						if (winEventIndex[index][i].status == Status::AnotherValueOnThisPosition)
						{
							l23.AddElement("Enother value on this position", f);
						}
						else if (winEventIndex[index][i].status == Status::IndexAbove)
						{
							l23.AddElement("Value above this position", f);
						}
						else if (winEventIndex[index][i].status == Status::IndexIsLower)
						{
							l23.AddElement("Value under this position", f);
						}

						else if (winEventIndex[index][i].status == Status::ThisValueOnEnotherPosition)
						{
							l23.AddElement("Value under this position", f);
						}
						else
						{
							l23.AddElement("Value on this position", f);
						}
					}

					t2.SetColumnByIndex(0, l21);
					t2.SetColumnByIndex(1, l22);
					t2.SetColumnByIndex(2, l23);
					break;
				}
				if (EXIT.IsPressed())
				{
					return;
				}
			}
		}

		w.clear();

		t1.Draw(w);
		t2.Draw(w);
		finalEvent.Draw(w);
		left.Draw(w);
		right.Draw(w);
		UP1.Draw(w);
		DOWN1.Draw(w);
		UP2.Draw(w);
		DOWN2.Draw(w);

		EXIT.Draw(w);

		w.display();
	}
}