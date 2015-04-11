#pragma once

#include "GameObject.h"
#include "RenderComponentFactory.h"
#include "Board.h"

#include <vector>
#include <string>

class PlayerSystem
{
	struct longestLine {

		int x1;
		int y1;
		int x2;
		int y2;
		int length;
	};
public:
	PlayerSystem(std::string texturePath, sf::Color color);
	~PlayerSystem();

	void initialize(Board* board, PlayerSystem* opponent);
	bool isInitialized() { return mInitialized; };

	virtual bool update() = 0;
	virtual std::string getMessage() = 0;

	std::vector<GameObject*>* getMarks(){ return &mMyMarks; };
	GameObject* getLastMove() { return mLastMove; };

	void setLongestVertical(int x1, int y1, int x2, int y2, int length);
	longestLine getLongestVertical(){ return verticalLine; };

	void setLongestHorizontal(int x1, int y1, int x2, int y2, int length);
	longestLine getLongestHorizontal(){ return horizontalLine; };

protected:
    void addMark(sf::Vector2i tilePosition);

	longestLine verticalLine;
	longestLine horizontalLine;

	std::vector<GameObject*> mMyMarks;
	PlayerSystem* mOpponent;
	Board* mBoard;
	RenderComponentFactory* mRenderFactory;
	GameObject* mLastMove;

private:
	bool mInitialized;
};

