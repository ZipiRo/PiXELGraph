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

    Text text(10, 10);
    text.setFont(font);
    text.setString("THE QUIK BROWN FOX\nJUMPS OVER THE LAZY DOG");
    text.setColor(Color::White);

    Text text2(10, text.GetBoundingBox().bottom + 10);
    text2.setFont(font);
    text2.setString("the quik brown fox\njumps over the lazy dog");
    text2.setColor(Color::White);

    Text text3(10, text2.GetBoundingBox().bottom + 10);
    text3.setFont(font);
    text3.setString("1234567890");
    text3.setColor(Color::White);

    Text text4(10, text3.GetBoundingBox().bottom + 10);
    text4.setFont(font);
    text4.setString("-=+[]()<>:?!.,;\"*%#|_\'/\\");
    text4.setColor(Color::White);

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

        if(curentKey == '-') 
        {
            fontSizeC--;
            text.setFontSize(fontSizeC);
            text2.setFontSize(fontSizeC);
            text3.setFontSize(fontSizeC);
            text4.setFontSize(fontSizeC);
            text2.Transform().MoveTo(Vector2(10, text.GetBoundingBox().bottom + 10));
            text3.Transform().MoveTo(Vector2(10, text2.GetBoundingBox().bottom + 10));
            text4.Transform().MoveTo(Vector2(10, text3.GetBoundingBox().bottom + 10));
        }
        if(curentKey == '=') 
        {
            fontSizeC++;
            text.setFontSize(fontSizeC);
            text2.setFontSize(fontSizeC);
            text3.setFontSize(fontSizeC);
            text4.setFontSize(fontSizeC);
            text2.Transform().MoveTo(Vector2(10, text.GetBoundingBox().bottom + 10));
            text3.Transform().MoveTo(Vector2(10, text2.GetBoundingBox().bottom + 10));
            text4.Transform().MoveTo(Vector2(10, text3.GetBoundingBox().bottom + 10));
        }
        if(curentKey == '_') 
        {
            fontWeight--;
            text.setFontWeight(fontWeight);
            text2.setFontWeight(fontWeight);
            text3.setFontWeight(fontWeight);
            text4.setFontWeight(fontWeight);
        }
        if(curentKey == '+') 
        {
            fontWeight++;
            text.setFontWeight(fontWeight);
            text2.setFontWeight(fontWeight);
            text3.setFontWeight(fontWeight);
            text4.setFontWeight(fontWeight);
        }


        curentKey = 0;
        if(rotate)
        {
            text.Transform().Rotate(5 * DEG_TO_RAD);
            text2.Transform().Rotate(5 * DEG_TO_RAD);
            text3.Transform().Rotate(5 * DEG_TO_RAD);
            text4.Transform().Rotate(5 * DEG_TO_RAD);
        }

        screen.Clear(Color::Black);
        text.Draw(screen);
        text2.Draw(screen);
        text3.Draw(screen);
        text4.Draw(screen);
        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}