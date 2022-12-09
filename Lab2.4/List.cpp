#include"List.h"

List::List(int countOfVisibleElements)
{
	this->countOfElements = 0;
	this->width = 0;
	this->countOfVisibleElements = countOfVisibleElements;
	this->currentIndex = 0;
	this->position = { 0,0 };
}

List::List(std::string name, sf::Vector2f position, int width, sf::Font& f, int countOfVisibleElements)
{
	Panel temp(name, position, f);
	temp.SetWidth(width);
	temp.SetShapeColor(sf::Color(175, 238, 238));
	this->countOfElements = 1;
	this->width = width;
	this->currentIndex = 0;
	this->position = position;
	this->countOfVisibleElements = countOfVisibleElements;
	this->list.push_back(temp);
}

void List::Draw(sf::RenderWindow& w)
{
	if (this->currentIndex == 0)
	{
		for (int i = this->currentIndex; i < this->currentIndex+ this->countOfVisibleElements + 1 && i < this->countOfElements; i++)
		{
			this->list[i].Draw(w);
		}
	}
	else
	{
		this->list[0].Draw(w);
		for (int i = this->currentIndex + 1; i < this->currentIndex+ 1 + this->countOfVisibleElements && i < this->countOfElements; i++)
		{
			this->list[i].Draw(w);
		}
	}
}

void List::AddElement(std::string name, sf::Font& f)
{
	sf::Vector2f tempPosition;
	tempPosition.y = this->list[0].GetShape().getPosition().y + (((this->countOfElements - 1) % (this->countOfVisibleElements)) + 1) * this->list[0].GetShape().getSize().y;
	tempPosition.x = this->list[0].GetShape().getPosition().x;


	Panel tempPanel(name,tempPosition, f);

	this->countOfElements++;
	tempPanel.SetWidth(this->width);
	this->list.push_back(tempPanel);
}

int List::GetCountOfElements()
{
	return this->countOfElements;
}

int List::GetCountOfVisibleElements()
{
	return this->countOfVisibleElements;
}

int List::GetWidth()
{
	return this->width;
}

sf::Vector2f List::GetPosition()
{
	return this->position;
}

void List::Clear()
{
	for (int i = 1; i < this->countOfElements; i++)
	{
		this->list[i].Clean();
	}
	this->currentIndex = 0;
	this->countOfElements = 1;
	std::vector<Panel> temp;
	temp.push_back(this->list[0]);
	this->list = temp;
}

void List::ScrollUP()
{
	if (this->currentIndex - this->countOfVisibleElements >= 0)
		this->currentIndex -= this->countOfVisibleElements;
	else
		this->currentIndex = 0;
}

void List::ScrollDOWN()
{
	if (this->currentIndex + this->countOfVisibleElements - (this->countOfElements - 1) < 0)
		this->currentIndex += this->countOfVisibleElements;
}
