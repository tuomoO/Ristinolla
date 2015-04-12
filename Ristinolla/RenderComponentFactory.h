#pragma once

#include "RenderComponent.h"

#include <vector>

class RenderComponentFactory
{
public:
	RenderComponentFactory();
	RenderComponentFactory(sf::Texture* texture, sf::Color color);
	~RenderComponentFactory();

	RenderComponent* make(float x, float y, bool centerOrigin = true);
	RenderComponent* make(float size, bool centerOrigin = true);
	RenderComponent* make();

private:
	RenderComponent* setShape(float x, float y, bool centerOrigin);

	sf::Texture* mTexture;
	sf::Color mColor;
};