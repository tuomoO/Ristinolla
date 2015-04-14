#include "MainMenu.h"

using namespace std;
using namespace sf;
using Ite = vector<Button>::iterator;

MainMenu::MainMenu(RenderWindow* window, Input* input, Font* font)
: mWindow(window), mInput(input), mFont(font),
mPlayer1(nullptr), mPlayer2(nullptr), mBoard(nullptr)
{
	mP1Texture = new Texture();
	mP1Texture->loadFromFile("risti.png");
	mP1Texture->setSmooth(false);
	mP2Texture = new Texture();
	mP2Texture->loadFromFile("nolla.png");
	mP2Texture->setSmooth(false);

	switchButtons();
}


MainMenu::~MainMenu()
{
}

bool MainMenu::update()
{
	if (mPlayer1 != nullptr && mPlayer2 != nullptr && mBoard != nullptr)
		return true;

	if (mInput->update())
	{
		Vector2i mousePosition = mInput->getPosition();
		for (Ite i = mButtons.begin(); i != mButtons.end(); i++)
		{
			if ((*i).update(mousePosition.x, mousePosition.y))
			{
				buttonAction((*i).getId());
				break;
			}
		}
	}

	return false;
}

void MainMenu::draw()
{
	for (Ite i = mButtons.begin(); i != mButtons.end(); i++)
	{
		(*i).draw(mWindow);
	}
}

Game* MainMenu::makeGame()
{
	mPlayer1->initialize(mBoard, mPlayer2);
	mPlayer2->initialize(mBoard, mPlayer1);
	mBoard->setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
	return new Game(mBoard, mPlayer1, mPlayer2);
}

void MainMenu::buttonAction(int selection)
{
	switch (selection)
	{
	case 0:
		mPlayer1 = new HumanSystem(mP1Texture, Color::Blue, mInput);
		mPlayer2 = new ComputerSystem(mP2Texture, Color::Red);
		switchButtons();
		break;

	case 1:
		mPlayer1 = new HumanSystem(mP1Texture, Color::Blue, mInput);
		mPlayer2 = new HumanSystem(mP2Texture, Color::Red, mInput);
		switchButtons();
		break;

	case 2:
		mPlayer1 = new ComputerSystem(mP1Texture, Color::Blue);
		mPlayer2 = new ComputerSystem(mP2Texture, Color::Red);
		switchButtons();
		break;

	case 3:
		mBoard = new Board(3, 3, 3, 128, 8);
		switchButtons();
		break;

	case 4:
		mBoard = new Board(8, 8, 5, 64, 4);
		switchButtons();
		break;

	case 5:
		mBoard = new Board(25, 25, 5, 16, 2);
		switchButtons();
		break;

	default:
		break;
	}
}

void MainMenu::switchButtons()
{
	float x = mWindow->getSize().x *0.5f;
	float y = mWindow->getSize().y;

	// game mode
	if (mPlayer1 == nullptr && mPlayer2 == nullptr && mBoard == nullptr)
	{
		mButtons.clear();
		mButtons.push_back(Button(0, mFont, "Singleplayer", x, 0.2f * y));
		mButtons.push_back(Button(1, mFont, "Multiplayer", x, 0.4 * y));
		mButtons.push_back(Button(2, mFont, "Demo mode", x, 0.6 * y));
	}

	// board
	else if (mPlayer1 != nullptr && mPlayer2 != nullptr && mBoard == nullptr)
	{
		mButtons.clear();
		mButtons.push_back(Button(3, mFont, "3x3 - row of 3", x, 0.2f * y));
		mButtons.push_back(Button(4, mFont, "8x8 - row of 5", x, 0.4 * y));
		mButtons.push_back(Button(5, mFont, "50 x 50 - row of 10", x, 0.6 * y));
	}

	// done
	else if (mPlayer1 != nullptr && mPlayer2 != nullptr && mBoard != nullptr)
	{
		mButtons.clear();
	}
}