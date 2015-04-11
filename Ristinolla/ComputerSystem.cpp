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
	// TODO 
	// if tile is not free, check the other end of the line

	Vector2i tilePosition;

	switch (rand() % 1)
	{
	case 0:
		if (mOpponent->getLongestVertical().length > 1)
		{
			// block down
			//tilePosition = Vector2i(mOpponent->getLongestVertical().x2, mOpponent->getLongestVertical().y2 + 2);

			// block up
			tilePosition = Vector2i(mOpponent->getLongestVertical().x1, mOpponent->getLongestVertical().y1 - 2);
		}

	case 1:
		if (mOpponent->getLongestHorizontal().length > 1)
		{
			// block right
			//tilePosition = Vector2i(mOpponent->getLongestHorizontal().x1 + 2, mOpponent->getLongestHorizontal().y1);

			// block left
			tilePosition = Vector2i(mOpponent->getLongestHorizontal().x2 - 2, mOpponent->getLongestHorizontal().y2);
		}

		for (Ite i = mMyMarks.begin(); i != mMyMarks.end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				tilePosition = Vector2i(0, 0);
		}
		vector<GameObject*>* opponentsMarks = mOpponent->getMarks();
		for (ConstIte i = opponentsMarks->begin(); i != opponentsMarks->end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				tilePosition = Vector2i(0, 0);
		}

		// Make sure its not out of the board
		if (tilePosition.x < 0 || tilePosition.y < 0 ||
			tilePosition.x > mBoard->getSize().x ||
			tilePosition.y > mBoard->getSize().y
			)
			tilePosition = Vector2i(0, 0);

		addMark(tilePosition);
		mBoard->markTile(tilePosition);
		return true;
	}
}
