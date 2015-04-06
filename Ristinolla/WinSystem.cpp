#include "WinSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;

WinSystem::WinSystem(Board* board)
:mBoard(board), mMessage("It's not over yet!")
{
}

WinSystem::~WinSystem()
{
}

bool WinSystem::update(int turn, PlayerSystem* player)
{
	if (turn > mBoard->getWinLineLength() * 2)
	{
		if (countLineSize(player) >= mBoard->getWinLineLength())
		{
			turn % 2 == 0 ? mMessage = "Player 2 wins!" : mMessage = "Player 1 wins!";
			return true;
		}
	}
	if (turn >= mBoard->getSize().x * mBoard->getSize().y)
	{
		mMessage = "Tie!";
		return true;
	}
	return false;
}

int WinSystem::countLineSize(PlayerSystem* player)
{
	int longestLine = 0;
	vector<Vector2i> currentLine;
	vector<vector<Vector2i>> lines;
	Vector2i current = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
	currentLine.push_back(current);
	lines.push_back(currentLine);
	//find all formed lines, choose longest
	
	/*
	for (vector<vector<Vector2i>>::iterator i = lines.begin(); i < lines.end(); i++)
	{
		if ((*i).size() > longestLine)
			longestLine = (*i).size();
	}
	*/
	return longestLine;
}
