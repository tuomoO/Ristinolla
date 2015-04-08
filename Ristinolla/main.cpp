#pragma once

#include "GameObject.h"
#include "RenderSystem.h"
#include "HumanSystem.h"
#include "ComputerSystem.h"
#include "TransformComponentFactory.h"
#include "RenderComponentFactory.h"
#include "BoardComponentFactory.h"
#include "Board.h"
#include "WinSystem.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include <time.h>


using namespace std;
using namespace sf;
using GoIt = vector<GameObject*>::iterator;

int main()
{
    srand(time(NULL));

	const int windowWidth = 800;
	const int windowHeight = 640;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Ristinolla", Style::Close);
	window.setFramerateLimit(60u);
	Font font;
	font.loadFromFile("arial.ttf");
	Text playerInfo = Text("Player 1 make your move.", font, 36u);
	Text mouseInfo = Text("cursor info", font, 28u);
	mouseInfo.setPosition(0, 64);

	//ristinolla
	//Board board(3, 3, 3, 128, 8);
    Board board(5, 5, 3, 64, 4);
    board.setPosition(128, 128);
	RenderSystem renderSystem = RenderSystem(&window, &board);
	RenderComponentFactory tileRenderFactory;
	TransformComponentFactory transformFactory;
	BoardComponentFactory boardCompFactory;

	vector<GameObject*> tiles;
	Vector2i boardSize = board.getSize();
	for (int i = 0; i < boardSize.y; i++)
	{
		for (int j = 0; j < boardSize.x; j++)
		{
			int x = j;
			int y = i;

			GameObject* obj = new GameObject();
			obj->add(boardCompFactory.make(x, y));
			obj->add(tileRenderFactory.make(board.getTileSize()));
			tiles.push_back(obj);
		}
	}

	vector<GameObject*> player1Marks;
	vector<GameObject*> player2Marks;
	HumanSystem* player1 = new HumanSystem(&player1Marks, &player2Marks, &tiles, &board,
		new RenderComponentFactory("risti.png", board.getTileSize()), &window);
	/* HumanSystem* player2 = new HumanSystem(&player2Marks, &player1Marks, &tiles, &board,
		new RenderComponentFactory("nolla.png", board.getTileSize()), &window);*/

    ComputerSystem* player2 = new ComputerSystem(&player2Marks, &player1Marks, &tiles, &board,
        new RenderComponentFactory("nolla.png", board.getTileSize()));
	PlayerSystem* currentPlayer = player1;
	WinSystem winSystem(&board);

	int currentTurn = 1;
	bool gameOver = false;

	//time
	LARGE_INTEGER startTime, endTime, frequency, milliSeconds;
	float dt = 1.0f / 60;

    while (window.isOpen())
    {
		//time
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

		// game loop
		if (!gameOver)
		{
			// update player systems
			if (currentPlayer->update())
			{
				// end of turn, update win system
				if (winSystem.update(currentTurn, currentPlayer))
				{
					//game ends
					playerInfo.setString(winSystem.getMessage());
					gameOver = true;
				}
				else
				{
					string infoString = "Player ";
					if (currentPlayer == player1)
					{
						currentPlayer = player2;
						infoString.append("2");
					}
					else
					{
						currentPlayer = player1;
						infoString.append("1");
					}
					
					infoString.append(currentPlayer->getMessage());
					playerInfo.setString(infoString);
				}
                currentTurn++;
			}
		}
		
		// draw tiles
		for (GoIt i = tiles.begin(); i != tiles.end(); i++)
			renderSystem.draw(*i);

		// draw player marks
		for (GoIt i = player1Marks.begin(); i != player1Marks.end(); i++)
			renderSystem.draw(*i);
		for (GoIt i = player2Marks.begin(); i != player2Marks.end(); i++)
			renderSystem.draw(*i);

		// text
		stringstream mouseStream;
		mouseStream << "Mouse: (" << Mouse::getPosition(window).x << ", " << Mouse::getPosition(window).y << ")";
		if (Mouse::isButtonPressed(Mouse::Left))
			mouseStream << " *click*";
		mouseInfo.setString(mouseStream.str());

		window.draw(playerInfo);
		window.draw(mouseInfo);

		// end draw
		renderSystem.swapBuffers();

		//time
		QueryPerformanceCounter(&endTime);
		milliSeconds.QuadPart = endTime.QuadPart - startTime.QuadPart;
		milliSeconds.QuadPart *= 1000;
		dt = milliSeconds.QuadPart / static_cast<float>(frequency.QuadPart);
		stringstream framesStream;
		framesStream.precision(4);
		framesStream << setfill('0') << setw(6) << (1.0f / dt) * 1000;
		window.setTitle("FPS: " + framesStream.str());
    }

	delete player1;
	delete player2;
	for (GoIt i = tiles.begin(); i != tiles.end(); i++)
		delete *i;

    return 0;
}

