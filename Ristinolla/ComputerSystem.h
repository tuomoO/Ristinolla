#pragma once

#include "PlayerSystem.h"

class ComputerSystem : public PlayerSystem
{
public:
    ComputerSystem(std::vector<GameObject*>* my,
        std::vector<GameObject*>* opponent,
        std::vector<GameObject*>* tiles,
        Board* board,
        RenderComponentFactory* renderFactory);
    ~ComputerSystem();

    bool update();
    std::string getMessage() { return " is thinking."; };

private:
    bool blockOpponent();
    bool makeLine();

};

