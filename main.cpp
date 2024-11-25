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
    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::DELETE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;

        curentKey = 0;

        screen.Clear();

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}