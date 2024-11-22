#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>
#include "../PixelGraph.h"

const int WIDTH = 300;
const int HEIGHT = 200;

// 300x200 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);


Color::Color colors[20] = {Color::Red, Color::Cyan, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan,
	Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntenseCyan};

int main()
{
    Elipse circle(WIDTH / 2, HEIGHT / 2, .5f, .5f, Color::Blue);

    circle.Rotate(PI / 2);
    circle.Scale({2, 0});
    int i = 0;

	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        // screen.Clear();

        circle.set_Color(colors[i++ % 4]);
        circle.Rotate(PI / 6);
        circle.Scale({0.5f, 1 / 5.f});

        circle.Draw(screen);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}