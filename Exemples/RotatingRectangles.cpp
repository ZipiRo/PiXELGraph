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

const float PI = 3.141592f;
const int WIDTH = 320;
const int HEIGHT = 240;

// 300x200 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

int main()
{
    Object *objects[5];

    objects[0] = new Rectangle(260, 150, 40, 40, Color::Red);
    objects[1] = new Rectangle(49, 59, 25, 40, Color::Green);
    objects[2] = new Rectangle(100, 200, 50, 10, Color::Blue);
    objects[3] = new Rectangle(240, 50, 50, 30, Color::Purple);
    objects[4] = new Rectangle(WIDTH / 2, HEIGHT / 2, 40, 40, Color::Cyan);
    
	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        screen.Clear();

        for(int i = 0; i < 5; i++)
        {  
            objects[i]->Rotate(0.05f);
            objects[i]->Draw(screen);
        }

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}