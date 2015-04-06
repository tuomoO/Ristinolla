#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class BoardComponent : public Component
{
	friend class BoardComponentFactory;

public:
	~BoardComponent();

	sf::Vector2i getPosition();

private:
	BoardComponent(int x, int y);
	BoardComponent(sf::Vector2i position);
	sf::Vector2i mPosition;

};

