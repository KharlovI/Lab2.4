#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
constexpr int CHAR_SIZE_Button = 18;
class Button
{
private:
	sf::Text text;
	sf::RectangleShape shape;
	bool isPressed;
	bool enable;
	
public:

	Button();
	Button(std::string name, sf::Vector2f position, sf::Font& font);

	void SetIsPressed(sf::Vector2i mousePosition);
	void SetEnable(bool isEnable);
	void SetTextColor(sf::Color color);
	void SetShapeColor(sf::Color color);
	void SetPosiyion(sf::Vector2f position);
	void SetText(std::string text);

	void Draw(sf::RenderWindow& w);
	bool IsPressed();
	bool Enable();
	void Delete();
};

