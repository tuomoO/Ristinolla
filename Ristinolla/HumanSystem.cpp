#include "HumanSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

HumanSystem::HumanSystem(string texturePath, Color color, Window* window)
	: PlayerSystem(texturePath, color), mWindow(window), mButtonWasDown(false)
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
		for (Ite i = mMyMarks.begin(); i != mMyMarks.end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				return false;
		}
		vector<GameObject*>* opponentsMarks = mOpponent->getMarks();
		for (ConstIte i = opponentsMarks->begin(); i != opponentsMarks->end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
				return false;
		}

		addMark(tilePosition);
		mBoard->markTile(tilePosition);
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
	vector<GameObject*>* tiles = mBoard->getTiles();
	for (ConstIte i = tiles->begin(); i != tiles->end(); i++)
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