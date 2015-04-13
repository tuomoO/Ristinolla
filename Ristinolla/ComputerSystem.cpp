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
	if (mMyMarks.size() == 0 || getBestLine()->length == 0)
		return randomMove();

	if (mOpponent->getBestLine()->length > getBestLine()->length)
	{
		if (!blockOpponent())
			if (!makeLine())
				return randomMove();
	}
	else if (!makeLine())
		if (!blockOpponent())
			return randomMove();

    return true;
}

bool ComputerSystem::makeLine()
{
	Vector2i tilePosition(-1, -1);
	LongestLine* best = getBestLine();

	/*
	if (best->length <= 1)
	{
		tilePosition = mLastMove->getComponent<BoardComponent>()->getPosition();
		
	}
	*/

	switch (best->dir)
	{
	case Vertical:
			// block up
			tilePosition = Vector2i(getLongestVertical().x1, getLongestVertical().y1 - 1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				//down
				tilePosition = Vector2i(getLongestVertical().x2, getLongestVertical().y2 + 1);
				for (int i = 1; i < mBoard->getSize().y; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(0, -i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(0, -i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition.y -= i;
						break;
					}
				}
			}
			else if (isTileMine(tilePosition))
			{
				//up
				for (int i = 1; i < mBoard->getSize().y; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(0, i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(0, i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition.y += i;
						break;
					}
				}
			}

		break;

	case Horizontal:
		/*
		tilePosition = Vector2i(getLongestHorizontal().x1 - 1, getLongestHorizontal().y1);
		if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			tilePosition = Vector2i(getLongestHorizontal().x2 + 1, getLongestHorizontal().y2);
		*/
		tilePosition = Vector2i(getLongestHorizontal().x1 - 1, getLongestHorizontal().y1);
		if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
		{
			//right
			tilePosition = Vector2i(getLongestHorizontal().x2 +1, getLongestHorizontal().y2);
			for (int i = 1; i < mBoard->getSize().x; i++)
			{
				if (isTileOpponents(tilePosition + Vector2i(-i, 0)) || mBoard->isTileOutBounds(tilePosition + Vector2i(-i, 0)))
					break;
				else if (mBoard->isTileFree(tilePosition))
				{
					tilePosition.x -= i;
					break;
				}
			}
		}
		else if (isTileMine(tilePosition))
		{
			//left
			for (int i = 1; i < mBoard->getSize().x; i++)
			{
				if (isTileOpponents(tilePosition + Vector2i(i, 0)) || mBoard->isTileOutBounds(tilePosition + Vector2i(i, 0)))
					break;
				else if (mBoard->isTileFree(tilePosition))
				{
					tilePosition.x += i;
					break;
				}
			}
		}
		
		break;

	default:
		return false;
	}
	// Make sure its not out of the board

	if (mBoard->isTileOutBounds(tilePosition))
		return false;
	if (!mBoard->isTileFree(tilePosition))
		return false;

	addMark(tilePosition);
	return true;
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
	Vector2i tilePosition(-1, -1);
	LongestLine* best = mOpponent->getBestLine();
	switch (best->dir)
	{
	case Vertical:
		if (mOpponent->getLongestVertical().length > 0)
		{
			// block up
			tilePosition = Vector2i(mOpponent->getLongestVertical().x1, mOpponent->getLongestVertical().y1 - 1);
			if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
				tilePosition = Vector2i(mOpponent->getLongestVertical().x2, mOpponent->getLongestVertical().y2 + 1);	
		}
        break;

	case Horizontal:
		if (mOpponent->getLongestHorizontal().length > 0)
		{
			// block left
			tilePosition = Vector2i(mOpponent->getLongestHorizontal().x1 - 1, mOpponent->getLongestHorizontal().y1);
			if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
				tilePosition = Vector2i(mOpponent->getLongestHorizontal().x2 + 1, mOpponent->getLongestHorizontal().y2);
		}
        break;

    default:
        return false;
	}
    // Make sure its not out of the board

	if (mBoard->isTileOutBounds(tilePosition))
		return false;
    if (!mBoard->isTileFree(tilePosition))
        return false;

	addMark(tilePosition);
	return true;
}
