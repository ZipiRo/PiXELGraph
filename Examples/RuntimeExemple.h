#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color256::White; 
        this->windowTitle = L"SpaceRocket v1.0";
        this->timeScale = 1;
        this->FPS = 60;

        Init(1240 / 3, 720 / 3, 3);
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