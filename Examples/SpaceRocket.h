#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color256::LightYellow; 
        this->windowTitle = L"SpaceRocket v1.0";
        this->timeScale = 1;
        this->FPS = 60;

        Init(640 / 3, 480 / 3, 3);
    }

    Font font;
    Text T_FPS;
    
    Shape *player;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        T_FPS = Text(1, 1);
        T_FPS.SetFont(font);
        T_FPS.SetFontSize(4.5);

        player = new Rectangle(30, 40, 10, 6);
        player->SetFillColor(Color256::Red);
        player->SetPivot({0.5, 0.5});
    }

    bool boost = false;
    bool slowmo = false; 

    float frameTimer = 1;
    float slowmoTimer = 0;
    float boostTimer = 0;

    Vector2 mousePosition;
    Vector2 screenMousePosition;
    Vector2 direction;

    float angle;
    float turnSpeed = 100;
    float speed = 100;

    Color colorCounter = 0;

    void OnUpdate(float deltaTime) override
    {   
        if(input.isKeyDown(Keyboard::Key_Escape))
            Quit();

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            SetWindowTitle(windowTitle + L" | FPS: " + std::to_wstring(int (1 / deltaTime)) + L" | DT: " + std::to_wstring(deltaTime) + L" MS");
            T_FPS.SetString("FPS " + std::to_string(int(1 / deltaTime)));
            frameTimer = 0;
        }

        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / FontSize();

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
        
        direction = screenMousePosition - player->GetTransform().position;
        angle = atan2(direction.y, direction.x);

        player->GetTransform().RotateTo(angle);

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
        player->Draw(screen);
        T_FPS.Draw(screen);
        
        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color256::Black);
    }

    void OnQuit() override
    {
        delete player;
    }
};