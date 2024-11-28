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
    Font font("pizxel.f2p");

    Text text(150, 60);
    text.setFont(font);
    text.setString("FUCK");
    text.setColor(Color::Red);
    text.setFontSize(25);
    text.setFontWeight(2);

    Text text2(150, 105);
    text2.setFont(font);
    text2.setString("XXX");
    text2.setColor(Color::Black);
    text2.setFontSize(25);
    text2.setFontWeight(2);
    
    Text text3(150, 145);
    text3.setFont(font);
    text3.setString("LOOL");
    text3.setColor(Color::Blue);
    text3.setFontSize(25);
    text3.setFontWeight(2);

    AABB textBoundingBox;
    
    int i = 0;
    bool rotate = false;
    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == Key::SPACE) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false;
        if (curentKey == Key::ENTER) rotate = true;
        // text.setColor(colors[i++ % 14]);

        curentKey = 0;
        if(rotate)
        {
            text.Transform().Rotate(5 * DEG_TO_RAD);
            text2.Transform().Rotate(5 * DEG_TO_RAD);
            text3.Transform().Rotate(5 * DEG_TO_RAD);
        }
        // textBoundingBox = text.GetBoundingBox();

        screen.Clear();
        text.Draw(screen);
        text2.Draw(screen);
        text3.Draw(screen);
        // DrawLines(screen, textBoundingBox.box, Color::Black);
        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}