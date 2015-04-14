#pragma once

#include "GameObject.h"
#include "RenderComponentFactory.h"
#include "Board.h"

#include <vector>
#include <string>

enum LineDirection {
	Horizontal, Vertical, Diagonal1, Diagonal2
};

struct LongestLine {
	LineDirection dir;
	int x1;
	int y1;
	int x2;
	int y2;
	int length;
};

class PlayerSystem
{
public:
	PlayerSystem(sf::Texture* texture, sf::Color color);
	~PlayerSystem();

	void initialize(Board* board, PlayerSystem* opponent);
	bool isInitialized() { return mInitialized; };

	virtual bool update() = 0;
	virtual std::string getMessage() = 0;

	std::vector<GameObject*>* getMarks(){ return &mMyMarks; };
	GameObject* getLastMove() { return mLastMove; };

	LongestLine* getBestLine();

	void setLongestVertical(int x1, int y1, int x2, int y2, int length);
	LongestLine getLongestVertical(){ return verticalLine; };

	void setLongestHorizontal(int x1, int y1, int x2, int y2, int length);
	LongestLine getLongestHorizontal(){ return horizontalLine; };

	bool isTileMine(sf::Vector2i position);
	bool isTileOpponents(sf::Vector2i position);

    void highlightLine();

protected:
    void addMark(sf::Vector2i tilePosition);
	void initializeLongestLines(sf::Vector2i position);

	LongestLine verticalLine;
	LongestLine horizontalLine;
    LongestLine diagonalLine1; // left up -> right down
    LongestLine diagonalLine2; //right up -> left down

	std::vector<GameObject*> mMyMarks;
	PlayerSystem* mOpponent;
	Board* mBoard;
	RenderComponentFactory* mRenderFactory;
	GameObject* mLastMove;

private:
	bool mInitialized;
};

