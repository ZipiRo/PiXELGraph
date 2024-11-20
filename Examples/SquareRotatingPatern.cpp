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

Color::Color colors[20] = {Color::Black, Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan,
	Color::IntenseBlack, Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntensePurple, Color::IntenseCyan};

int main()
{

    Object *object[100];

    int obj_count = 30;

    for(int i = 0; i < obj_count; i++)
        object[i] = new Rectangle(WIDTH / 2.f, HEIGHT / 2.f, obj_count / 5 + 5 * i, obj_count / 5 + 5 * i, colors[i % 14]);

	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        for(int i = 0; i < obj_count; i++)
        { 
            object[i]->Rotate(0.07f * ((1 + i) * 0.05f)); 
        }

        screen.Clear();

        for(int i = 0; i < obj_count; i++)
            object[i]->Draw(screen);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}