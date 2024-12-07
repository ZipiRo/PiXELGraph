#include "Include/PixelGraph.h"

const int WIDTH = 300;
const int HEIGHT = 200;
const int FPS = 60;

Screen screen(WIDTH, HEIGHT);
Font font("Resources/basic.f2p");
Timer timer;

int main()
{   
    Text fps_Text(1, HEIGHT - 7);
    fps_Text.setFont(font);

    Shape *shape[1000];
    int countS = 50;
    
    Box box;

    int y = 15, x = 0;
    for(int i = 0; i < countS; i++)
    {
        shape[i] = new Rectangle((x++ + 1) * 20, y, 20, 10);
        shape[i]->SetFillColor(Color(i % 16));
        shape[i]->SetPivot({0.5, 0.5});

        if(shape[i]->GetBoundingBox().right > WIDTH - 20)
        { 
            y += 30; 
            x = 0;
        }
    }

    int currentFPS;

    int curentKey;

    float time = 0;
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
            time += timer.DeltaTime();
            timer.Reset();

            if(time >= 1)
            {
                currentFPS = 1 / timer.DeltaTime();
                fps_Text.setString("FPS:" + std::to_string(currentFPS));
                time = 0;
            }

            for(int i = 0; i < countS; i++)
            {
                shape[i]->GetTransform().Rotate((100 + i * 1.f) * DEG_TO_RAD * timer.DeltaTime());
            }

            box = shape[0]->GetBoundingBox();
        }
            
        screen.Clear();

        for(int i = 0; i < countS; i++)
            shape[i]->Draw(screen);
        
        DrawLines(screen, box.vertices, Color::Red);

        fps_Text.Draw(screen);

        screen.Display();
    }

    for(int i = 0; i < countS; i++)
        delete shape[i];

    return 0;
}