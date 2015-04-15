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
	bool makeLine(LongestLine* best = nullptr);
	bool startNewLine();
	bool continueLastLine();
	bool randomMove();
	bool blockOpponent(LongestLine* best = nullptr);
	bool blockSecondToBest();
	bool makeSecondToBest();
};

