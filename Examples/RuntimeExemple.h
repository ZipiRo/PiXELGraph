#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        Init(700, 700, 3);
    }

private:
    Elipse e;

    void OnStart() override
    {
        e = Elipse(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, 10);
        e.SetFillColor(Color(123, 43, 164));
        e.SetPivot(Vector2(0.5, 0.5));
        e.SetOutlineThickness(3);
    }

    void OnUpdate(float deltaTime) override
    {   
        e.GetTransform().Scale(Vector2(.3, .3));
    }

    void OnDraw(Screen &screen) override
    {
        e.Draw(screen);
    }

    void OnQuit() override
    {
        // DestroyThings
    }
};