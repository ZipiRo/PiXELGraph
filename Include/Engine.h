#pragma once

namespace winapi
{
    #include <windows.h>
}

#include "InputSystem.h"
#include "Timer.h"
#include "Screen.h"

Vector2 WindowToCanvasMousePosition(const Vector2 &mousePosition, int fontSize)
{
    return (mousePosition / fontSize) - Vector2(8 - (fontSize / 0.6), 49.5 / fontSize);
}

class Engine
{
protected:
    InputSystem input;

    float FPS = 60;
    float timeScale = 1.0;
    Color screenColor = Color256::White;

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
        if(timer.DeltaTime() >= 1.0 / FPS)
        {
            timer.Reset();
            this->OnUpdate(timer.DeltaTime());
        }

        screen.Clear(screenColor);
        this->OnDraw(screen);
        screen.Display();
    }

    this->OnQuit();
}