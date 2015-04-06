#pragma once

#include "BoardComponent.h"

#include <vector>

class BoardComponentFactory
{
public:
	BoardComponentFactory();
	~BoardComponentFactory();

	BoardComponent* make(int x, int y);
	BoardComponent* make(sf::Vector2i position);

private:
};

