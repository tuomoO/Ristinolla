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

	if (best->length <= 1)
	{
		tilePosition = mLastMove->getComponent<BoardComponent>()->getPosition();
		vector<GameObject*>* freeTiles = mBoard->getFreeTiles();
		vector<Vector2i> options;
		Vector2i target = mLastMove->getComponent<BoardComponent>()->getPosition();
		if (target.x < 0)
			target.x = 0;
		if (target.y < 0)
			target.y = 0;
		if (target.x > mBoard->getSize().x - 1)
			target.x = mBoard->getSize().x - 1;
		if (target.y > mBoard->getSize().y - 1)
			target.y = mBoard->getSize().y - 1;

		for (Ite i = freeTiles->begin(); i < freeTiles->end(); i++)
		{
			Vector2i pos = (*i)->getComponent<BoardComponent>()->getPosition();
			if (abs(target.x - pos.x) <= 1 && abs(target.y - pos.y) <= 1)
				options.push_back(pos);
		}
		//no free tiles around last move
		if (options.empty())
			return false;

		tilePosition = options.at(rand() % options.size());
	}
	else
	{
		switch (best->dir)
		{
		case Vertical:
			// up
			tilePosition = Vector2i(getLongestVertical().x1, getLongestVertical().y1 - 1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check down
				tilePosition = Vector2i(getLongestVertical().x2, getLongestVertical().y2 + 1);
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
			// check up
			else if (isTileMine(tilePosition))
			{
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

			break;

		case Horizontal:
			// left
			tilePosition = Vector2i(getLongestHorizontal().x1 - 1, getLongestHorizontal().y1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check right
				tilePosition = Vector2i(getLongestHorizontal().x2 + 1, getLongestHorizontal().y2);
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
			// check left
			else if (isTileMine(tilePosition))
			{
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

			break;

		default:
			return false;
		}
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
		if (mOpponent->getLongestVertical().length > 1)
		{
			// block up
			tilePosition = Vector2i(mOpponent->getLongestVertical().x1, mOpponent->getLongestVertical().y1 - 1);
			if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
				tilePosition = Vector2i(mOpponent->getLongestVertical().x2, mOpponent->getLongestVertical().y2 + 1);	
		}
        break;

	case Horizontal:
		if (mOpponent->getLongestHorizontal().length > 1)
		{
			// block left
			tilePosition = Vector2i(mOpponent->getLongestHorizontal().x1 - 1, mOpponent->getLongestHorizontal().y1);
			if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
				tilePosition = Vector2i(mOpponent->getLongestHorizontal().x2 + 1, mOpponent->getLongestHorizontal().y2);
		}
        break;

	case Diagonal1:
		break;

	case Diagonal2:

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
