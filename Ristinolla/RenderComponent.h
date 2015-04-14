#pragma once

#include "TransformComponent.h"

#include <SFML/Graphics.hpp>

#include <string>

class RenderComponent : public Component
{
	friend class RenderComponentFactory;

public:
	~RenderComponent();
    void update(float dt);

	sf::RectangleShape* getDrawable();
    void setColor(sf::Color color);

private:
	RenderComponent();

    sf::RectangleShape mShape;
	sf::Texture* mTexture;
};
