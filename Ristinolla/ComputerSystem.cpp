#include "ComputerSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

ComputerSystem::ComputerSystem(string texturePath, Color color)
    : PlayerSystem(texturePath, color)
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
	vector<GameObject*>* freeTiles = mBoard->getFreeTiles();
	int index = rand() % freeTiles->size();
	Vector2i tilePosition(freeTiles->at(index)->getComponent<BoardComponent>()->getPosition());
	/*
    Vector2i tilePosition = Vector2i(rand() % mBoard->getSize().x,
        rand() % mBoard->getSize().y);

    for (Ite i = mMyMarks.begin(); i != mMyMarks.end(); i++)
    {
        if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
            return false;
    }
	vector<GameObject*>* opponentsMarks = mOpponent->getMarks();
    for (ConstIte i = opponentsMarks->begin(); i != opponentsMarks->end(); i++)
    {
        if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
            return false;
    }
	void markTile(int x, int y);
	*/
    addMark(tilePosition);
	mBoard->markTile(tilePosition);
    return true;
}

bool ComputerSystem::blockOpponent()
{
    return false;
}
