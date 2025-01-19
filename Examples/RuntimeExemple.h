#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color::White; 
        this->windowTitle = L"SpaceRocket v1.0";
        this->timeScale = 1;
        this->FPS = 60;

        Init(1920 / 2, 1080 / 2, 2);
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