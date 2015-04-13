#pragma once

#include "Game.h"
#include "MainMenu.h"

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
	Text message = Text("Player 1 make your move.", font, 32u);

	RenderSystem renderSystem(&window);
	Input input(&window);
	Button resetButton(1, &font, "Quit to main menu", window.getSize().x - 128, 32);
	MainMenu* menu = new MainMenu(&window, &input, &font);
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

		//update
		if (game != nullptr)
		{
			if (game->isRunning())
				game->update();
			else
			{
				if (input.update() && resetButton.update(input.getPosition()))
				{
					delete menu;
					delete game;
					game = nullptr;
					menu = new MainMenu(&window, &input, &font);
				}
			}
		}
		else if (menu->update())
		{
			game = menu->makeGame();
			renderSystem.setBoard(game->getBoard());
		}
		
		//draw
		if (game != nullptr)
		{

			message.setString(game->getMessage());
			game->draw(&renderSystem);
			window.draw(message);

            if (!game->isRunning())
            {
                message.setString(game->getMessage());
                window.draw(message);
                resetButton.draw(&window);
            }
				
		}
		else
			menu->draw();

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
	delete menu;
    return 0;
}

