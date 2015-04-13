#include "HumanSystem.h"
#include "BoardComponent.h"

using namespace std;
using namespace sf;
using ConstIte = vector<GameObject*>::const_iterator;
using Ite = vector<GameObject*>::iterator;

HumanSystem::HumanSystem(Texture* texture, Color color, Input* input)
	: PlayerSystem(texture, color), mInput(input), mButtonWasDown(false)
{
}


HumanSystem::~HumanSystem()
{
}

bool HumanSystem::update()
{
	if (mInput->update())
		return checkClickPos();
	return false;
}

bool HumanSystem::checkClickPos()
{
	Vector2i tilePosition;
	if (findClickedTile(tilePosition))
	{
		vector<GameObject*>* freeTiles = mBoard->getFreeTiles();
		for (Ite i = freeTiles->begin(); i != freeTiles->end(); i++)
		{
			if ((*i)->getComponent<BoardComponent>()->getPosition() == tilePosition)
			{
				addMark(tilePosition);
				return true;
			}
		}
	}
	return false;
}

bool HumanSystem::findClickedTile(Vector2i& tilePosition)
{
	vector<GameObject*>* tiles = mBoard->getTiles();
	for (ConstIte i = tiles->begin(); i != tiles->end(); i++)
	{
		RectangleShape shape = *(*i)->getComponent<RenderComponent>()->getDrawable();
		Vector2i boardCoords = (*i)->getComponent<BoardComponent>()->getPosition();
		shape.setPosition(mBoard->getTilePosition(boardCoords));
		if (shape.getGlobalBounds().contains(mInput->getPositionf()))
		{
			tilePosition = (*i)->getComponent<BoardComponent>()->getPosition();
			return true;
		}
	}
	return false;
}