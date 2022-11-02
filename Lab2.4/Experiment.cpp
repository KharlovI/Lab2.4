#include"Experiment.h"
#include"Utilities.h"
#include<random>
#include<iostream>
#include<cmath>

Experiment::Experiment()
{
	this->etemptCount = 0;
	this->SE_count = 0;
	this->UE_count = 0;
}
Experiment::Experiment(std::vector<Event2> simpleEvent)
{
	this->etemptCount = 0;
	this->UE_count = 0;
	this->simpleEvents = simpleEvent;
	this->SE_count = simpleEvent.size();
}

int Experiment::GetCountEtempt()
{
	return this->etemptCount;
}
int Experiment::GetCountEvent()
{
	return this->SE_count;
}
int Experiment::GetUserEventCount()
{
	return this->UE_count;
}
std::vector<int> Experiment::GetResultat()
{
	return this->res;
}
Event2 Experiment::GetSimpleEvent(int index)
{
	return this->simpleEvents[index];
}
std::vector<Event2> Experiment::GetUserEvent(int index)
{
	return this->userEvents[index];
}
std::vector<Event2> Experiment::GetSimpleEvent()
{
	return this->simpleEvents;
}
std::vector<std::vector<Event2>> Experiment::GetUserEvent()
{
	return this->userEvents;
}
int Experiment::GetResultat(int index)
{
	return this->res[index];
}

void Experiment::SetSimpleEvent(Event2& e)
{
	this->simpleEvents.push_back(e);
	this->SE_count++;
}
void Experiment::SetSimpleEvent(std::vector<Event2> e)
{
	this->simpleEvents = e;
	this->SE_count = e.size();
}
void Experiment::SetResultat(std::vector<int> r)
{
	this->res = r;
	this->etemptCount = r.size();
}

void Experiment::AddUserEvent(std::vector<Event2> e)
{

	this->userEvents.push_back(e);
	this->UE_count++;

}

void Experiment::IncrementCount()
{
	this->etemptCount++;
}
void Experiment::PrintRes()
{
	for (int i = 0; i < this->etemptCount; i++)
	{
		std::cout << i << ") " << this->res[i] << std::endl;
	}
}
std::vector<int> Experiment::CountEveryValu()
{
	int eventCount = GetCountEvent();
	std::vector<int> answer(eventCount);

	for (int i = 0; i < GetCountEtempt(); i++)
	{
		answer[GetResultat(i) - 1]++;
	}
	return answer;
}
Dice::Dice()
{
	//!!!!!!
	std::vector<int> res(0);
	SetResultat(res);
	//!!!!!!
	std::vector<Event2> temp(0);
	SetSimpleEvent(temp);
}

Dice::Dice(int countOfSimpleEvent, bool equal, sf::RenderWindow& w, sf::Event& e, sf::Font& font)
{
	if (equal)
	{
		std::vector<Event2> temp;
		double probabylity = 1.0 / (double)countOfSimpleEvent;

		for (int i = 0, value = 1; i < countOfSimpleEvent; i++, value++)
		{
			temp.push_back({ probabylity, value });
		}

		SetSimpleEvent(temp);
	}


	else
	{
		SetSimpleEvent(SetEventProbabilitys(w, font, countOfSimpleEvent));
	}
}

void Dice::DoExperiment(int count)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<double> distribution(0, 0.9999);

	std::vector<Event2> simpleEvents = GetSimpleEvent();
	std::vector<int> res;

	int tempRes = -1;

	double min = 0;
	double max = simpleEvents[0].GetProbabylity();

	double randomValue;
	for (int i = 0, index = 0; i < count; i++, index = 0)
	{
		randomValue = distribution(eng);
		while (tempRes == -1)
		{
			if (randomValue >= min && randomValue <= max)
			{
				tempRes = GetSimpleEvent()[index].GetValue();
				res.push_back(tempRes);
				IncrementCount();
			}

			else
			{
				index++;

				min = max;
				max += simpleEvents[index].GetProbabylity();
			}
		}

		min = 0;
		max = simpleEvents[0].GetProbabylity();
		tempRes = -1;
	}

	SetResultat(res);
}

std::vector<int> Experiment::RarestAndFrequent()
{
	std::vector<int> resCount = CountEveryValu();
	int maxCountRes = resCount[0];
	int minCountRes = resCount[0];
	int indexMin = 0;
	int indexMax = 0;

	for (int i = 1; i < GetCountEvent(); i++)
	{
		if (minCountRes > resCount[i])
		{
			minCountRes = resCount[i];
			indexMin = i;
			continue;
		}

		if (maxCountRes < resCount[i])
		{
			maxCountRes = resCount[i];
			indexMax = i;
		}
	}

	std::vector<int> ans(2);

	ans[0] = GetSimpleEvent()[indexMin].GetValue();
	ans[1] = GetSimpleEvent()[indexMax].GetValue();
	return ans;
}

double Dice::Expectation()
{
	double answer = 0;

	Event2 temp;
	for (int i = 0; i < GetCountEvent(); i++)
	{
		temp = GetSimpleEvent(i);
		answer += temp.GetValue() * temp.GetProbabylity();
	}

	return answer;
}

double Dice::Dispersion(double expectation)
{
	double answer = 0;

	int currentIndex;
	int res;

	for (int i = 0; i < GetCountEtempt(); i++)
	{
		res = GetResultat()[i];
		currentIndex = res - 1;
		answer += GetSimpleEvent(currentIndex).GetProbabylity() * (res - expectation) * (res - expectation);
	}

	return answer / GetCountEtempt();
}

double Dice::Deviation(double dispersion)
{
	return pow(dispersion, 0.5);
}

std::vector<Event2> Dice::EventClass(sf::RenderWindow& w, sf::Font& font)
{
	std::vector<Event2> answer(0);

	Panel description("Firstly, enter value. After that you can chouse type", { 0,200 - (CHAR_SIZE_Button - 7) * 8 }, font);
	description.SetShapeColor(sf::Color(204, 204, 255));

	Panel descriptionIsEqua("<- Resultant is equal entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 5 }, font);
	descriptionIsEqua.SetShapeColor(sf::Color(204, 204, 255));
	Panel descriptionIsNotEqua("<- Resultant is not equal entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 8 }, font);
	descriptionIsNotEqua.SetShapeColor(sf::Color(204, 204, 255));
	Panel descriptionIsMore("<- Resultant is more then entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 11 }, font);
	descriptionIsMore.SetShapeColor(sf::Color(204, 204, 255));
	Panel descriptionIsLess("<- Resultant is less then entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 14 }, font);
	descriptionIsLess.SetShapeColor(sf::Color(204, 204, 255));
	Panel descriptionIsMultiple("<- Resultant is multiple by entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 17 }, font);
	descriptionIsMultiple.SetShapeColor(sf::Color(204, 204, 255));
	Panel descriptionNotMultiple("<- Resultant is not multiple by entered value", { 20 * (CHAR_SIZE_Button - 7),200 + (CHAR_SIZE_Button - 7) * 20 }, font);
	descriptionNotMultiple.SetShapeColor(sf::Color(204, 204, 255));

	Panel valuePanel("Enter integer value:", { 0,200 - (CHAR_SIZE_Button - 7) * 4 }, font);
	Field valueField({ (CHAR_SIZE_Button - 7) * 22, 200 - (CHAR_SIZE_Button - 7) * 4 }, 10, font);

	int value;
	Panel panel2("Max value is:" + DoubleToString(this->GetCountEvent()), { (CHAR_SIZE_Button - 7) * 34, 200 - (CHAR_SIZE_Button - 7) * 4 }, font);
	Panel panel("Choose class:", { 0,200 }, font);

	Button isEqua     ("     Equal X     ", {0, 200 + (CHAR_SIZE_Button - 7) * 5 }, font);
	Button notEqua    ("   Not equal X   ", { 0, 200 + (CHAR_SIZE_Button - 7) * 8 }, font);
	Button isMore     ("   More than X   ", { 0, 200 + (CHAR_SIZE_Button - 7) * 11 }, font);
	Button isLess     ("   Less than X   ", { 0, 200 + (CHAR_SIZE_Button - 7) * 14 }, font);
	Button isMultiple ("  Multiple by X  ", { 0, 200 + (CHAR_SIZE_Button - 7) * 17 }, font);
	Button notMultiple("Not multiple by X", { 0, 200 + (CHAR_SIZE_Button - 7) * 20 }, font);

	isEqua.SetEnable(0);
	notEqua.SetEnable(0);
	isMore.SetEnable(0);
	isLess.SetEnable(0);
	isMultiple.SetEnable(0);
	notMultiple.SetEnable(0);

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
				sf::Vector2i mousePosition= sf::Mouse::getPosition(w);

				if(isEqua.Enable())
				isEqua.SetIsPressed(mousePosition);
				if (notEqua.Enable())
				notEqua.SetIsPressed(mousePosition);
				if (isMore.Enable())
				isMore.SetIsPressed(mousePosition);
				if (isLess.Enable())
				isLess.SetIsPressed(mousePosition);
				if (isMultiple.Enable())
				isMultiple.SetIsPressed(mousePosition);
				if (isMultiple.Enable())
				notMultiple.SetIsPressed(mousePosition);

				if (valueField.OnClick(mousePosition))
				{
					valueField.SetSring(w, event);
					value = StringToDouble(valueField.GetInput());

					if (value > this->GetCountEvent())
					{
						break;
					}
					description.Clean();
					isEqua.SetEnable(1);
					notEqua.SetEnable(1);
					isMore.SetEnable(1);
					isLess.SetEnable(1);
					isMultiple.SetEnable(1);
					notMultiple.SetEnable(1);
				}

				if (isEqua.IsPressed())
				{
					answer.push_back(this->GetSimpleEvent(value - 1));
					return answer;
				}
				if (notEqua.IsPressed())
				{
					int count = this->GetCountEvent();

					for (int i = 0; i < count; i++)
					{
						if (this->GetSimpleEvent(i).GetValue() != value)
						{
							answer.push_back(this->GetSimpleEvent(i));
						}
					}
					return answer;
				}
				if (isMore.IsPressed())
				{
					int count = this->GetCountEvent();

					for (int i = value; i < count; i++)
					{
						answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
				if (isLess.IsPressed())
				{
					for (int i = 0; i < value - 1; i++)
					{
						answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
				if (isMultiple.IsPressed())
				{
					int count = this->GetCountEvent();

					for (int i = 0; i < count; i++)
					{
						if(this->GetSimpleEvent(i).GetValue() % value == 0)
							answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
				if (notMultiple.IsPressed())
				{
					int count = this->GetCountEvent();

					for (int i = 0; i < count; i++)
					{
						if (this->GetSimpleEvent(i).GetValue() % value != 0)
							answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
			}
		}

		w.clear();

		descriptionIsEqua.Draw(w);
		descriptionIsLess.Draw(w);
		descriptionIsMore.Draw(w);
		descriptionIsMultiple.Draw(w);
		descriptionIsNotEqua.Draw(w);
		descriptionNotMultiple.Draw(w);

		panel2.Draw(w);
		description.Draw(w);
		valueField.Draw(w);
		valuePanel.Draw(w);
		panel.Draw(w);
		isEqua.Draw(w);
		notEqua.Draw(w);
		isMore.Draw(w);
		isLess.Draw(w);
		isMultiple.Draw(w);
		notMultiple.Draw(w);

		w.display();
	}
}

void Dice::MakeEvent(sf::RenderWindow& w, sf::Font& font)
{
	std::vector<Event2> answer;
	std::vector<Event2> temp;
	Panel description("Choose the type of connection", { 0,0 }, font);
	description.SetShapeColor(sf::Color(204, 204, 255));

	Panel panel("Choose type:", {0,200}, font);
	Button orButton		 ("    OR    ", { 0, 200 + (CHAR_SIZE_Button - 7) * 4},font);
	Button andButton	 ("    AND   ", { 0, 200 + (CHAR_SIZE_Button - 7) * 7 }, font);
	Button continueButton(" CONTINUE ", { 0, 200 + (CHAR_SIZE_Button - 7) * 10 }, font);

	temp = EventClass(w, font);
	answer = DifferentEvents(answer, temp);

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

				orButton.SetIsPressed(mousePosition);
				andButton.SetIsPressed(mousePosition);
				continueButton.SetIsPressed(mousePosition);

				if (orButton.IsPressed())
				{
					temp = EventClass(w, font);
					answer = DifferentEvents(answer, temp);
				}

				else if (andButton.IsPressed())
				{
					temp = EventClass(w, font);
					answer = SameEvents(answer, temp);
				}

				else if (continueButton.IsPressed())
				{
					this->AddUserEvent(answer);
					return;
				}
			}
		}

		w.clear();
		description.Draw(w);
		panel.Draw(w);
		orButton.Draw(w);
		andButton.Draw(w);
		continueButton.Draw(w);

		w.display();
	}
}

PlayingCards::PlayingCards()
{
	
}

PlayingCards::PlayingCards(sf::RenderWindow& w, sf::Font& font)
{
	Panel description("Count of card - deck size", { 200,175 }, font);
	description.SetShapeColor(sf::Color(204, 204, 255));
	Panel panel("Enter count of card:", {200,200}, font);
	Field field({ 200 + (CHAR_SIZE_PANEL - 7) * 22, 200 }, 10, font);
	int countOfSE = 0;
	bool flag = 0;

	while (w.isOpen())
	{
		sf::Event event;
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
				break;
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(w);
				if (field.OnClick(mousePosition))
				{
					field.SetSring(w, event);
					countOfSE = StringToDouble(field.GetInput());
					flag = 1;
					break;
				}
			}
		}

		if (flag)
			break;

		w.clear();
		description.Draw(w);
		panel.Draw(w);
		field.Draw(w);
		w.display();
	}

	std::vector<Event2> e;
	for (int i = 0; i < countOfSE; i++)
	{
		Event2 e2(1 / countOfSE, -1);
		this->indexes.push_back(i + 1);
		e.push_back(e2);
	}

	this->SetSimpleEvent(e);
}

std::vector<int> PlayingCards::GEtIndexes()
{
	return this->indexes;
}

int PlayingCards::GetIndex(int index)
{
	return this->indexes[index];
}

void PlayingCards::DoExperiment()
{
	int countOfSE = this->GetCountEvent();
	int pointer = countOfSE - 1;

	std::vector<int> indexes = GEtIndexes();

	std::random_device rd;
	std::mt19937 eng(rd());

	std::vector<Event2> simpleEvents = GetSimpleEvent();
	std::vector<int> res;

	int tempRes = -1;

	for (int i = 0; i < countOfSE; i++)
	{
		int tempIndex;

		std::uniform_real_distribution<double> distribution(0, pointer);

		int position = distribution(eng);
		tempRes = indexes[position];

		tempIndex = indexes[position];
		indexes[position] = indexes[pointer];
		indexes[pointer] = tempIndex;

		pointer--;

		res.push_back(tempRes);

	}

	SetResultat(res);

	
}