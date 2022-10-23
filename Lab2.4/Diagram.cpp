#include "Diagram.h"

Diagram::Diagram()
{
	this->shapeWidth = 0;
}

int Diagram::GetCountOFShape()
{
	return this->countOfShape;
}
double Diagram::GetShapeWidth()
{
	return this->shapeWidth;
}
double Diagram::GetShapeHeight(int index)
{
	return this->shapeHeight[index];
}
double Diagram::GetScale()
{
	return this->scale;
}

void Diagram::Print(sf::RenderWindow& w)
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color::Black);

	sf::Vector2f position;
	float diagramHeight;

	for (int i = 0; i < this->countOfShape; i++)
	{
		diagramHeight = this->diagram[i].getSize().y;

		line.setSize({ 1,diagramHeight });

		position.x = (i + 1) * this->shapeWidth - 1;
		position.y = WINDOW_HEIGHT - diagramHeight;

		line.setPosition(position);
		w.draw(this->diagram[i]);
		w.draw(line);
	}
}

void Diagram::SetCountOfShapes(int count)
{
	this->countOfShape = count;
}
void Diagram::SetScale(int maxValue)
{
	this->scale = (double)WINDOW_HEIGHT / (double)(2 * maxValue);
}
void Diagram::SetHeight(std::vector<int> res)
{
	double buffer;
	for (int i = 0; i < this->countOfShape; i++)
	{
		buffer = res[i] * this->scale;
		this->shapeHeight.push_back(buffer);
	}
}
void Diagram::SetWidth(int countOfEvent)
{
	this->shapeWidth = WINDOW_WIDTH / countOfEvent;
}
void Diagram::SetDiagram()
{
	std::vector<sf::RectangleShape> temp(this->countOfShape);
	sf::Vector2f size;

	for (int i = 0; i < this->countOfShape; i++)
	{
		size.x = this->shapeWidth;
		size.y = this->shapeHeight[i];

		temp[i].setFillColor(this->color);
		temp[i].setSize(size);
		temp[i].setPosition({i * size.x, WINDOW_HEIGHT - size.y});
	}
	this->diagram = temp;
}
