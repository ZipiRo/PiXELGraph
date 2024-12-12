#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <list>
#include "nlohmann/json.hpp"

namespace winapi 
{
    #include <windows.h>
}

const float PI = 3.1415926535f;

const int MAX_INT = 2147483647;
const int MIN_INT = -2147483647;

const int MAX_WIDTH = 1000;
const int MAX_HEIGHT = 1000;

#include "ConsoleWindow.h"
#include "InputSystem.h"
#include "Timer.h"

#include "Vector2.h"
#include "Utils.h"

#include "Font.h"
#include "Box.h"
#include "Color.h"
#include "Screen.h"
#include "Transform.h"
#include "Shape.h"
#include "Text.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Elpise.h"

class PiXELGraph
{
protected:
    ConsoleWindow window;
    InputSystem input;

    std::wstring windowTitle = L"Demo";
    float timeScale = 1.0;
    float FPS = 60;
    int fontSize = 2;

    Color screenColor = Color256::White; // MAke a screen function

    bool running; // Quit

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

void PiXELGraph::Init(int width, int height)
{
    this->running = true;

    this->timer = Timer(this->timeScale);
    this->window = ConsoleWindow(width, height, fontSize, fontSize, windowTitle);
    this->screen = Screen(width, height);
}

void PiXELGraph::Run()
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