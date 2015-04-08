#pragma once

#include "HumanSystem.h"

class WinSystem
{
public:
	WinSystem(Board* board);
	~WinSystem();

	bool update(int turn, PlayerSystem* player);
	std::string getMessage() { return mMessage; };

private:
	int countLongestLine(PlayerSystem* player);
    int countVertical(PlayerSystem* player);
    int countHorizontal(PlayerSystem* player);
    int countDiagonal1(PlayerSystem* player);
    int countDiagonal2(PlayerSystem* player);

	Board* mBoard;
	std::string mMessage;
};

