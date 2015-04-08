#include "ComputerSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

ComputerSystem::ComputerSystem(vector<GameObject*>* my, vector<GameObject*>* opponent, vector<GameObject*>* tiles, Board* board, RenderComponentFactory* renderFactory)
    : PlayerSystem(my, opponent, tiles, board, renderFactory)
{
}


ComputerSystem::~ComputerSystem()
{
}

bool ComputerSystem::update()
{
    switch (rand() % 1)
    {
    case 0:
        return makeLine();

    case 1:
        return blockOpponent();

    default:
        return false;
    }
}

bool ComputerSystem::makeLine()
{
    Vector2i tilePosition = Vector2i(rand() % mBoard->getSize().x,
        rand() % mBoard->getSize().y);

    for (Ite i = mMyMarks->begin(); i != mMyMarks->end(); i++)
    {
        if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
            return false;
    }
    for (ConstIte i = mOpponentMarks->begin(); i != mOpponentMarks->end(); i++)
    {
        if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
            return false;
    }

    addMark(tilePosition);
    return true;
}

bool ComputerSystem::blockOpponent()
{
    return false;
}
