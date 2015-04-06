#pragma once

#include "PlayerSystem.h"

class HumanSystem : public PlayerSystem
{
public:
	HumanSystem(std::vector<GameObject*>* my,
		std::vector<GameObject*>* opponent,
		std::vector<GameObject*>* tiles,
		Board* board,
		RenderComponentFactory* renderFactory, sf::Window* window);
	~HumanSystem();

	bool update();
	std::string getMessage() { return " make your move."; };

private:
	bool checkClickPos();
	sf::Vector2f getMousePos();
	bool findClickedTile(sf::Vector2i& tilePosition);
	void addMark(sf::Vector2i tilePosition);

	sf::Window* mWindow;
	bool mButtonWasDown;

};

