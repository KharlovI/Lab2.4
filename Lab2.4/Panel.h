#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr int CHAR_SIZE_PANEL = 18;

class Panel
{
private:
	sf::Text text;
	sf::RectangleShape shape;
	int countOfChar;

public:
	Panel();
	Panel(std::string text, sf::Vector2f position, sf::Font& font);

	void Draw(sf::RenderWindow& w);

	void SetText(std::string text);
	void SetFont(sf::Font& font);
	void SetPosition(sf::Vector2f position);
	void Clean();
	void SetWidth(int charsCount);
	void SetShapeColor(sf::Color c);
	void SetTextColor(sf::Color c);
	void SetCharSize(int size);

	sf::RectangleShape& GetShape();
};

