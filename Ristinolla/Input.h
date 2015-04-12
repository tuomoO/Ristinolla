#pragma once

#include "SFML\Graphics.hpp"

class Input
{
public:
	Input(sf::RenderWindow* window);
	~Input();
	bool update();
	sf::Vector2i getPosition();
	sf::Vector2f getPositionf();

private:
	sf::RenderWindow* mWindow;
	bool mButtonWasDown;

};

