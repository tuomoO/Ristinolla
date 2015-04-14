#include "PlayerSystem.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;
using Ite = vector<GameObject*>::iterator;

PlayerSystem::PlayerSystem(Texture* texture, Color color)
	: mLastMove(nullptr)
{
	mRenderFactory = new RenderComponentFactory(texture, color);
}


PlayerSystem::~PlayerSystem()
{
	for (vector<GameObject*>::iterator i = mMyMarks.begin(); i != mMyMarks.end(); i++)
		delete *i;
	mMyMarks.clear();
	delete mRenderFactory;
}

void PlayerSystem::initialize(Board* board, PlayerSystem* opponent)
{
	mOpponent = opponent;
	mBoard = board;
	verticalLine.length = 0;
	verticalLine.dir = Vertical;
	horizontalLine.length = 0;
	horizontalLine.dir = Horizontal;
    diagonalLine1.length = 0;
	diagonalLine1.dir = Diagonal1;
    diagonalLine2.length = 0;
	diagonalLine2.dir = Diagonal2;

	mInitialized = true;
}

void PlayerSystem::addMark(Vector2i tilePosition)
{
	if (mMyMarks.size() == 0)
		initializeLongestLines(tilePosition);

    BoardComponentFactory boardFactory;
    GameObject* obj = new GameObject();
    obj->add(mRenderFactory->make(mBoard->getTileSize()));
    obj->add(boardFactory.make(tilePosition));
    mMyMarks.push_back(obj);
    mBoard->markTile(tilePosition);
    mLastMove = obj;
}

void PlayerSystem::initializeLongestLines(Vector2i position)
{
	int x = position.x;
	int y = position.y;
	verticalLine.x1 = x;
	verticalLine.x2 = x;
	verticalLine.y1 = y;
	verticalLine.y2 = y;
	verticalLine.length = 1;

	horizontalLine.x1 = x;
	horizontalLine.x2 = x;
	horizontalLine.y1 = y;
	horizontalLine.y2 = y;
	horizontalLine.length = 1;

	diagonalLine1.x1 = x;
	diagonalLine1.x2 = x;
	diagonalLine1.y1 = y;
	diagonalLine1.y2 = y;
	diagonalLine1.length = 1;

	diagonalLine2.x1 = x;
	diagonalLine2.x2 = x;
	diagonalLine2.y1 = y;
	diagonalLine2.y2 = y;
	diagonalLine2.length = 1;

}

LongestLine* PlayerSystem::getBestLine()
{
	LongestLine* result = &verticalLine;
    if (horizontalLine.length >= result->length)
        result = &horizontalLine;
    if (diagonalLine1.length >= result->length)
        result = &diagonalLine1;
    if (diagonalLine2.length >= result->length)
        result = &diagonalLine2;

    return result;
}

void PlayerSystem::setLongestVertical(int x1, int y1, int x2, int y2, int length)
{
	verticalLine.x1 = x1;
	verticalLine.y1 = y1;
	verticalLine.x2 = x2;
	verticalLine.y2 = y2;
	verticalLine.length = length;
}

void PlayerSystem::setLongestHorizontal(int x1, int y1, int x2, int y2, int length)
{
	horizontalLine.x1 = x1;
	horizontalLine.y1 = y1;
	horizontalLine.x2 = x2;
	horizontalLine.y2 = y2;
	horizontalLine.length = length;
}

bool PlayerSystem::isTileMine(Vector2i position)
{
	for (Ite i = mMyMarks.begin(); i != mMyMarks.end(); i++)
	{
		if ((*i)->getComponent<BoardComponent>()->getPosition() == position)
			return true;
	}
	return false;
}

bool PlayerSystem::isTileOpponents(Vector2i position)
{
	vector<GameObject*>* marks = mOpponent->getMarks();
	for (Ite i = marks->begin(); i != marks->end(); i++)
	{
		if ((*i)->getComponent<BoardComponent>()->getPosition() == position)
			return true;
	}
	return false;
}

void PlayerSystem::highlightLine()
{
    //todo marks in between
    LongestLine* best = getBestLine();
    mBoard->removeTile(best->x1, best->y1);
    mBoard->removeTile(best->x2, best->y2);
}