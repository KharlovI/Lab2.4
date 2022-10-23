#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

constexpr int CHAR_SIZE_FIELD = 18;

class Field
{
private:
	std::string input;
	sf::Text text;
	int countOfChar;
	sf::RectangleShape field;

	void SetText();
public:
	Field(sf::Vector2f position, int length, sf::Font& font);

	void AddChar(char& c);
	void SetSring(sf::RenderWindow& w, sf::Event& e);
	void PopChar();
	std::string GetInput();
	int GetCount();
	
	void CleanUp();
	void Draw(sf::RenderWindow& w);
	bool OnClick(sf::Vector2i mousePosition);
};

