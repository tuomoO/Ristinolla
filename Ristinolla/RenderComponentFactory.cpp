#include "RenderComponentFactory.h"

using namespace std;
using namespace sf;

RenderComponentFactory::RenderComponentFactory()
: mTexture(nullptr), mTileSize(0)
{

}

RenderComponentFactory::RenderComponentFactory(string path, int tileSize)
: mTileSize(tileSize)
{
	mTexture = new Texture();
	mTexture->loadFromFile(path);
	mTexture->setSmooth(true);
}

RenderComponentFactory::~RenderComponentFactory()
{
	delete mTexture;
}

RenderComponent* RenderComponentFactory::make(float x, float y, bool centerOrigin)
{
	return setShape(x, y, centerOrigin);
}

RenderComponent* RenderComponentFactory::make(float size, bool centerOrigin)
{
	return setShape(size, size, centerOrigin);
}

RenderComponent* RenderComponentFactory::make()
{
	return setShape(mTileSize, mTileSize, true);
}

RenderComponent* RenderComponentFactory::setShape(float x, float y, bool centerOrigin)
{
	RenderComponent* result = new RenderComponent();
	result->mShape = RectangleShape(Vector2f(x, y));
	result->mShape.setPosition(0, 0);
	if (centerOrigin)
		result->mShape.setOrigin(x*0.5f, y*0.5f);
	if (mTexture != nullptr)
		result->mShape.setTexture(mTexture);
	return result;
}