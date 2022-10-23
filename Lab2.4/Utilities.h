#pragma once
#include"Diagram.h"
#include"Button.h"
#include"Field.h"
#include"Panel.h"

double StringToDouble(std::string string);

void SetDiagramConfigs(Diagram& d, Dice& e);
void DrawDiagram(Diagram& d, sf::RenderWindow& w);
char& IntToChar(sf::Keyboard::Key& key);

std::vector<Event2> Event(int countOfSimpleEvent, sf::RenderWindow& window, sf::Event& event, sf::Font& font);

void StartDiceMenu(sf::RenderWindow& window, sf::Event& event, sf::Font& font, Dice& original);