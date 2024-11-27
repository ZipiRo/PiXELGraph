#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <map>
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

Color::Color colors[20] = {Color::Black, Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan,
	Color::IntenseBlack, Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntensePurple, Color::IntenseCyan};


int i = 0;
int main()
{
    Text text(40, HEIGHT / 2);
    text.setFont("pixel.font");
    text.setString("FUCK");
    text.setColor(Color::Blue);
    text.setFontSize(10);
    text.setFontWeight(2);

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::SPACE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;

        text.setColor(colors[i++ % 14]);

        curentKey = 0;

        screen.Clear();
        text.Draw(screen);
        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}