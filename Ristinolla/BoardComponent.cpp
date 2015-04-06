#include "BoardComponent.h"

using namespace sf;

BoardComponent::BoardComponent(int x, int y)
	: mPosition(x,y)
{

}

BoardComponent::BoardComponent(Vector2i position)
	: mPosition(position)
{

}


BoardComponent::~BoardComponent()
{
}

Vector2i BoardComponent::getPosition()
{
	return mPosition;
}