#pragma once

#include "TransformComponent.h"

class TransformComponentFactory
{
public:
	TransformComponentFactory();
	~TransformComponentFactory();

	TransformComponent* make(float x = 0.0f, float y = 0.0f);

private:
};