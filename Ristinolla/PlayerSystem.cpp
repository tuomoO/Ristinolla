#include "PlayerSystem.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;

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
	horizontalLine.length = 0;

	mInitialized = true;
}

void PlayerSystem::addMark(Vector2i tilePosition)
{
    BoardComponentFactory boardFactory;
    GameObject* obj = new GameObject();
    obj->add(mRenderFactory->make(mBoard->getTileSize()));
    obj->add(boardFactory.make(tilePosition));
    mMyMarks.push_back(obj);
    mLastMove = obj;
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