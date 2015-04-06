#include "BoardComponentFactory.h"

using namespace std;
using namespace sf;

BoardComponentFactory::BoardComponentFactory()
{
}


BoardComponentFactory::~BoardComponentFactory()
{
}

BoardComponent* BoardComponentFactory::make(int x, int y)
{
	return new BoardComponent(x,y);
}

BoardComponent* BoardComponentFactory::make(Vector2i position)
{
	return new BoardComponent(position.x, position.y);
}
