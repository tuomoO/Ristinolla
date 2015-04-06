#include "TransformComponentFactory.h"

using namespace sf;

TransformComponentFactory::TransformComponentFactory()
{

}

TransformComponentFactory::~TransformComponentFactory()
{

}

TransformComponent* TransformComponentFactory::make(float x, float y)
{
	TransformComponent* result = new TransformComponent();
	result->mPosition = Vector2f(x, y);
	return result;
}