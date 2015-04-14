#include "Game.h"

using namespace std;
using namespace sf;

Game::Game(Board* board, PlayerSystem* player1, PlayerSystem* player2)
: mBoard(board), mPlayer1(player1), mPlayer2(player2), mWinSystem(board), mRunning(true), mTurn(1)
{
	mPlayerInTurn = player1;
	mMessage = mBoard->getMessage() + "Player 1" + mPlayerInTurn->getMessage();
}


Game::~Game()
{
	delete mPlayer1;
	delete mPlayer2;
	delete mBoard;
}

void Game::update()
{
	if (mPlayerInTurn->update())
		endOfTurn();
}

void Game::draw(RenderSystem* renderSystem)
{
	renderSystem->draw(mBoard);
	renderSystem->draw(mPlayer1);
	renderSystem->draw(mPlayer2);
}

void Game::endOfTurn()
{
	if (mWinSystem.update(mTurn, mPlayerInTurn))
	{
		mMessage = mBoard->getMessage() + mWinSystem.getMessage();
		mRunning = false;
        mPlayerInTurn->highlightLine();
	}
	else
	{
		string msg = "Player ";
		if (mPlayerInTurn == mPlayer1)
		{
			mPlayerInTurn = mPlayer2;
			msg.append("2");
		}
		else
		{
			mPlayerInTurn = mPlayer1;
			msg.append("1");
		}

		mMessage = mBoard->getMessage() + msg + mPlayerInTurn->getMessage();
	}
	mTurn++;
}
