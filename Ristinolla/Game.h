#pragma once

#include "PlayerSystem.h"
#include "Board.h"
#include "WinSystem.h"
#include "RenderSystem.h"

#include <string>

class Game
{
public:
	Game(Board* board, PlayerSystem* player1, PlayerSystem* player2);
	~Game();

	void update();
	void draw(RenderSystem* renderSystem);

	bool isRunning(){ return mRunning; }
	std::string getMessage(){ return mMessage; };

private:
	void endOfTurn();

	Board* mBoard;
	PlayerSystem* mPlayer1;
	PlayerSystem* mPlayer2;
	PlayerSystem* mPlayerInTurn;
	WinSystem mWinSystem;
	bool mRunning;
	int mTurn;
	std::string mMessage;
};

