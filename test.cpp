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

int main()
{
    Font font("pizxel.f2p");

    Text text(10, 60);
    text.setFont(font);
    text.setString("BUNA ACESTA ESTE O FONTUL PE CARE L-AM CREAT EU\nESTE ANUL 30:11:2024");
    text.setColor(Color::Red);

    Text text2(10, 105);
    text2.setFont(font);
    text2.setString("abcdefghijklmnopqrstuvwxyz");
    text2.setColor(Color::Black);

    
    Text text3(10, 140);
    text3.setFont(font);
    text3.setString("0123456789-+:");
    text3.setColor(Color::Blue);

    AABB textBoundingBox;
    
    int i = 0;

    float fontSizeC = 5;
    int fontWeight = 1;

    bool rotate = false;
    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::SPACE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;
        if (curentKey == Key::ENTER) rotate = !rotate;

        if(curentKey == '-') fontSizeC--;
        if(curentKey == '=') fontSizeC++;
        if(curentKey == '_') fontWeight--;
        if(curentKey == '+') fontWeight++;

        text.setFontSize(fontSizeC);
        text.setFontWeight(fontWeight);
        text2.setFontSize(fontSizeC);
        text2.setFontWeight(fontWeight);
        text3.setFontSize(fontSizeC);
        text3.setFontWeight(fontWeight);

        curentKey = 0;
        if(rotate)
        {
            text.Transform().Rotate(5 * DEG_TO_RAD);
            text2.Transform().Rotate(5 * DEG_TO_RAD);
            text3.Transform().Rotate(5 * DEG_TO_RAD);
        }

        screen.Clear();
        text.Draw(screen);
        text2.Draw(screen);
        text3.Draw(screen);
        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}