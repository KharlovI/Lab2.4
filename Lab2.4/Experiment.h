#pragma once
#include<vector>
#include"Event2.h"
#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 1000;

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
	void SetCountOFEtempt(int count) { this->etemptCount = count; }
	void SetCountOfSE(int count) { this->SE_count = count; }
	void SetCountOfUserEvent(int count) { this->UE_count = count; }
	void SetUserEvent(std::vector<std::vector<Event2>> e) { this->userEvents = e; }
	void AddUserEvent(std::vector<Event2> e);

	void IncrementCount();

	void PrintRes();											// DELETE!!!!

	std::vector<int> CountEveryValu();

	std::vector<int> RarestAndFrequent();
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
		this->SetResultat(d.GetResultat());
		this->SetCountOfSE(d.GetCountEvent());
		this->SetCountOFEtempt(d.GetCountEtempt());
		this->SetCountOfUserEvent(d.GetUserEventCount());
		this->SetUserEvent(d.GetUserEvent());
		
	}

	std::vector<Event2> EventClass(sf::RenderWindow& w, sf::Font& font);
	void MakeEvent(sf::RenderWindow& w, sf::Font& font);

	double Expectation();
	double Dispersion(double expectation);
	double Deviation(double dispersion);
};

class PlayingCards : public Experiment
{
private:
	std::vector<int> indexes;
public:
	PlayingCards();
	PlayingCards(sf::RenderWindow& w, sf::Font& font);
	void operator =(PlayingCards& pc)
	{
		this->SetSimpleEvent(pc.GetSimpleEvent());
		this->indexes = pc.GEtIndexes();
		this->SetResultat(pc.GetResultat());
		this->SetCountOfSE(pc.GetCountEvent());
		this->SetCountOFEtempt(pc.GetCountEtempt());	
		this->SetUserEvent(pc.GetUserEvent());
	}
	std::vector<int> GEtIndexes();
	int GetIndex(int index);

	void DoExperiment();

};
