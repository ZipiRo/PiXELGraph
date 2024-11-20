#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>
#include "Color.h"
#include "Screen.h"
#include "Vector2.h"
#include "Transform.h"
#include "Object.h"
#include "Rectangle.h"
#include "Circle.h"

const float PI = 3.141592f;
const int WIDTH = 300;
const int HEIGHT = 200;

// 300x200 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

int main()
{
    Rectangle square1(0, 0, 20, 20, Color::Green);
    Rectangle square2(0, 0, 20, 20, Color::Red);

	int curentKey;
    float angle = 0;
    float radius = 60;
    Vector2 m_Center(WIDTH / 2, HEIGHT / 2);

    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        screen.Clear();

        angle += .1f;
        float x = (cos(angle) * radius / 2) + m_Center.x;
        float y = (sin(angle) * radius) + m_Center.y;

        square1.MoveTo(Vector2(x, y));
        square1.Rotate(0.1f);
        square1.Draw(screen);

        x = (cos(angle) * -radius / 2) + m_Center.x;
        y = (sin(angle) * -radius) + m_Center.y;

        square2.MoveTo(Vector2(x, y));
        square2.Rotate(0.1f);
        square2.Draw(screen);        

        screen.PutPixel(m_Center.x, m_Center.y, Color::Black);
        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}