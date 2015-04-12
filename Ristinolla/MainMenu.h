#pragma once

#include "Game.h"
#include "Button.h"
#include "ComputerSystem.h"
#include "Input.h"

class MainMenu
{
public:
	MainMenu(sf::RenderWindow* window, Input* input, sf::Font* font);
	~MainMenu();

	bool update();
	void draw();

	Game* makeGame();

private:
	void buttonAction(int selection);
	void switchButtons();

	std::vector<Button> mButtons;
	PlayerSystem* mPlayer1;
	PlayerSystem* mPlayer2;
	sf::Texture* mP1Texture;
	sf::Texture* mP2Texture;
	Board* mBoard;
	sf::Font* mFont;
	sf::RenderWindow* mWindow;
	Input* mInput;
};

