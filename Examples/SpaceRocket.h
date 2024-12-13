#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color256::LightYellow; 
        this->windowTitle = L"SpaceRocket v1.0";
        this->timeScale = 1;
        this->FPS = 120;

        Init(640 / 3, 480 / 3, 3);
    }

    Font font;
    Text fps_text;
    
    Shape *player;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        fps_text = Text(1, 1);
        fps_text.SetFont(font);
        fps_text.SetFontSize(4.5);

        player = new Rectangle(30, 40, 10, 6);
        player->SetFillColor(Color256::Red);
        player->SetPivot({0.5, 0.5});
    }

    bool boost = false;
    bool slowmo = false;

    Color colorCounter = 0;
    float boostTimer = 0;
    float frameTimer = 1;
    float speed = 100;
    float turnSpeed = 100;
    Vector2 mousePosition;
    Vector2 screenMousePosition;

    float slowmoTimer = 0;

    Vector2 direction;
    float angle;

    void OnUpdate(float deltaTime) override
    {   
        if(input.isKeyDown(Keyboard::Key_Escape))
            Quit();

        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / FontSize();
        
        direction = screenMousePosition - player->GetTransform().position;
        angle = atan2(direction.y, direction.x);

        player->GetTransform().RotateTo(angle);

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            SetWindowTitle(windowTitle + L" | FPS: " + std::to_wstring(int(1 / deltaTime * timeScale)) + L" fps");
            fps_text.SetString("FPS " + std::to_string(int(1 / deltaTime * timeScale)));
            frameTimer = 0;
        }

        if(input.isKeyDown(Keyboard::Key_W))
            player->GetTransform().Move(player->GetTransform().right * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_S))
            player->GetTransform().Move(-player->GetTransform().right * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_A))
            player->GetTransform().Move(player->GetTransform().up * speed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_D))
            player->GetTransform().Move(-player->GetTransform().up * speed * deltaTime);
        
        if(input.isKeyDown(Keyboard::Key_Q))
        {
            SetTimeScale(0.5);
            player->SetFillColor(Color256::LightBlue);
            slowmo = true;
        }

        if(input.isKeyDown(Keyboard::Key_Space))
            boost = true;

        if(slowmo)
        {
            slowmoTimer += deltaTime;

            if(slowmoTimer >= 2)
            {
                SetTimeScale(1);
                player->SetFillColor(Color256::Red);
                slowmo = false;
                slowmoTimer = 0;
            }
        }

        if(boost)
        {
            speed = 700;
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
        player->Draw(screen);
        fps_text.Draw(screen);
        
        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color256::Black);
    }

    void OnQuit() override
    {
        delete player;
    }
};