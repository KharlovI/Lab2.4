#pragma once
#include"Experiment.h"
#include"Button.h"
#include"Field.h"
#include"Panel.h"

enum Status
{
	ThisValueOnThisPosition,
	ThisValueOnEnotherPosition,
	AnotherValueOnThisPosition,
	IndexIsLower,
	IndexIsHire
};

struct ValueIndex
{
	int value;
	int index;
	Status status;
};

double StringToDouble(std::string string);
std::string DoubleToString(const double& value);

char& IntToChar(sf::Keyboard::Key& key);

std::vector<Event2> SetEventProbabilitys(sf::RenderWindow& w, sf::Font& font, int eventCount);

void DiceMenu(sf::RenderWindow& w, sf::Font& font, Dice& dice);
int  EventCount(sf::RenderWindow& w, sf::Font& font);
std::vector<Event2> DifferentEvents(std::vector<Event2> e1, std::vector<Event2> e2);
std::vector<Event2> SameEvents(std::vector<Event2> e1, std::vector<Event2> e2);

bool EventOnRes(int value, std::vector<int> res);
bool EventContainThisValue(int value, std::vector<Event2> event);
bool VectoreContainValue(std::vector<Event2> v, int value);

std::vector<std::vector<ValueIndex>> MakeEvent(sf::RenderWindow& w, sf::Font& font, int countOfSE);

void ShowResultat(Dice& dice, sf::RenderWindow& w, sf::Font& f);
void ShowResultat(sf::RenderWindow& w, sf::Font& f, PlayingCards& cards, std::vector<std::vector<ValueIndex>> userEvent);

std::vector <std::vector<ValueIndex>> CardMenu(sf::RenderWindow& w, sf::Font& f, PlayingCards& c);
void UI(sf::RenderWindow& w, sf::Font& f);