#pragma once

#include "Game.h"

#include "RenderSystem.h"
#include "HumanSystem.h"
#include "WinSystem.h"
#include "ComputerSystem.h"
#include "MainMenu.h"

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
	const int windowHeight = 800;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Ristinolla", Style::Close);

	Font font;
	font.loadFromFile("arial.ttf");
	Text message = Text("Player 1 make your move.", font, 36u);

	RenderSystem renderSystem(&window);
	MainMenu menu(&window, &font);
	Game* game = nullptr;

	//time
	LARGE_INTEGER startTime, endTime, frequency, milliSeconds;
	float fpsTimer = 0;
	float dt = 1.0f / 60;
	int fps = 60;

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

		if (game != nullptr)
		{
			//update
			if (game->isRunning())
				game->update();
			message.setString(game->getMessage());

			//draw
			game->draw(&renderSystem);
			window.draw(message);
		}
		else
		{
			if (menu.update())
			{
				game = menu.makeGame();
				renderSystem.setBoard(game->getBoard());
			}
			menu.draw();
		}
		
		renderSystem.swapBuffers();

		//time
		QueryPerformanceCounter(&endTime);
		milliSeconds.QuadPart = endTime.QuadPart - startTime.QuadPart;
		milliSeconds.QuadPart *= 1000;
		dt = milliSeconds.QuadPart / static_cast<float>(frequency.QuadPart);
		
		fpsTimer += dt;
		if (fpsTimer > 100)
		{
			fps = static_cast<int>(0.8f * fps + 0.2f * ((1.0f / dt) * 1000));
			stringstream framesStream;
			framesStream << setfill('0') << setw(4) << fps;

			window.setTitle("Ristinolla (fps: " + framesStream.str() + ")");
			fpsTimer = 0;
		}
    }
    return 0;
}

