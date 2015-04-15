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
	if (countLongestLine(player) >= mBoard->getWinLineLength())
	{
		turn % 2 == 0 ? mMessage = "Player 2 wins!" : mMessage = "Player 1 wins!";
		player->highlightLine();
		return true;
	}
	if (turn >= mBoard->getSize().x * mBoard->getSize().y)
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
	Vector2i up(lastMove.x, lastMove.y);
	Vector2i down(lastMove.x, lastMove.y);

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
				down = mark;
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
				up = mark;
				found = true;
            }
        }
        if (!found)
            break;
    }

	if (player->getLongestVertical().length <= longestLine)
		player->setLongestVertical(up.x, up.y, down.x, down.y, longestLine);

    return longestLine;
}

int WinSystem::countHorizontal(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();
	int y = lastMove.y;

	Vector2i right(lastMove.x, lastMove.y);
	Vector2i left(lastMove.x, lastMove.y);

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
				right = mark;
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
				left = mark;
				found = true;
            }
        }
        if (!found)
            break;
    }

	if (player->getLongestHorizontal().length <= longestLine)
		player->setLongestHorizontal(left.x, left.y, right.x, right.y, longestLine);

    return longestLine;
}

// left up -> right down
int WinSystem::countDiagonal1(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();
	
	Vector2i leftUp(lastMove.x, lastMove.y);
	Vector2i rightDown(lastMove.x, lastMove.y);

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
				rightDown = mark;
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
				leftUp = mark;
                found = true;
            }
        }
        if (!found)
            break;
    }
	if (player->getLongestDiagonal1().length <= longestLine)
		player->setLongestDiagonal1(leftUp.x, leftUp.y, rightDown.x, rightDown.y, longestLine);

    return longestLine;
}

// right up -> left down
int WinSystem::countDiagonal2(PlayerSystem* player)
{
    int longestLine = 1;
    Vector2i lastMove = player->getLastMove()->getComponent<BoardComponent>()->getPosition();
    vector<GameObject*>* marks = player->getMarks();

	Vector2i leftDown(lastMove.x, lastMove.y);
	Vector2i rightUp(lastMove.x, lastMove.y);

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
				leftDown = mark;
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
				rightUp = mark;
                found = true;
            }
        }
        if (!found)
            break;
    }
	if (player->getLongestDiagonal2().length <= longestLine)
		player->setLongestDiagonal2(leftDown.x, leftDown.y, rightUp.x, rightUp.y, longestLine);


    return longestLine;
}
