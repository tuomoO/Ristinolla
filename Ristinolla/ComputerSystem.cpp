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

	LongestLine* opBest = mOpponent->getBestLine();
	LongestLine* myBest = getBestLine();


	if (myBest->length > mBoard->getWinLineLength() - 1)
	{
		if (!makeLine())
		{
			if (!makeSecondToBest())
				if (!continueLastLine())
					return randomMove();
		}
	}
	if (opBest->length > mBoard->getWinLineLength() - 1)
	{
		if (!blockOpponent())
		{
			if (!blockSecondToBest())
				if (!continueLastLine())
					return randomMove();
		}
	}
	else if (mOpponent->getBestLine()->length > getBestLine()->length)
	{
		if (!blockOpponent())
		{
			if (!blockSecondToBest())
				if (!continueLastLine())
					return randomMove();
		}
	}
	else if (!makeLine())
	{
		if (!makeSecondToBest())
			if (!blockOpponent())
				if (!blockSecondToBest())
					if (!continueLastLine())
						return randomMove();
	}

	return true;
}

bool ComputerSystem::makeLine(LongestLine* best)
{
	Vector2i tilePosition(-1, -1);
	if (best == nullptr)
		best = getBestLine();

	if (best->length <= 1)
		return startNewLine();
	else
	{
		switch (best->dir)
		{
		case Vertical:
			// up
			tilePosition = Vector2i(best->x1, best->y1 - 1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check down
				tilePosition = Vector2i(best->x2, best->y2 + 1);
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
			tilePosition = Vector2i(best->x1 - 1, best->y1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check right
				tilePosition = Vector2i(best->x2 + 1, best->y2);
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

		case Diagonal1:
			// left+up
			tilePosition = Vector2i(best->x1 - 1, best->y1 - 1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check right+down
				tilePosition = Vector2i(best->x2 + 1, best->y2 + 1);
				for (int i = 1; i < mBoard->getSize().x; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(i, i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(i, i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition += Vector2i(i, i);
						break;
					}
				}
			}
			// check left+up
			else if (isTileMine(tilePosition))
			{
				for (int i = 1; i < mBoard->getSize().x; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(-i, -i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(-i, -i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition += Vector2i(-i, -i);
						break;
					}
				}
			}
			break;

		case Diagonal2:
			// left+down
			tilePosition = Vector2i(best->x1 - 1, best->y1 + 1);
			if (isTileOpponents(tilePosition) || !mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			{
				// check right+up
				tilePosition = Vector2i(best->x2 + 1, best->y2 - 1);
				for (int i = 1; i < mBoard->getSize().x; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(i, -i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(i, -i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition += Vector2i(i, -i);
						break;
					}
				}
			}
			// check left+down
			else if (isTileMine(tilePosition))
			{
				for (int i = 1; i < mBoard->getSize().x; i++)
				{
					if (isTileOpponents(tilePosition + Vector2i(-i, i)) || mBoard->isTileOutBounds(tilePosition + Vector2i(-i, i)))
						break;
					else if (mBoard->isTileFree(tilePosition))
					{
						tilePosition += Vector2i(-i, i);
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

bool ComputerSystem::startNewLine()
{
	Vector2i tilePosition(-1, -1);

	tilePosition = mLastMove->getComponent<BoardComponent>()->getPosition();
	vector<GameObject*>* freeTiles = mBoard->getFreeTiles();
	vector<Vector2i> options;
	Vector2i target = mLastMove->getComponent<BoardComponent>()->getPosition();

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

	// Make sure its not out of the board
	if (mBoard->isTileOutBounds(tilePosition))
		return false;
	if (!mBoard->isTileFree(tilePosition))
		return false;

	addMark(tilePosition);
	return true;
}

bool ComputerSystem::continueLastLine()
{
	Vector2i tilePosition(-1, -1);
	Vector2i lastMove = mLastMove->getComponent<BoardComponent>()->getPosition();
	vector<GameObject*>* myMarks = mBoard->getFreeTiles();
	vector<Vector2i> options;

	for (Ite i = myMarks->begin(); i < myMarks->end(); i++)
	{
		Vector2i pos = (*i)->getComponent<BoardComponent>()->getPosition();
		if (abs(lastMove.x - pos.x) <= 1 && abs(lastMove.y - pos.y) <= 1)
			options.push_back(pos);
	}

	for (vector<Vector2i>::iterator i = options.begin(); i < options.end(); i++)
	{
		Vector2i newPosition = lastMove - *i;
		if (!mBoard->isTileOutBounds(newPosition) && mBoard->isTileFree(tilePosition))
		{
			tilePosition = newPosition;
			break;
		}
	}

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

bool ComputerSystem::blockOpponent(LongestLine* best)
{
	Vector2i tilePosition(-1, -1);
	if (best == nullptr)
		best = mOpponent->getBestLine();
	if (best->length <= 1)
		return false;

	switch (best->dir)
	{
	case Vertical:
		// block up
		tilePosition = Vector2i(best->x1, best->y1 - 1);
		if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			tilePosition = Vector2i(best->x2, best->y2 + 1);
		break;

	case Horizontal:
		// block left
		tilePosition = Vector2i(best->x1 - 1, best->y1);
		if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
			tilePosition = Vector2i(best->x2 + 1, best->y2);
		break;

	case Diagonal1:
		// block left+up
		tilePosition = Vector2i(best->x1 - 1, best->y1 - 1);
		if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
		{
			//block right+down
			tilePosition = Vector2i(best->x2 + 1, best->y2 + 1);
		}
		break;

	case Diagonal2:
		// block left+down
		tilePosition = Vector2i(best->x1 - 1, best->y1 + 1);
		if (!mBoard->isTileFree(tilePosition) || mBoard->isTileOutBounds(tilePosition))
		{
			//block right+up
			tilePosition = Vector2i(best->x2 + 1, best->y2 - 1);
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

bool ComputerSystem::blockSecondToBest()
{
	LongestLine* best = mOpponent->getBestLine();
	LongestLine temp;
	temp.length = 0;
	LongestLine* second = &temp;
	
	if (best->dir != Horizontal && mOpponent->getLongestHorizontal().length > second->length)
		second = &mOpponent->getLongestHorizontal();
	if (best->dir != Vertical && mOpponent->getLongestVertical().length > second->length)
		second = &mOpponent->getLongestVertical();
	if (best->dir != Diagonal1 && mOpponent->getLongestDiagonal1().length > second->length)
		second = &mOpponent->getLongestDiagonal1();
	if (best->dir != Diagonal2 && mOpponent->getLongestDiagonal2().length > second->length)
		second = &mOpponent->getLongestDiagonal2();

	return blockOpponent(second);
}

bool ComputerSystem::makeSecondToBest()
{
	LongestLine* best = getBestLine();
	LongestLine temp;
	temp.length = 0;
	LongestLine* second = &temp;

	if (best->dir != Horizontal && getLongestHorizontal().length > second->length)
		second = &getLongestHorizontal();
	if (best->dir != Vertical && getLongestVertical().length > second->length)
		second = &getLongestVertical();
	if (best->dir != Diagonal1 && getLongestDiagonal1().length > second->length)
		second = &getLongestDiagonal1();
	if (best->dir != Diagonal2 && getLongestDiagonal2().length > second->length)
		second = &getLongestDiagonal2();

	return makeLine(second);
}