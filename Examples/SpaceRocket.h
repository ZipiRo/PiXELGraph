#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->windowTitle = L"SpaceRocket v1.0";
        this->FPS = 120;
        this->timeScale = 1;
        this->screenColor = Color256::White;
        this->fontSize = 2;

        Init(400, 225);
    }

    Font font;
    Text fps_text;
    
    Elipse elipse;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        fps_text = Text(1, 1);
        fps_text.SetFont(font);
        fps_text.SetFontSize(4.5);

        elipse = Elipse(30, 40, 10, 6, 3);
        elipse.SetFillColor(Color256::Red);
        elipse.SetPivot({0.5, 0.5});
    }

    bool boost = false;

    Color colorCounter = 0;
    float boostTimer = 0;
    float frameTimer = 1;
    float speed = 100;
    float turnSpeed = 100;
    Vector2 mousePosition;
    Vector2 screenMousePosition;

    Vector2 direction;
    float angle;

    void OnUpdate(float deltaTime) override
    {   
        if(input.isKeyDown(Keyboard::Key_Escape))
            running = false;

        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / this->fontSize;
        
        direction = screenMousePosition - elipse.GetTransform().position;
        angle = atan2(direction.y, direction.x);

        elipse.GetTransform().RotateTo(angle);

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            fps_text.SetString("FPS " + std::to_string(int(1 / deltaTime)));
            frameTimer = 0;
        }

        if(input.isKeyDown(Keyboard::Key_W))
            elipse.GetTransform().Move(elipse.GetTransform().right * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_S))
            elipse.GetTransform().Move(-elipse.GetTransform().right * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_A))
            elipse.GetTransform().Move(elipse.GetTransform().up * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_D))
            elipse.GetTransform().Move(-elipse.GetTransform().up * speed * deltaTime);
            
        if(input.isKeyDown(Keyboard::Key_Space))
            boost = true;

        if(boost)
        {
            speed = 200;
            turnSpeed = 150;
            boostTimer += deltaTime;

            if(boostTimer >= 1)
            {
                speed = 100;
                turnSpeed = 100;
                boost = false;
                boostTimer = 0;
            }
        }
    }

    void OnDraw(Screen &screen) override
    {
        elipse.Draw(screen);
        fps_text.Draw(screen);
        
        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color256::Black);
    }

    void OnQuit() override
    {

    }
};