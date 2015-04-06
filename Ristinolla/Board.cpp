#include "Board.h"

using namespace std;
using namespace sf;

Board::Board(int width, int height, int winLine, int tileSize, int gap)
	:mSize(width, height), mWinLineLength(winLine), mTileSize(tileSize), mTileGap(gap)
{
	mTileOffset = Vector2i(mPosition.x + mTileSize / 2, mPosition.y + mTileSize / 2);
}


Board::~Board()
{
}

void Board::setPosition(int x, int y)
{
	mPosition = Vector2i(x, y);
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
