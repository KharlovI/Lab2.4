#pragma once
#include"List.h"
class Table
{
private:
	std::vector<List> table;
	int countOfColumn;
	int countOfString;
	int showCount;
	

public:
	Table();
	std::vector<List> GetTable();
	List GetTable(int index);
	int GetCountOfColumn();
	int GetCountOfString();
	void AddColumn(List& list);
	void AddString(std::vector<std::string> names,  sf::Font& f);
	void Draw(sf::RenderWindow& w);
	void SetColumnByIndex(int index, List column);
	void ScrollDown();
	void ScrollUp();
};

