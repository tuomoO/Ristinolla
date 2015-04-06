#include "HumanSystem.h"
#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

HumanSystem::HumanSystem(vector<GameObject*>* my, vector<GameObject*>* opponent,
	vector<GameObject*>* tiles, Board* board, RenderComponentFactory* renderFactory, Window* window)
: PlayerSystem(my, opponent, tiles, board, renderFactory), mWindow(window), mButtonWasDown(false)
{
}


HumanSystem::~HumanSystem()
{
}

bool HumanSystem::update()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		mButtonWasDown = true;
	}
	else if (mButtonWasDown)
	{
		mButtonWasDown = false;
		return checkClickPos();
	}
	return false;
}

bool HumanSystem::checkClickPos()
{
	Vector2i tilePosition;
	if (findClickedTile(tilePosition))
	{
		// checking if the tile is empty
		for (Ite i = mMyMarks->begin(); i != mMyMarks->end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				return false;
		}
		for (ConstIte i = mOpponentMarks->begin(); i != mOpponentMarks->end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				return false;
		}

		addMark(tilePosition);
		return true;
	}
	return false;
}

Vector2f HumanSystem::getMousePos()
{
	Vector2i temp = Mouse::getPosition(*mWindow);
	return Vector2f(temp.x, temp.y);
}

bool HumanSystem::findClickedTile(Vector2i& tilePosition)
{
	for (ConstIte i = mTiles->begin(); i != mTiles->end(); i++)
	{
		RectangleShape shape = *(*i)->getComponent<RenderComponent>()->getDrawable();
		Vector2i boardCoords = (*i)->getComponent<BoardComponent>()->getPosition();
		shape.setPosition(mBoard->getTilePosition(boardCoords));
		if (shape.getGlobalBounds().contains(getMousePos()))
		{
			tilePosition = (*i)->getComponent<BoardComponent>()->getPosition();
			return true;
		}
	}
	return false;
}

void HumanSystem::addMark(Vector2i tilePosition)
{
	BoardComponentFactory boardFactory;
	GameObject* obj = new GameObject();
	obj->add(mRenderFactory->make());
	obj->add(boardFactory.make(tilePosition));
	mMyMarks->push_back(obj);
	mLastMove = obj;
}