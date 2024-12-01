#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <conio.h>
#include <thread>
#include "../Include/PixelGraph.h"

const int WIDTH = 300;
const int HEIGHT = 200;
const float FPS = 9999;

// 450x300 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);
Font font("Resources/pizxel.f2p");
Timer timer;

int main()
{
    Elipse Rocket(0, HEIGHT / 2, 15, 7, 3);
    Rocket.SetPivot({0.5f, 0.5f});
    Rocket.SetOutlineColor(Color::Black);

    Text fps(10, 10);
    fps.setFont(font);
    fps.setColor(Color::Red);

    Vector2 position;
    Vector2 rightDirection;
    Vector2 upDirection;
    float amplitude = 4;
    float angleDirection = 1;

    int currentFPS;

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::SPACE) CLEAR_CONSOLE
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

        timer.Tick();
        if(timer.DeltaTime() >= 1.0f / FPS)
        {
            timer.Reset();
            currentFPS = 1.0 / timer.DeltaTime();

            fps.setString(std::to_string(currentFPS));

            Rocket.Transform().Rotate(angleDirection * 13 * DEG_TO_RAD);
            rightDirection = Rocket.Transform().right;
            upDirection = Rocket.Transform().up;
            Rocket.Transform().Move((rightDirection) * amplitude);
            position = Rocket.Transform().position;
        }

        screen.Clear();
        Rocket.Draw(screen);

        DrawLine(screen, position.x, position.y, (rightDirection.x * amplitude + position.x), (rightDirection.y * amplitude + position.y), Color::Blue);
        DrawLine(screen, position.x, position.y, (upDirection.x * amplitude + position.x), (upDirection.y * amplitude + position.y), Color::Green);

        fps.Draw(screen);

        screen.Display();
    }

    return 0;
}