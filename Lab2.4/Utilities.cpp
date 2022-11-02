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

					if ((maxValue - currentProbability >= 0.001 || currentProbability - maxValue >= 0.001) && counter <= eventCount)
					{
						eventCountTemp--;
						maxValue -= currentProbability;
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

					temp.push_back({ value, index, Status::IndexIsHire });
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
	std::vector<std::vector<ValueIndex>> answer;
	Panel description("OR, AND add additional event. Continue - go to next step", {0, 170}, font);
	description.SetShapeColor(sf::Color(204, 204, 255));

	Panel panel("Choose option:", {0,200 }, font);
	Button ORButton("OR", { NORMALISED_SIZE * 17, 200 }, font);
	Button ANDButton("AND", { NORMALISED_SIZE * 17, 200 + NORMALISED_SIZE * 3 }, font);
	Button ContinueButton("Contunue", { NORMALISED_SIZE * 17, 200 + NORMALISED_SIZE * 9 }, font);

	std::vector<ValueIndex> temp = TypeEventCards(w, font, countOfSE);
	
	int currentIndex = 0;

	for (int i = 0; i < temp.size(); i++)
	{
		answer.push_back(temp);
	}

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

				if (ORButton.IsPressed())
				{
					temp = TypeEventCards(w, font, countOfSE);

					answer.push_back(temp);
					currentIndex++;
					temp.clear();
					break;
				}

				if (ANDButton.IsPressed())
				{
					temp = TypeEventCards(w, font, countOfSE);
					answer[currentIndex].push_back(temp[0]);
					temp.clear();
					break;
				}

				if (ContinueButton.IsPressed())
				{
					return answer;
				}
			}
		}

		w.clear();
		description.Draw(w);
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

	Panel description("You should creat least 1 event for continue", {0,160}, f);
	description.SetShapeColor(sf::Color(204, 204, 255));
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
					userEvents = (MakeEvent(w, f, c.GetCountEvent()));
					continueButton.SetEnable(1);
					flag = 1;
					break;
				}
			}
		}

		w.clear();

		description.Draw(w);
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
						ShowResultat( w, f, newCards, cardsEvents);
					}

					else
					{
						ShowResultat(newDice, w, f);
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

void ShowResultat(Dice& dice, sf::RenderWindow& w, sf::Font& f)
{
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;

	int totalCountOfUserEvent = dice.GetUserEvent().size();

	std::vector<int> countEverySE = dice.CountEveryValu();
	std::vector<int> countEveryUserEvent;
	int temp = 0;


	for (int i = 0; i < totalCountOfUserEvent; i++)
	{
		for (int j = 0; j < dice.GetCountEvent(); j++)
		{
			if (EventContainThisValue(j + 1, dice.GetUserEvent()[i]))
			{
				temp += countEverySE[j];
			}
		}
		countEveryUserEvent.push_back(temp);
		temp = 0;
	}

	if (countEveryUserEvent.size() == 0)
	{
		countEveryUserEvent = std::vector<int>(1);
	}

	std::vector<int> res = dice.GetResultat();

	Button EXIT("EXIT", { 0,200 + NORMALISED_SIZE * 14 }, f);

	/*Panel description1("Show resultat (all droped values step by step)", { NORMALISED_SIZE * 42,200 }, f);
	description1.SetShapeColor(sf::Color(204, 204, 255));
	Panel description2("Shows count of each event", { NORMALISED_SIZE * 42,200 + NORMALISED_SIZE * 3 }, f);
	description2.SetShapeColor(sf::Color(204, 204, 255));
	Panel description3("Shows count of each simple event", { NORMALISED_SIZE * 42,200 + NORMALISED_SIZE * 6 }, f);
	description3.SetShapeColor(sf::Color(204, 204, 255));*/

	Panel panel11("        Steps:        ", { 0,200 }, f);
	Panel panel21(" Value of user event: ", { 0,200 + NORMALISED_SIZE * 3 }, f);
	Panel panel31("Value of simple event:", { 0,200 + NORMALISED_SIZE * 6 }, f);

	Panel panel12(DoubleToString(index1 + 1) + ")" + DoubleToString(res[0]), { NORMALISED_SIZE * 30,200 }, f);
	Panel panel22(DoubleToString(index2 + 1) + ")" + DoubleToString(countEveryUserEvent[0]), {NORMALISED_SIZE * 30,200 + NORMALISED_SIZE * 3 }, f);
	Panel panel32(DoubleToString(index3 + 1) + ": " + DoubleToString(countEverySE[0]), { NORMALISED_SIZE * 30,200 + NORMALISED_SIZE * 6 }, f);

	Button b1L(" < ", { NORMALISED_SIZE * 25 , 200 }, f);
	Button b1R(" > ", { NORMALISED_SIZE * 48 , 200 }, f);
	Button b2L(" < ", { NORMALISED_SIZE * 25 , 200 + NORMALISED_SIZE * 3 }, f);
	Button b2R(" > ", { NORMALISED_SIZE * 48 , 200 + NORMALISED_SIZE * 3 }, f);
	Button b3L(" < ", { NORMALISED_SIZE * 25 , 200 + NORMALISED_SIZE * 6 }, f);
	Button b3R(" > ", { NORMALISED_SIZE * 48 , 200 + NORMALISED_SIZE * 6 }, f);

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

				b1L.SetIsPressed(mousePosition);
				b1R.SetIsPressed(mousePosition);
				b2L.SetIsPressed(mousePosition);
				b2R.SetIsPressed(mousePosition);
				b3L.SetIsPressed(mousePosition);
				b3R.SetIsPressed(mousePosition);

				EXIT.SetIsPressed(mousePosition);

				if (b1L.IsPressed())
				{
					if (index1 == 0)
						index1 = res.size() - 1;
					else
						index1--;

					panel12.SetText(DoubleToString(index1 + 1) + ")" + DoubleToString(res[index1]));
					break;
				}
				if (b1R.IsPressed())
				{
					if (index1 == res.size() - 1)
						index1 = 0;
					else
						index1++;

					panel12.SetText(DoubleToString(index1 + 1) + ")" + DoubleToString(res[index1]));
					break;
				}
				if (b2L.IsPressed())
				{
					if (index2 == 0)
						index2 = countEveryUserEvent.size() - 1;
					else
						index2--;

					panel22.SetText(DoubleToString(index2 + 1) + ")" + DoubleToString(countEveryUserEvent[index2]));
					break;
				}
				if (b2R.IsPressed())
				{
					if (index2 == countEveryUserEvent.size() - 1)
						index2 = 0;
					else
						index2++;

					panel22.SetText(DoubleToString(index2 + 1) + ")" + DoubleToString(countEveryUserEvent[index2]));
					break;
				}
				if (b3L.IsPressed())
				{
					if (index3 == 0)
						index3 = countEverySE.size() - 1;
					else
						index3--;

					panel32.SetText(DoubleToString(index3 + 1) + ": " + DoubleToString(countEverySE[index3]));
					break;
				}
				if (b3R.IsPressed())
				{
					if (index3 == countEverySE.size() - 1)
						index3 = 0;
					else
						index3++;

					panel32.SetText(DoubleToString(index3 + 1) + ": " + DoubleToString(countEverySE[index3]));
					break;
				}

				if (EXIT.IsPressed())
				{
					return;
				}
			}
		}

		w.clear();

		//description1.Draw(w);
		//description2.Draw(w);
		//description3.Draw(w);

		b1L.Draw(w);
		b1R.Draw(w);
		b2L.Draw(w);
		b2R.Draw(w);
		b3L.Draw(w);
		b3R.Draw(w);
		EXIT.Draw(w);

		panel11.Draw(w);
		panel12.Draw(w);
		panel21.Draw(w);
		panel22.Draw(w);
		panel31.Draw(w);
		panel32.Draw(w);

		w.display();
	}

}
void ShowResultat(sf::RenderWindow& w, sf::Font& f, PlayingCards& cards, std::vector<std::vector<ValueIndex>> userEvent)
{
	int index1 = 0;
	int index2i = 0;
	int index2j = 0;

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

			case Status::IndexIsHire:

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

	Button EXIT("EXIT", { 0,200 + NORMALISED_SIZE * 14 }, f);

	Panel panel11("         Steps:         ", { 0,200 }, f);
	Panel panel21("      Combination:      ", { 0,200 + NORMALISED_SIZE * 3 }, f);
	Panel panel31("   Combination index:   ", { 0,200 + NORMALISED_SIZE * 6 }, f);

	/*Panel description1("Show resultat (step by step 'drawing' cards)", { NORMALISED_SIZE * 42,200}, f);
	description1.SetShapeColor(sf::Color(204, 204, 255));
	Panel description2("Shows values, that happened", { NORMALISED_SIZE * 42,200 + NORMALISED_SIZE * 3 }, f);
	description2.SetShapeColor(sf::Color(204, 204, 255));
	Panel description3("Index of combination, that happened", { NORMALISED_SIZE * 42,200 + NORMALISED_SIZE * 6 }, f);
	description3.SetShapeColor(sf::Color(204, 204, 255));*/

	Panel panel12(DoubleToString(index1+1) + ")" + DoubleToString(res[index1]), { NORMALISED_SIZE * 30,200 }, f);

	Panel panel22("", { NORMALISED_SIZE * 30,200 + NORMALISED_SIZE * 3 }, f);
	if (winEventIndex.size() != 0)
	{
		panel22.SetText((DoubleToString(index2j + 1) + ")" + DoubleToString(winEventIndex[index2i][index2j].value)));
	}

	Panel panel32(DoubleToString(index2i+1), { NORMALISED_SIZE * 30,200 + NORMALISED_SIZE * 6}, f);

	Button b1L(" < ", { NORMALISED_SIZE * 25 , 200 }, f);
	Button b1R(" > ", { NORMALISED_SIZE * 48 , 200 }, f);
	Button b2L(" < ", { NORMALISED_SIZE * 25 , 200 + NORMALISED_SIZE * 3 }, f);
	Button b2R(" > ", { NORMALISED_SIZE * 48 , 200 + NORMALISED_SIZE * 3 }, f);
	Button b3L(" < ", { NORMALISED_SIZE * 25 , 200 + NORMALISED_SIZE * 6 }, f);
	Button b3R(" > ", { NORMALISED_SIZE * 48 , 200 + NORMALISED_SIZE * 6 }, f);

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

				b1L.SetIsPressed(mousePosition);
				b1R.SetIsPressed(mousePosition);
				b2L.SetIsPressed(mousePosition);
				b2R.SetIsPressed(mousePosition);
				b3L.SetIsPressed(mousePosition);
				b3R.SetIsPressed(mousePosition);

				EXIT.SetIsPressed(mousePosition);

				if (b1L.IsPressed())
				{
					if (index1 == 0)
						index1 = res.size() - 1;
					else
						index1--;

					panel12.SetText(DoubleToString(index1+1) + ")" + DoubleToString(res[index1]));
					break;
				}
				if (b1R.IsPressed())
				{
					if (index1 == res.size() - 1)
						index1 = 0;
					else
						index1++;

					panel12.SetText(DoubleToString(index1+1) + ")" + DoubleToString(res[index1]));
					break;
				}
				if (b2L.IsPressed())
				{
					if (winEventIndex.size() != 0)
					{
						if (index2j == 0)
							index2j = winEventIndex[index2i].size() - 1;
						else
							index2j--;

					
							panel22.SetText((DoubleToString(index2j + 1) + ")" + DoubleToString(winEventIndex[index2i][index2j].value)));
					}
					break;
				}
				if (b2R.IsPressed())
				{
					if (winEventIndex.size() != 0)
					{
						if (index2j == winEventIndex[index2i].size() - 1)
							index2j = 0;
						else
							index2j++;

						panel22.SetText((DoubleToString(index2j + 1) + ")" + DoubleToString(winEventIndex[index2i][index2j].value)));
					}
					break;
				}

				if (b3L.IsPressed())
				{
					if (winEventIndex.size() != 0)
					{
						if (index2i == 0)
							index2i = winEventIndex.size() - 1;
						else
							index2i--;
					
							panel22.SetText((DoubleToString(index2j + 1) + ")" + DoubleToString(winEventIndex[index2i][index2j].value)));
							panel32.SetText(DoubleToString(index2i + 1));
					}
					break;
				}

				if (b3R.IsPressed())
				{
					if (winEventIndex.size() != 0)
					{
						if (index2i  == winEventIndex.size() - 1)
							index2i = 0;
						else
							index2i++;

						panel22.SetText((DoubleToString(index2j + 1) + ")" + DoubleToString(winEventIndex[index2i][index2j].value)));
						panel32.SetText(DoubleToString(index2i + 1));
					}
					break;
				}
				if (EXIT.IsPressed())
				{
					return;
				}
			}
		}

		w.clear();
		/*description1.Draw(w);
		description2.Draw(w);
		description3.Draw(w);*/

		b1L.Draw(w);
		b1R.Draw(w);
		b2L.Draw(w);
		b2R.Draw(w);
		b3L.Draw(w);
		b3R.Draw(w);

		EXIT.Draw(w);

		panel11.Draw(w);
		panel12.Draw(w);
		panel21.Draw(w);
		panel22.Draw(w);
		panel31.Draw(w);
		panel32.Draw(w);

		w.display();
	}
}