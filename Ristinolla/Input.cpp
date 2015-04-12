#include "Input.h"

using namespace sf;

Input::Input(RenderWindow* window)
: mWindow(window), mButtonWasDown(false)
{
}


Input::~Input()
{
}


bool Input::update()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		mButtonWasDown = true;
	}
	else if (mButtonWasDown)
	{
		mButtonWasDown = false;
		return true;
	}
	return false;
}

Vector2i Input::getPosition()
{
	return Mouse::getPosition(*mWindow);
}

Vector2f Input::getPositionf()
{
	Vector2i temp = getPosition();
	return Vector2f(temp.x, temp.y);
}