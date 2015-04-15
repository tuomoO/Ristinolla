#include "MainMenu.h"

using namespace std;
using namespace sf;
using Ite = vector<Button>::iterator;

MainMenu::MainMenu(RenderWindow* window, Input* input, Font* font)
: mWindow(window), mInput(input), mFont(font),
mPlayer1(nullptr), mPlayer2(nullptr), mBoard(nullptr)
{
	mP1Texture = new Texture();
	mP1Texture->loadFromFile("risti64.png");
	mP1Texture->setSmooth(true);
	mP2Texture = new Texture();
	mP2Texture->loadFromFile("nolla64.png");
	mP2Texture->setSmooth(true);

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
		break;

	case 1:
		mPlayer1 = new HumanSystem(mP1Texture, Color::Blue, mInput);
		mPlayer2 = new HumanSystem(mP2Texture, Color::Red, mInput);
		break;

	case 2:
		mPlayer1 = new ComputerSystem(mP1Texture, Color::Blue);
		mPlayer2 = new ComputerSystem(mP2Texture, Color::Red);
		break;

	case 3:
		mBoard = new Board(3, 3, 3, 128, 8);
		break;

	case 4:
		mBoard = new Board(8, 8, 5, 64, 4);
		break;

	case 5:
		mBoard = new Board(12, 12, 6, 50, 3);
		break;

	case 6:
		mBoard = new Board(25, 25, 8, 24, 2);
		break;

	case 7:
		mBoard = new Board(50, 50, 10, 12, 1);
		break;

	default:
		break;
	}
	switchButtons();
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
		mButtons.push_back(Button(3, mFont, "3 x 3 - row of 3", x, 0.15f * y));
		mButtons.push_back(Button(4, mFont, "8 x 8 - row of 5", x, 0.3 * y));
		mButtons.push_back(Button(5, mFont, "12 x 12 - row of 6", x, 0.45 * y));
		mButtons.push_back(Button(6, mFont, "25 x 25 - row of 8", x, 0.6 * y));
		mButtons.push_back(Button(7, mFont, "50 x 50 - row of 10", x, 0.75 * y));
	}

	// done
	else if (mPlayer1 != nullptr && mPlayer2 != nullptr && mBoard != nullptr)
	{
		mButtons.clear();
	}
}