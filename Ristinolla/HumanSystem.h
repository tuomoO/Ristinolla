#pragma once

#include "PlayerSystem.h"
#include "Input.h"

class HumanSystem : public PlayerSystem
{
public:
	HumanSystem(sf::Texture* texture, sf::Color color, Input* input);
	~HumanSystem();

	bool update();
	std::string getMessage() { return " make your move."; };

private:
	bool checkClickPos();
	bool findClickedTile(sf::Vector2i& tilePosition);
	
	Input* mInput;
	bool mButtonWasDown;

};

