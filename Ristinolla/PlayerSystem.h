#pragma once

#include "GameObject.h"
#include "RenderComponentFactory.h"
#include "Board.h"

#include <vector>
#include <string>

class PlayerSystem
{
public:
	PlayerSystem(std::string texturePath, sf::Color color);
	~PlayerSystem();

	void initialize(Board* board, PlayerSystem* opponent);
	bool isInitialized() { return mInitialized; };

	virtual bool update() = 0;
	virtual std::string getMessage() = 0;

	std::vector<GameObject*>* getMarks(){ return &mMyMarks; };
	GameObject* getLastMove() { return mLastMove; };

protected:
    void addMark(sf::Vector2i tilePosition);

	std::vector<GameObject*> mMyMarks;
	PlayerSystem* mOpponent;
	Board* mBoard;
	RenderComponentFactory* mRenderFactory;
	GameObject* mLastMove;

private:
	bool mInitialized;
};

