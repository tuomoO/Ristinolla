#include "RenderComponent.h"

using namespace sf;

RenderComponent::RenderComponent()
{
	mShape = RectangleShape();
	mTexture = nullptr;
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(float dt)
{
}

RectangleShape* RenderComponent::getDrawable()
{
	return &mShape;
}