#pragma once

#include <SFML/Graphics.hpp>
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "BoardComponent.h"
#include "GameObject.h"
#include "Board.h"

class RenderSystem
{
public:
	RenderSystem(sf::RenderWindow* window, Board* board = nullptr);
	~RenderSystem();

	void draw(GameObject* gameObject);
	void swapBuffers();

private:
	sf::RenderWindow* mWindow;
	Board* mBoard;
};

