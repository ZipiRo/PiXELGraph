#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color::Black; 
        this->windowTitle = L"Demo";
        this->timeScale = 1;
        this->FPS = 60;
    }

private:
    void OnStart() override
    {
        // Start Things
    }

    void OnUpdate(float deltaTime) override
    {   
        // Update Things
    }

    void OnDraw(Screen &screen) override
    {
        // Draw Things
    }

    void OnQuit() override
    {
        // DestroyThings
    }
};