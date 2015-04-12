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
    bool blockOpponent();
    bool makeLine();

};

