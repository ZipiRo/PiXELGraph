#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>
#include "Include/PixelGraph.h"

const int WIDTH = 450;
const int HEIGHT = 300;

// 450x300 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

int main()
{
    Elipse Rocket(WIDTH / 2, HEIGHT / 2, 15, 7, 3);
    Rocket.SetPivot({0.5f, 0.5f});
    Rocket.SetOutlineColor(Color::White);

    Vector2 position;
    Vector2 rightDirection;
    Vector2 upDirection;
    float amplitude = 5;
    float angleDirection = 1;

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::DELETE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;

        angleDirection = 0;

        if (_kbhit())
			curentKey = _getch();
        if(curentKey == Key::ARROW_RIGHT)
        {
            angleDirection = 1;
        }

        if (_kbhit())
			curentKey = _getch();
        if(curentKey == Key::ARROW_LEFT)
        {
            angleDirection = -1;
        }

        curentKey = 0;

        Rocket.Transform().Rotate(angleDirection * 13 * DEG_TO_RAD);
        rightDirection = Rocket.Transform().right;
        upDirection = Rocket.Transform().up;
        Rocket.Transform().Move((rightDirection) * amplitude);
        position = Rocket.Transform().position;

        screen.Clear(Color::Black);

        Rocket.Draw(screen);

        DrawLine(screen, position.x, position.y, (rightDirection.x * amplitude + position.x), (rightDirection.y * amplitude + position.y), Color::Blue);
        DrawLine(screen, position.x, position.y, (upDirection.x * amplitude + position.x), (upDirection.y * amplitude + position.y), Color::Green);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}