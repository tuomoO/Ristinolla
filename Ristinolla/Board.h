#pragma once

#include "SFML\Graphics.hpp"

#include "GameObject.h"

#include <vector>
#include <sstream>

class Board
{
public:
	Board(int width, int height, int winLine, int tileSize, int gap);
	~Board();

	std::vector<GameObject*>* getTiles(){ return &mTiles; };
	std::vector<GameObject*>* getFreeTiles() { return &mFreeTiles; };
	void setPosition(int x, int y);
	int getTileSize() { return mTileSize; };
	sf::Vector2f getTilePosition(int x, int y);
	sf::Vector2f getTilePosition(sf::Vector2i coordinates);
	sf::Vector2i getSize() { return mSize; };
	int getWinLineLength() { return mWinLineLength; };
	std::string getMessage();
	void markTile(sf::Vector2i position);

private:
	std::vector<GameObject*> mTiles;
	std::vector<GameObject*> mFreeTiles;
	sf::Vector2i mSize;
	sf::Vector2i mPosition;
	int mWinLineLength;
	int mTileSize;
	sf::Vector2i mTileOffset;
	int mTileGap;
};

