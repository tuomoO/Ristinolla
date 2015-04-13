#include "WinSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using GoIt = vector<GameObject*>::iterator;

WinSystem::WinSystem(Board* board)
:mBoard(board), mMessage("It's not over yet!")
{
}

WinSystem::~WinSystem()
{
}

bool WinSystem::update(int turn, PlayerSystem* player)
{
	if (turn >= (mBoard->getWinLineLength() * 2) -1)
	{
        if (countLongestLine(player) >= mBoard->getWinLineLength())
		{
			turn % 2 == 0 ? mMessage = "Player 2 wins!" : mMessage = "Player 1 wins!";
			return true;
		}
	}
	else if (turn >= mBoard->getSize().x * mBoard->getSize().y)
	{
		mMessage = "Tie!";
		return true;
	}
    if (mBoard->getFreeTiles()->size() <= 0)
    {
        mMessage = "Tie!";
        return true;
    }

	return false;
}

int WinSystem::countLongestLine(PlayerSystem* player)
{
    int longestLine = countVertical(player);

    int temp = countHorizontal(player);
    if (temp > longestLine)
        longestLine = temp;

    temp = countDiagonal1(player);
    if (temp > longestLine)
        longestLine = temp;

    temp = countDiagonal2(player);
    if (temp > longestLine)
        longestLine = temp;

	return longestLine;
}

int WinSystem::countVertical(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();
    int x = lastMove.x;

    // down
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y + i;
            if (y >= mBoard->getSize().y)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
				if (player->getLongestVertical().length <= longestLine)
					player->setLongestVertical(mark.x, mark.y, player->getLongestVertical().x2, player->getLongestVertical().y2, longestLine);
                found = true;
            }
        }
        if (!found)
            break;
    }

    // up
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y - i;
            if (y < 0)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
				if (player->getLongestVertical().length <= longestLine)
					player->setLongestVertical(player->getLongestVertical().x1, player->getLongestVertical().y1, mark.x, mark.y, longestLine);
                found = true;
            }
        }
        if (!found)
            break;
    }

    return longestLine;
}

int WinSystem::countHorizontal(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();
    int y = lastMove.y;

    //right
    for (int i = 1; i < mBoard->getSize().x; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int x = lastMove.x + i;
            if (x >= mBoard->getSize().x)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
				if (player->getLongestHorizontal().length <= longestLine)
					player->setLongestHorizontal(player->getLongestHorizontal().x1, player->getLongestHorizontal().y1, mark.x, mark.y, longestLine);
                found = true;
            }
        }
        if (!found)
            break;
    }

    //left
    for (int i = 1; i < mBoard->getSize().x; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int x = lastMove.x - i;
            if (x < 0)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
				if (player->getLongestHorizontal().length <= longestLine)
					player->setLongestHorizontal(mark.x, mark.y, player->getLongestHorizontal().x2, player->getLongestHorizontal().y2, longestLine);
                found = true;
            }
        }
        if (!found)
            break;
    }

    return longestLine;
}

// left up -> right down
int WinSystem::countDiagonal1(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();

    // down
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y + i;
            if (y >= mBoard->getSize().y)
                break;

            int x = lastMove.x + i;
            if (x >= mBoard->getSize().x)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
                found = true;
            }
        }
        if (!found)
            break;
    }

    // up
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y - i;
            if (y < 0)
                break;

            int x = lastMove.x - i;
            if (x < 0)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
                found = true;
            }
        }
        if (!found)
            break;
    }

    return longestLine;
}

// right up -> left down
int WinSystem::countDiagonal2(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();

    // down
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y + i;
            if (y >= mBoard->getSize().y)
                break;

            int x = lastMove.x - i;
            if (x < 0)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
                found = true;
            }
        }
        if (!found)
            break;
    }

    // up
    for (int i = 1; i < mBoard->getSize().y; i++)
    {
        bool found = false;
        for (GoIt j = marks->begin(); j != marks->end(); j++)
        {
            int y = lastMove.y - i;
            if (y < 0)
                break;

            int x = lastMove.x + i;
            if (x >= mBoard->getSize().x)
                break;

            Vector2i mark = (*j)->getComponent<BoardComponent>()->getPosition();
            if (mark.x == x && mark.y == y)
            {
                longestLine++;
                found = true;
            }
        }
        if (!found)
            break;
    }

    return longestLine;
}
