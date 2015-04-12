#pragma once

#include "SFML\Graphics.hpp"

#include <string.h>

class Button
{
public:
	Button(int id, sf::Font* font, std::string text, float x, float y);
	~Button();

	bool update(int x, int y);
	bool update(sf::Vector2i position);

	void draw(sf::RenderWindow* window);
	int getId(){ return mId; };

private:
	int mId;
	sf::RectangleShape mShape;
	sf::Text mText;

};

