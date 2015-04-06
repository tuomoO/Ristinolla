#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>


class TransformComponent : public Component
{
	friend class TransformComponentFactory;
public:
    TransformComponent();
    ~TransformComponent();

    void setPosition(sf::Vector2f& position);
	void setPosition(float x, float y);
	void move(sf::Vector2f& change);
	void move(float x, float y);

	sf::Vector2f& getPosition();

private:
    sf::Vector2f mPosition;
};




