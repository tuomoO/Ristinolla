#include "Button.h"

using namespace std;
using namespace sf;

Button::Button(int id, Font* font, std::string text, float x, float y)
	: mId(id)
{
	mShape.setSize(Vector2f(256, 64));
	mShape.setOrigin(128, 32);
	mText.setFont(*font);
	mText.setColor(Color::Black);
	mText.setOrigin(128, 32);
	mShape.setPosition(x, y);
	mText.setPosition(x, y);
	mText.setString(text);
}


Button::~Button()
{
}

bool Button::update(int x, int y)
{
	return mShape.getGlobalBounds().contains(Vector2f(x, y));
}

bool Button::update(Vector2i position)
{
	return update(position.x, position.y);
}

void Button::draw(RenderWindow* window)
{
	window->draw(mShape);
	window->draw(mText);
}
