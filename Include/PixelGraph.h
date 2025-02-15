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

const int MAX_INT = 2147483647;
const int MIN_INT = -2147483647;

const int MAX_WIDTH = 1920 / 2;
const int MAX_HEIGHT = 1080 / 2;

#include "ConsoleWindow.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "Timer.h"

#include "Vector2.h"
#include "Math.h"
#include "Box.h"
#include "Utils.h"

#include "Font.h"
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
    InputSystem input;
    Event event;


    void Init(int width, int height, int fontSize);
private:
    Color backgroundColor = Color::White;
    std::wstring windowTitle = L"Demo";
    float timeScale = 1.0;
    float FPS = 60;

    EventSystem eventSystem;
    ConsoleWindow window;
    Screen screen;
    Timer timer;

    Box screenBounds;
    int screenWidth;
    int screenHeight;
    int fontSize;
    bool running;
public:
    virtual void OnStart() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw(Screen &screen) = 0;
    virtual void OnQuit() = 0;

    void Run();
    void Quit();

    void SetScreenBackgroundColor(Color color)
    {
        this->backgroundColor = color;
    }

    void SetTimeScale(float timeScale)
    {
        this->timeScale = timeScale > 0 ? timeScale : 0.1;
        this->timer.TimeScale(timeScale);
    }

    void SetWindowTitle(const std::wstring &title) 
    { 
        this->window.SetTitle(title); 
    }
    
    void SetMaxFPS(int maxFPS)
    {
        this->FPS = maxFPS < 1 ? 1 : maxFPS;
    }

    Vector2 ScreenMousePosition(const Vector2 &mousePosition) 
    {
        return Vector2(mousePosition.x / fontSize, mousePosition.y / fontSize);
    }

    float GetFontSize() { return this->fontSize; }
    Box GetScreenBounds() { return this->screenBounds; }
    int GetScreenWidth() { return this->screen.GetWidth(); }
    int GetScreenHeight() { return this->screen.GetHeight(); }
    std::wstring GetWindowTitle() { return this->windowTitle; }

};
 
void PiXELGraph::Init(int width, int height, int fontSize = 2)
{
    this->fontSize = fontSize < 2 ? 2 : fontSize;
    
    width = (width > MAX_WIDTH) ? MAX_WIDTH : width;
    height = (height > MAX_HEIGHT) ? MAX_HEIGHT : height;

    this->window = ConsoleWindow(width, height, this->fontSize, this->fontSize, windowTitle);
    this->screen = Screen(width, height);

    this->screenWidth = this->screen.GetWidth();
    this->screenHeight = this->screen.GetHeight();

    this->screenBounds = Box(0, 0, this->screenWidth - 1, this->screenHeight - 1);

    this->timer = Timer(this->timeScale);
    this->eventSystem = EventSystem(window.GetInputHandle());
    this->input = InputSystem(window.GetHWNDConsole());

    this->running = true;
}

void PiXELGraph::Run()
{
    this->OnStart();

    while (running)
    {
        if(window.IsFocused())
        {
            input.PollInput();
            eventSystem.PoolEvent(event);

            if(input.isKeyPressed(Keyboard::Key_Delete))
                CLEAR_CONSOLE
        }
        
        timer.Tick();
        if(timer.DeltaTime() >= 1.0 / FPS)
        {
            timer.Reset();
            this->OnUpdate(timer.DeltaTime());
        }

        screen.Clear(backgroundColor);
        this->OnDraw(screen);
        screen.Display();
    }

    this->OnQuit();
}

void PiXELGraph::Quit()
{
    this->running = false;
}