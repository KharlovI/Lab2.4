#pragma once
#include<vector>
#include "Panel.h"
class List
{
private:
	std::vector<Panel> list;
	int countOfElements;
	int width;
	int countOfVisibleElements;
	int currentIndex;
	sf::Vector2f position;

public:
	List(int countOfVisibleElements);
	List(std::string name, sf::Vector2f position, int width, sf::Font& f, int countOfVisibleElements);

	void Draw(sf::RenderWindow& w);
	void AddElement(std::string name,  sf::Font& f);
	int GetCountOfElements();
	int GetCountOfVisibleElements();
	int GetWidth();
	sf::Vector2f GetPosition();
	
	void Clear();
	void ScrollUP();
	void ScrollDOWN();
};