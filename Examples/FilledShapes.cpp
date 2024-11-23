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

const int WIDTH = 300;
const int HEIGHT = 200;

// 450x300 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90, 300x200
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

Color::Color colors[20] = {Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan,  
	                    Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntensePurple, Color::IntenseCyan, Color::White, Color::IntenseWhite, Color::IntenseBlack, Color::Black, };

int main()
{
    std::list<Shape *> shapelist; 

    int radius = 20;
    int x = radius + 10,  y = radius + 10;
    for(int i = 3; i <= 9; i++)
    {   

        Elipse* polygon = new Elipse(x, y, radius, radius, i);
        polygon->SetOutlineColor(Color::Black);
        polygon->SetFillColor(colors[i - 3 % 12]);

        x += radius * 2 + 20;
        if(polygon->GetBoundingBox().right > WIDTH) {
            x = radius + 10; 
            y += radius * 2 + 20;
        }

        shapelist.emplace_back(polygon);
    }

    x = radius + 10;
    y += radius * 2 + 20;
    Elipse* elipse = new Elipse(x, y, radius / 2, radius);
    elipse->SetOutlineColor(Color::Black);
    elipse->SetFillColor(Color::Cyan);

    shapelist.emplace_back(elipse);

    x += radius * 2 + 10;
    elipse = new Elipse(x, y, radius, radius);
    elipse->SetOutlineColor(Color::Black);
    elipse->SetFillColor(Color::IntensePurple);

    shapelist.emplace_back(elipse);

    x += radius * 2 + 10;
    Rectangle* rectangle = new Rectangle(x, y, radius * 2, radius);
    rectangle->SetOutlineColor(Color::Black);
    rectangle->SetFillColor(Color::Red);

    shapelist.emplace_back(rectangle);

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;  

        for(Shape* shape : shapelist)
        {
            shape->Rotate(5 * DEG_TO_RAD);
        }

        screen.Clear();
        for(Shape* shape : shapelist)
            shape->Draw(screen);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}