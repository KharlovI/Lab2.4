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

void Experiment::AddUserEvent(Event2& e)
{
	this->userEvents.push_back(e);
	IncrementCount();
}
void Experiment::AddUserEvent(std::vector<Event2> e, int count)
{
	for (int i = 0; i < count; i++)
	{
		this->userEvents.push_back(e[i]);
		IncrementCount();
	}
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
		SetSimpleEvent(Event(countOfSimpleEvent, w, e, font));
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
