#pragma once

#include "GameObject.h"
#include "RenderComponentFactory.h"
#include "Board.h"

#include <vector>
#include <string>

class PlayerSystem
{
public:
	PlayerSystem(std::vector<GameObject*>* my,
		std::vector<GameObject*>* opponent,
		std::vector<GameObject*>* tiles,
		Board* board,
		RenderComponentFactory* renderFactory);
	~PlayerSystem();

	virtual bool update() = 0;
	virtual std::string getMessage() = 0;
	std::vector<GameObject*>* getMarks(){ return mMyMarks; };
	GameObject* getLastMove() { return mLastMove; };

protected:
	std::vector<GameObject*>* mMyMarks;
	const std::vector<GameObject*>* mOpponentMarks;
	const std::vector<GameObject*>* mTiles;
	Board* mBoard;
	RenderComponentFactory* mRenderFactory;
	GameObject* mLastMove;
};

