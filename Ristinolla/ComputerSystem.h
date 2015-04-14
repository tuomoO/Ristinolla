#pragma once

#include "PlayerSystem.h"

class ComputerSystem : public PlayerSystem
{
public:
    ComputerSystem(sf::Texture* texture, sf::Color color);
    ~ComputerSystem();

    bool update();
    std::string getMessage() { return " is thinking."; };

private:
	bool makeLine();
	bool startNewLine();
	bool randomMove();
    bool blockOpponent();

};

