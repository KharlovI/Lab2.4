#include "Button.h"

Button::Button()
{
	this->isPressed = 0;
}

Button::Button(std::string name, sf::Vector2f position, sf::Font& font)
{
	this->isPressed = 0;
	this->enable = 1;

	sf::Vector2f size;
	size.x = name.size() * (CHAR_SIZE_Button - 7);
	size.y = 2 * (CHAR_SIZE_Button - 7);

	this->shape.setSize(size);					
	this->shape.setPosition(position);
	this->shape.setFillColor(sf::Color::White);

	sf::Text temp;

	temp.setFont(font);
	temp.setCharacterSize(CHAR_SIZE_Button);
	temp.setString(name);
	temp.setFillColor(sf::Color::Black);
	temp.setPosition(position);

	this->text = temp;
}

void Button::SetIsPressed(sf::Vector2i mousePosition)
{

	sf::Vector2f shapePosition = this->shape.getPosition();
	sf::Vector2f shapeSize = this->shape.getSize();

	if (mousePosition.x >= shapePosition.x && mousePosition.x <= shapePosition.x + shapeSize.x &&
		mousePosition.y >= shapePosition.y && mousePosition.y <= shapePosition.y + shapeSize.y)
	{
		this->isPressed = 1;
	}
}

void Button::SetEnable(bool isEnable)
{
	this->enable = isEnable;
	if (isEnable)
		SetShapeColor(sf::Color::White);
	else
		SetShapeColor(sf::Color(192, 192, 192));
}

void Button::SetTextColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void Button::SetShapeColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void Button::SetPosiyion(sf::Vector2f position)
{
	this->shape.setPosition(position);
	this->text.setPosition(position);
}

void Button::SetText(std::string text)
{
	sf::Vector2f size;
	size.x = this->text.getString().getSize() * (CHAR_SIZE_Button - 7);
	size.y = 2 * (CHAR_SIZE_Button - 7);

	this->shape.setSize(size);
	this->text.setString(text);
}

void Button::Draw(sf::RenderWindow& w)
{
	w.draw(this->shape);
	w.draw(this->text);
}

bool Button::IsPressed()
{
	if (this->isPressed == 1)
	{
		this->isPressed = 0;
		return 1;
	}

	return this->isPressed;
}

bool Button::Enable()
{
	return this->enable;
}

void Button::Delete()
{
	sf::RectangleShape temp1;
	sf::Text temp2;

	this->shape = temp1;
	this->text = temp2;
	this->isPressed = 0;
}