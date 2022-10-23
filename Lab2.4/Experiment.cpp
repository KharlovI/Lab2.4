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
std::vector<int> Experiment::GetResultat()
{
	return this->res;
}
Event2 Experiment::GetSimpleEvent(int index)
{
	return this->simpleEvents[index];
}
std::vector<Event2> Experiment::GetSimpleEvent()
{
	return this->simpleEvents;
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

//void Experiment::AddUserEvent(Event2& e)
//{
//	this->userEvents.push_back(e);
//	IncrementCount();
//}
void Experiment::AddUserEvent(std::vector<Event2> e)
{

	this->userEvents.push_back(e);
	IncrementCount();

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

Dice::Dice()
{
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
std::vector<int> Dice::CountEveryValu()
{
	int eventCount = GetCountEvent();
	std::vector<int> answer(eventCount);

	for (int i = 0; i < GetCountEtempt(); i++)
	{
		answer[GetResultat(i) - 1]++;
	}
	return answer;
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

std::vector<int> Dice::RarestAndFrequent()
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

void Dice::PrintStatistic()
{
	double expectation = Expectation();
	double dispersion = Dispersion(expectation);
	double deviation = Deviation(dispersion);

	std::vector<int> countEveryEvent = CountEveryValu();
	std::vector<int> rarestAndFrequent = RarestAndFrequent();

	std::cout << "________________________" << std::endl << std::endl;
	std::cout << "Mat expectation: " << expectation << std::endl;
	std::cout << "________________________" << std::endl << std::endl;
	std::cout << "Deviation: " << deviation << std::endl;
	std::cout << "________________________" << std::endl << std::endl;
	std::cout << "Count of every event: " << std::endl;
	for (int i = 0; i < GetCountEvent(); i++)
	{
		std::cout << i + 1 << ": \t" << countEveryEvent[i] << std::endl;
	}
	std::cout << std::endl << std::endl;
	std::cout << "Rarest: \t" << rarestAndFrequent[0] << std::endl;
	std::cout << "Frequent:\t" << rarestAndFrequent[1] << std::endl;
	std::cout << "________________________" << std::endl << std::endl;
}
void Dice::PrintPosibleActions()
{


}

std::vector<Event2> Dice::EventClass(sf::RenderWindow& w, sf::Font& font)
{
	std::vector<Event2> answer(0);

	Panel panel("Choose class:", { 200,200 }, font);

	Button isEqua("Equal X", { 200, 200 + (CHAR_SIZE_Button - 7) * 4 }, font);
	Button notEqua("Not equal X", { 200, 200 + (CHAR_SIZE_Button - 7) * 6 }, font);
	Button isMore("More than X", { 200, 200 + (CHAR_SIZE_Button - 7) * 8 }, font);
	Button isLess("Less than X", { 200, 200 + (CHAR_SIZE_Button - 7) * 10 }, font);
	Button isMultiple("Multiple by X", { 200, 200 + (CHAR_SIZE_Button - 7) * 12 }, font);
	Button notMultiple("Not multiple by X", { 200, 200 + (CHAR_SIZE_Button - 7) * 14 }, font);

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

				isEqua.SetIsPressed(mousePosition);
				notEqua.SetIsPressed(mousePosition);
				isMore.SetIsPressed(mousePosition);
				isLess.SetIsPressed(mousePosition);
				isMultiple.SetIsPressed(mousePosition);
				notMultiple.SetIsPressed(mousePosition);

				if (isEqua.IsPressed())
				{
					int value = Value(w, font);
					answer.push_back(this->GetSimpleEvent(value));
					return answer;
				}
				if (notEqua.IsPressed())
				{
					int value = Value(w, font);
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
					int value = Value(w, font);
					int count = this->GetCountEvent();

					for (int i = value; i < count; i++)
					{
						answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
				if (isLess.IsPressed())
				{
					int value = Value(w, font);

					for (int i = 0; i < value - 1; i++)
					{
						answer.push_back(this->GetSimpleEvent(i));
					}
					return answer;
				}
				if (isMultiple.IsPressed())
				{
					int value = Value(w, font);
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
					int value = Value(w, font);
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
	Panel panel("Choose type:", {200,200}, font);
	Button orButton("OR", {200, 200 + (CHAR_SIZE_Button - 7) * 4},font);
	Button andButton("AND", { 200, 200 + (CHAR_SIZE_Button - 7) * 6 }, font);
	Button continueButton("CONTINUE", { 200, 200 + (CHAR_SIZE_Button - 7) * 9 }, font);

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

				}
			}
		}

		w.clear();

		panel.Draw(w);
		orButton.Draw(w);
		andButton.Draw(w);

		w.display();
	}
}
