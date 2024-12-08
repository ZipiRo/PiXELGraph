#pragma once

namespace WindowsApi
{
    #include <windows.h>
}

#include "InputSystem.h"
#include "Timer.h"
#include "Screen.h"

class Engine
{
protected:
    InputSystem input;

    float FPS = 60;
    float timeScale = 1.0;

    bool running;

    void Init(int width, int height);
private:
    Screen screen;
    Timer timer;

public:
    virtual void OnStart() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw(Screen &screen) = 0;
    virtual void OnQuit() = 0;

    void Run();
};

void Engine::Init(int width, int height)
{
    this->running = true;

    this->screen = Screen(width, height);
    this->timer = Timer(this->timeScale);
}

void Engine::Run()
{
    this->OnStart();

    while (running)
    {
        input.PollInput();

        if(input.isKeyPressed(Keyboard::Key_Delete))
            CLEAR_CONSOLE

        timer.Tick();
        if(timer.DeltaTime() >= 1 / FPS)
        {
            timer.Reset();
            this->OnUpdate(timer.DeltaTime());
        }

        screen.Clear();
        this->OnDraw(screen);
        screen.Display();
    }

    this->OnQuit();
}