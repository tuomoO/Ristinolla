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
	int countLineSize(PlayerSystem* player);

	Board* mBoard;
	std::string mMessage;
};

