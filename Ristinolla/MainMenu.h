#pragma once

#include "Game.h"
#include "Button.h"
#include "ComputerSystem.h"

class MainMenu
{
public:
	MainMenu(sf::RenderWindow* window, sf::Font* font);
	~MainMenu();

	bool update();
	void draw();

	Game* makeGame();

private:
	void buttonAction(int selection);
	void switchButtons();

	bool mMouseButtonWasDown;
	std::vector<Button> mButtons;
	PlayerSystem* mPlayer1;
	PlayerSystem* mPlayer2;
	Board* mBoard;
	sf::Font* mFont;
	sf::RenderWindow* mWindow;
};

