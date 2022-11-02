#include "Field.h"
#include "Utilities.h"
void Field::SetText()
{
	std::string temp;
	int fieldWidth = this->field.getSize().x;

	if (this->countOfChar - (fieldWidth / (CHAR_SIZE_FIELD - 7)) >= 0)
	{
		for (int i = this->countOfChar - (fieldWidth / (CHAR_SIZE_FIELD - 7)); i < this->countOfChar; i++)
		{
			temp.push_back(this->input[i]);
		}
	}

	else
	{
		for (int i = 0; i < countOfChar; i++)
		{
			temp.push_back(this->input[i]);
		}
	}
	this->text.setString(temp);
}

Field::Field(sf::Vector2f position, int length, sf::Font& font)
{
	this->countOfChar = 0;

	this->text.setFont(font);
	this->text.setCharacterSize(CHAR_SIZE_FIELD);
	this->text.setPosition(position);
	this->text.setFillColor(sf::Color::Black);

	sf::Vector2f size;
	size.x = length * (CHAR_SIZE_FIELD - 7);
	size.y = 2 * (CHAR_SIZE_FIELD - 7);

	this->field.setSize(size);
	this->field.setPosition(position);
	this->field.setFillColor(sf::Color::White);
}

void Field::AddChar(char& c)
{
	this->input.push_back(c);
	this->countOfChar++;
	
	this->SetText();
}

void Field::SetSring(sf::RenderWindow& w, sf::Event& e)
{
	char temp;

	while (true)
	{
		this->Draw(w);
		w.display();

		w.pollEvent(e);

		if (e.type == sf::Event::KeyPressed)
		{
			temp = IntToChar(e.key.code);
			if (temp == 'e')
				break;
			if (temp == 'b')
				this->PopChar();
			else if(temp != ' ')
			{
				this->AddChar(temp);
			}
		}
	}
}

void Field::PopChar()
{
	if (this->input.size() == 0)
		return;

	this->input.pop_back();
	this->countOfChar--;
	this->SetText();
}

std::string Field::GetInput()
{
	std::string answer = this->input;
	this->CleanUp();
	return answer;
}

int Field::GetCount()
{
	return this->countOfChar;
}

void Field::CleanUp()
{
	sf::Text temp;
	temp.setFont(*this->text.getFont());
	temp.setCharacterSize(this->text.getCharacterSize());
	temp.setPosition(this->text.getPosition());
	temp.setFillColor(sf::Color::Black);

	this->text = temp;
	this->input = std::string();
	this->countOfChar = 0;
}

void Field::Draw(sf::RenderWindow& w)
{
	w.draw(this->field);
	w.draw(this->text);
}

bool Field::OnClick(sf::Vector2i mousePosition)
{
	sf::Vector2f position = this->field.getPosition();
	sf::Vector2f size = this->field.getSize();

	if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
		mousePosition.y >= position.y && mousePosition.y <= position.y + size.y)
	{
		return 1;
	}

	return 0;
}
