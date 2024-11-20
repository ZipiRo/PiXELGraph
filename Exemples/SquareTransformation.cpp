#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Color.h"
#include "Screen.h"
#include "Vector2.h"
#include "Transform.h"
#include "Object.h"
#include "Rectangle.h"

const float PI = 3.141592f;
const int WIDTH = 320;
const int HEIGHT = 240;

// 300x200 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

int main()
{
    Object *square = new Rectangle(0, HEIGHT / 2, 30, 30, Color::White);
    
	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        square->Rotate(0.4f);
        square->Move(Vector2(10.f, 0));
        square->Scale(Vector2(-0.08f, -0.08f));

        screen.Clear(Color::Black);

        square->Draw(screen);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}