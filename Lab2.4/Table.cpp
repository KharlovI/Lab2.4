#include "Table.h"

Table::Table()
{
	this->countOfColumn = 0;
	this->countOfString = 0;
}

std::vector<List> Table::GetTable()
{
	return this->table;
}

List Table::GetTable(int index)
{
	return this->table[index];
}

int Table::GetCountOfColumn()
{
	return this->countOfColumn;
}

int Table::GetCountOfString()
{
	return this->countOfString;
}

void Table::AddColumn(List& list)
{
	this->countOfColumn++;
	this->countOfString = list.GetCountOfElements();
	this->table.push_back(list);
}

void Table::AddString(std::vector<std::string> names, sf::Font& f)
{
	for (int i = 0; i < this->countOfColumn; i++)
	{
		this->table[i].AddElement(names[i], f);
	}
}

void Table::Draw(sf::RenderWindow& w)
{
	for (int i = 0; i < this->countOfColumn; i++)
	{
		this->table[i].Draw(w);
	}
}

void Table::SetColumnByIndex(int index, List column)
{
	this->table[index] = column;
}

void Table::ScrollDown()
{
	/*if (index + this->table[0].GetCountOfVisibleElements() - (this->table[0].GetCountOfElements() - 1) < 0)
		index += this->table[0].GetCountOfVisibleElements();*/

	for (int i = 0; i < this->countOfColumn; i++)
	{
		this->table[i].ScrollDOWN();
	}
}

void Table::ScrollUp()
{
	/*if (index - this->table[0].GetCountOfVisibleElements() >= 0)
		index -= this->table[0].GetCountOfVisibleElements();
	else
		index = 0;*/

	for (int i = 0; i < this->countOfColumn; i++)
	{
		this->table[i].ScrollUP();
	}
}
