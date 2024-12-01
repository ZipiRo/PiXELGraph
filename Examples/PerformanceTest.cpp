#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <conio.h>
#include <thread>
#include "Include/PixelGraph.h"

const int WIDTH = 450;
const int HEIGHT = 300;
const int FPS = 60;

// 450x300 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);
Timer timer;

Font font("Resources/pizxel.f2p");

int main()
{
    Elipse square(WIDTH / 2, HEIGHT / 2, 20, 20, 7);
    square.SetFillColor(Color::Red);
    square.SetOutlineThickness(1);
    square.SetPivot({0.5, 0.5});

    Text drawtime_text(10, 10);
    drawtime_text.setFont(font);
    drawtime_text.Transform().ScaleTo({6, 6});

    Text fps_text(10, 20);
    fps_text.setFont(font);
    fps_text.Transform().ScaleTo({6, 6});
    
    int currentFPS;

    int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
            curentKey = _getch();

        if (curentKey == Key::SPACE) CLEAR_CONSOLE
        if (curentKey == Key::ESCAPE) running = false;

        curentKey = 0;  

        timer.Tick();
        if(timer.DeltaTime() >= 1.0 / FPS)
        {
            timer.Reset();

            currentFPS = (1.0f / timer.DeltaTime());

            fps_text.setString("FPS:" + std::to_string(currentFPS));
            drawtime_text.setString("DTIME:" + std::to_string(timer.DeltaTime()) + "MS");

            square.Transform().Rotate(5 * DEG_TO_RAD);
        }
            
        screen.Clear();
        square.Draw(screen);
        fps_text.Draw(screen);
        drawtime_text.Draw(screen);
        screen.Display();
    }

    return 0;
}