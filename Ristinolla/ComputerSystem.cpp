#include "ComputerSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

ComputerSystem::ComputerSystem(Texture* texture, Color color)
    : PlayerSystem(texture, color)
{
}


ComputerSystem::~ComputerSystem()
{
}

bool ComputerSystem::update()
{
    if (mOpponent->getLongestLineLength() > 1)
    {
        if (!blockOpponent())
        {
            if (!makeLine())
                return randomMove();
        }
    }
    else
        return randomMove();

    return true;

    /*
    switch (rand() % 1)
    {
    case 0:
        return makeLine();

    case 1:
        return blockOpponent();

    default:
        return false;
    }
    */
}

bool ComputerSystem::makeLine()
{
    return false;
}

bool ComputerSystem::randomMove()
{
    vector<GameObject*>* freeTiles = mBoard->getFreeTiles();
    int index = rand() % freeTiles->size();
    Vector2i tilePosition(freeTiles->at(index)->getComponent<BoardComponent>()->getPosition());
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
        break;

	case 1:
		if (mOpponent->getLongestHorizontal().length > 1)
		{
			// block right
			//tilePosition = Vector2i(mOpponent->getLongestHorizontal().x1 + 2, mOpponent->getLongestHorizontal().y1);

			// block left
			tilePosition = Vector2i(mOpponent->getLongestHorizontal().x2 - 2, mOpponent->getLongestHorizontal().y2);
		}
        break;

    default:
        return false;
	}
    // Make sure its not out of the board
    if (tilePosition.x < 0 || tilePosition.y < 0 ||
        tilePosition.x > mBoard->getSize().x ||
        tilePosition.y > mBoard->getSize().y
        )
        return false;
    if (!mBoard->isTileFree(tilePosition))
        return false;

	addMark(tilePosition);
	mBoard->markTile(tilePosition);
	return true;
}
