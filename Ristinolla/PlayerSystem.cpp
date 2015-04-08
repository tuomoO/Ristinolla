#include "PlayerSystem.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;

PlayerSystem::PlayerSystem(vector<GameObject*>* my, vector<GameObject*>* opponent,
	vector<GameObject*>* tiles, Board* board, RenderComponentFactory* renderFactory)
	: mMyMarks(my), mOpponentMarks(opponent), mTiles(tiles), mBoard(board), mRenderFactory(renderFactory), mLastMove(nullptr)
{
}


PlayerSystem::~PlayerSystem()
{
	delete mRenderFactory;
	for (vector<GameObject*>::iterator i = mMyMarks->begin(); i != mMyMarks->end(); i++)
		delete *i;
	mMyMarks->clear();
}

void PlayerSystem::addMark(Vector2i tilePosition)
{
    BoardComponentFactory boardFactory;
    GameObject* obj = new GameObject();
    obj->add(mRenderFactory->make());
    obj->add(boardFactory.make(tilePosition));
    mMyMarks->push_back(obj);
    mLastMove = obj;
}
