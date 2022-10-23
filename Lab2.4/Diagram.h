#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include"Experiment.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

class Diagram
{
private:
	std::vector<sf::RectangleShape> diagram;
	int countOfShape = 0;
	double scale = 0;
	double shapeWidth;
	std::vector<double> shapeHeight;
	sf::Color color = sf::Color::Cyan;
public:
	Diagram();

	int GetCountOFShape();
	double GetShapeWidth();
	double GetShapeHeight(int index);
	double GetScale();

	void Print(sf::RenderWindow& w);

	void SetCountOfShapes(int count);
	void SetScale(int maxValue);
	void SetHeight(std::vector<int> res);
	void SetWidth(int countOfEvent);
	void SetDiagram();
};

