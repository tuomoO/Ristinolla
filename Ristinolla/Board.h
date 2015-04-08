#pragma once

#include "SFML\Graphics.hpp"

#include "GameObject.h"

#include <vector>

class Board
{
public:
	Board(int width, int height, int winLine, int tileSize, int gap);
	~Board();

	std::vector<GameObject*>* getTiles(){ return &mTiles; };
	void setPosition(int x, int y);
	int getTileSize() { return mTileSize; };
	sf::Vector2f getTilePosition(int x, int y);
	sf::Vector2f getTilePosition(sf::Vector2i coordinates);
	sf::Vector2i getSize() { return mSize; };
	int getWinLineLength() { return mWinLineLength; };

private:
	std::vector<GameObject*> mTiles;
	sf::Vector2i mSize;
	sf::Vector2i mPosition;
	int mWinLineLength;
	int mTileSize;
	sf::Vector2i mTileOffset;
	int mTileGap;
};

