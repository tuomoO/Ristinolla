#include "Board.h"
#include "RenderComponentFactory.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;
using Ite = vector<GameObject*>::iterator;

Board::Board(int width, int height, int winLine, int tileSize, int gap)
	:mSize(width, height), mWinLineLength(winLine), mTileSize(tileSize), mTileGap(gap)
{
	mTileOffset = Vector2i(mPosition.x + mTileSize / 2, mPosition.y + mTileSize / 2);
	
	RenderComponentFactory tileRenderFactory;
	BoardComponentFactory boardCompFactory;

	for (int i = 0; i < mSize.y; i++)
	{
		for (int j = 0; j < mSize.x; j++)
		{
			GameObject* obj = new GameObject();
			obj->add(boardCompFactory.make(i, j));
			obj->add(tileRenderFactory.make(mTileSize));
			mTiles.push_back(obj);
			mFreeTiles.push_back(obj);
		}
	}

}


Board::~Board()
{
}

void Board::setPosition(int x, int y)
{
	mPosition = Vector2i(
		x - mSize.x * (mTileSize + mTileGap) / 2,
		y - mSize.y * (mTileSize + mTileGap) / 2);
	mTileOffset = Vector2i(mPosition.x + mTileSize / 2, mPosition.y + mTileSize / 2);
}

Vector2f Board::getTilePosition(int x, int y)
{
	return Vector2f(mTileOffset.x + x * mTileSize + x * mTileGap,
		mTileOffset.y + y * mTileSize + y * mTileGap);
}

Vector2f Board::getTilePosition(Vector2i coordinates)
{
	return getTilePosition(coordinates.x, coordinates.y);
}

string Board::getMessage()
{
	stringstream stream;
	stream << "Form a row of " << mWinLineLength << ". ";
	return stream.str();
}

void Board::markTile(sf::Vector2i position)
{
	for (Ite i = mFreeTiles.begin(); i != mFreeTiles.end(); i++)
	{
		if ((*i)->getComponent<BoardComponent>()->getPosition() == position)
		{
			mFreeTiles.erase(i);
			break;
		}
	}
}

bool Board::isTileFree(Vector2i position)
{
    for (Ite i = mFreeTiles.begin(); i != mFreeTiles.end(); i++)
    {
        if ((*i)->getComponent<BoardComponent>()->getPosition() == position)
            return true;
    }
    return false;
}
