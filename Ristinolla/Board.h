#pragma once

#include "SFML\Graphics.hpp"

#include "GameObject.h"

#include <vector>

class Board
{
public:
	Board(int width, int height, int winLine, int tileSize, int gap);
	~Board();

	void setPosition(int x, int y);
	int getTileSize() { return mTileSize; };
	sf::Vector2f getTilePosition(int x, int y);
	sf::Vector2f getTilePosition(sf::Vector2i coordinates);
	sf::Vector2i getSize() { return mSize; };
	int getWinLineLength() { return mWinLineLength; };

private:
	sf::Vector2i mSize;
	sf::Vector2i mPosition;
	int mWinLineLength;
	int mTileSize;
	sf::Vector2i mTileOffset;
	int mTileGap;
};

