#pragma once

#include "Game.h"

#include "RenderSystem.h"
#include "HumanSystem.h"
#include "WinSystem.h"
#include "ComputerSystem.h"

#include "TransformComponentFactory.h"
#include "RenderComponentFactory.h"
#include "BoardComponentFactory.h"

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
	Text message = Text("Player 1 make your move.", font, 42u);

	//Board board(3, 3, 3, 128, 8);
    Board* board = new Board(7, 7, 4, 64, 4);
    board->setPosition(windowWidth / 2, windowHeight / 2);
	RenderSystem renderSystem(&window, board);

	PlayerSystem* player1;
	PlayerSystem* player2;
	player1 = new HumanSystem("risti.png", Color::Blue, &window);
	player2 = new ComputerSystem("nolla.png", Color::Red);
	player1->initialize(board, player2);
	player2->initialize(board, player1);
	Game game(board, player1, player2);

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

		//update
		if (game.isRunning())
			game.update();
		message.setString(game.getMessage());

		//draw
		game.draw(&renderSystem);
		window.draw(message);
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
    return 0;
}

