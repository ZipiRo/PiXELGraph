#include "../Include/PixelGraph.h"

class Game : public Engine
{
public:
    Game()
    {
        this->FPS = 60;
        this->timeScale = 1.0;

        Init(300, 200);
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