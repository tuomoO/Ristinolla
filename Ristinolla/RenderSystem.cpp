#include "RenderSystem.h"

using namespace sf;
using namespace std;
using GoIt = vector<GameObject*>::iterator;

RenderSystem::RenderSystem(RenderWindow* window, Board* board)
:mWindow(window), mBoard(board)
{
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::draw(GameObject* gameObject)
{
	RenderComponent* render = gameObject->getComponent<RenderComponent>();
	if (render != nullptr)
	{
		RectangleShape shape = *render->getDrawable();

		TransformComponent* transform = gameObject->getComponent<TransformComponent>();
		if (transform != nullptr)
		{
			shape.setPosition(transform->getPosition());
		}
		else
		{
			BoardComponent* boardComp = gameObject->getComponent<BoardComponent>();
			if (boardComp != nullptr && mBoard != nullptr)
			{
				Vector2i boardPos = boardComp->getPosition();
				shape.setPosition(mBoard->getTilePosition(boardPos.x, boardPos.y));
			}
		}

		mWindow->draw(shape);
	}
}


void RenderSystem::draw(PlayerSystem* player)
{
	vector<GameObject*>* marks = player->getMarks();
	for (GoIt i = marks->begin(); i != marks->end(); i++)
		draw(*i);
}


void RenderSystem::draw(Board* board)
{
	vector<GameObject*>* marks = board->getTiles();
	for (GoIt i = marks->begin(); i != marks->end(); i++)
		draw(*i);
}


void RenderSystem::swapBuffers()
{
	mWindow->display();
}
