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
        }
            
        screen.Clear();
        
        screen.Display();
    }

    return 0;
}