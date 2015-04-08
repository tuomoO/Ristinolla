#include "PlayerSystem.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;

PlayerSystem::PlayerSystem(string texturePath, Color color)
	: mLastMove(nullptr)
{
	mRenderFactory = new RenderComponentFactory(texturePath, color);
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
