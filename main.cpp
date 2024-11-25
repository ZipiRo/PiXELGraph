#include <iostream>
#include <fstream>
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

    Rectangle Square(WIDTH / 2, HEIGHT / 2, 15, 15);
    Square.SetOrigin({0.5f, 0.5f});
    Square.SetOutlineColor(Color::Black);

    Vector2 position;
    Vector2 rightDirection;
    Vector2 upDirection;
    float amplitude = 5;

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::DELETE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;

        curentKey = 0;

        Square.Rotate(10 * DEG_TO_RAD);
        rightDirection = Square.GetTransform().right;
        upDirection = Square.GetTransform().up;
        Square.Move((rightDirection + upDirection) * amplitude);
        position = Square.GetTransform().position;


        screen.Clear();

        Square.Draw(screen);

        DrawLine(screen, position.x, position.y, (rightDirection.x * amplitude * 5 + position.x), (rightDirection.y * amplitude * 5 + position.y), Color::Red);
        DrawLine(screen, position.x, position.y, (upDirection.x * amplitude * 5 + position.x), (upDirection.y * amplitude * 5 + position.y), Color::Green);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}