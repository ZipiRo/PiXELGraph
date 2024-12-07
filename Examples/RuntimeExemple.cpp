#include "Include/PixelGraph.h"

const int WIDTH = 300;
const int HEIGHT = 200;
const int FPS = 60;

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