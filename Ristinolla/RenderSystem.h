#pragma once

#include <SFML/Graphics.hpp>
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "BoardComponent.h"
#include "GameObject.h"
#include "Board.h"
#include "PlayerSystem.h"

class RenderSystem
{
public:
	RenderSystem(sf::RenderWindow* window, Board* board = nullptr);
	~RenderSystem();

	void draw(GameObject* gameObject);
	void draw(PlayerSystem* player);
	void draw(Board* board);
	void swapBuffers();
	void setBoard(Board* board) { mBoard = board; };

private:
	sf::RenderWindow* mWindow;
	Board* mBoard;
};

