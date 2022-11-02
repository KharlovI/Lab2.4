#include "Panel.h"

Panel::Panel()
{
	this->countOfChar = 0;
}

Panel::Panel(std::string text, sf::Vector2f position, sf::Font& font)
{
	sf::Text temp;	
	this->countOfChar = text.size();

	sf::Vector2f size;
	size.x = this->countOfChar * (CHAR_SIZE_PANEL - 7);
	size.y = 2 * (CHAR_SIZE_PANEL - 7);

	this->shape.setSize(size);
	this->shape.setPosition(position);
	this->shape.setFillColor(sf::Color::White);

	temp.setFont(font);
	temp.setCharacterSize(CHAR_SIZE_PANEL);
	temp.setFillColor(sf::Color::Black);
	temp.setString(text);
	temp.setPosition(position);

	this->text = temp;
}

void Panel::Draw(sf::RenderWindow& w)
{
	w.draw(this->shape);
	w.draw(this->text);
}

void Panel::SetText(std::string text)
{
	this->countOfChar = text.size();
	sf::Vector2f size;

	size.x = (CHAR_SIZE_PANEL - 7) * countOfChar;
	size.y = (CHAR_SIZE_PANEL - 7) * 2;

	this->shape.setSize(size);
	this->text.setString(text);
}

void Panel::SetPosition(sf::Vector2f position)
{
	this->shape.setPosition(position);
	this->text.setPosition({ position.x , position.y + CHAR_SIZE_PANEL / 2 });
}

void Panel::Clean()
{
	sf::Text temp;
	temp.setPosition(this->text.getPosition());
	temp.setFont(*this->text.getFont());
	temp.setCharacterSize(this->text.getCharacterSize());
	temp.setFillColor(sf::Color::Black);

	this->shape.setSize({ 0,0 });
}

void Panel::SetShapeColor(sf::Color c)
{
	this->shape.setFillColor(c);
}
void Panel::SetTextColor(sf::Color c)
{
	this->text.setFillColor(c);
}
