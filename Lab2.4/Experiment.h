#pragma once
#include<vector>
#include"Event2.h"
#include <SFML/Graphics.hpp>
class Experiment
{
private:
	int etemptCount;
	int SE_count;
	int UE_count;

	std::vector<Event2> simpleEvents;
	std::vector<std::vector<Event2>> userEvents;
	
	std::vector<int> res;
public:

	Experiment();
	Experiment(std::vector<Event2> simpleEvent);

	int GetCountEtempt();
	int GetCountEvent();
	int GetUserEventCount();

	std::vector<Event2> GetSimpleEvent();
	std::vector<std::vector<Event2>> GetUserEvent();
	Event2 GetSimpleEvent(int index);
	std::vector<Event2> GetUserEvent(int index);

	std::vector<int> GetResultat();
	int GetResultat(int index);

	void SetSimpleEvent(Event2& e);
	void SetSimpleEvent(std::vector<Event2> e);
	void SetResultat(std::vector<int> r);

	void AddUserEvent(std::vector<Event2> e);

	void IncrementCount();

	void PrintRes();											// DELETE!!!!

	std::vector<int> CountEveryValu();
};


class Dice : public Experiment
{

public:
	Dice();
	Dice(int countOfSimpleEvent, bool equal, sf::RenderWindow& w, sf::Event& e , sf::Font& font);
	void DoExperiment(int count);

	void operator =(Dice& d)
	{
		this->SetSimpleEvent(d.GetSimpleEvent());
	}
	std::vector<int> RarestAndFrequent();

	void PrintStatistic();										// Rework or delete

	void PrintPosibleActions();									// Rework or delete
	std::vector<Event2> EventClass(sf::RenderWindow& w, sf::Font& font);
	void MakeEvent(sf::RenderWindow& w, sf::Font& font);

	double Expectation();
	double Dispersion(double expectation);
	double Deviation(double dispersion);
};

class Coin
{

};

class Cards
{

};