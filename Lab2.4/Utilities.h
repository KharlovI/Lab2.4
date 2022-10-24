#pragma once
#include"Diagram.h"
#include"Button.h"
#include"Field.h"
#include"Panel.h"

double StringToDouble(std::string string);

void SetDiagramConfigs(Diagram& d, Dice& e);
void DrawDiagram(Diagram& d, sf::RenderWindow& w);
char& IntToChar(sf::Keyboard::Key& key);

std::vector<Event2> SetEventProbabilitys(sf::RenderWindow& w, sf::Font& font, int eventCount);

void DiceMenu(sf::RenderWindow& w, sf::Font& font, Dice& dice);
int  EventCount(sf::RenderWindow& w, sf::Font& font);
int Value(sf::RenderWindow& w, sf::Font& font);
std::vector<Event2> DifferentEvents(std::vector<Event2> e1, std::vector<Event2> e2);
std::vector<Event2> SameEvents(std::vector<Event2> e1, std::vector<Event2> e2);

bool EventOnRes(int value, std::vector<int> res);
bool EventContainThisValue(int value, std::vector<Event2> event);

void ShowResultat(std::vector<std::vector<Event2>> userEvents, std::vector<int> res, int countSE, std::vector<int> countEverySE, sf::RenderWindow& w, sf::Font& f);