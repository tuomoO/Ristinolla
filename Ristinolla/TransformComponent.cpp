#include "TransformComponent.h"

using namespace sf;

TransformComponent::TransformComponent()
	: mPosition(Vector2f(0, 0))
{
}


TransformComponent::~TransformComponent()
{
}


void TransformComponent::setPosition(Vector2f& position)
{
    mPosition = position;
}


void TransformComponent::setPosition(float x, float y)
{
	mPosition = Vector2f(x, y);
}


void TransformComponent::move(Vector2f& change)
{
    mPosition += change;
}


void TransformComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}


Vector2f& TransformComponent::getPosition()
{
	return mPosition;
}