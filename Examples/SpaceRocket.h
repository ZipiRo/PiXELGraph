#include "../Include/PixelGraph.h"

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->FPS = 60;
        this->timeScale = 1;
        this->screenColor = Color256::White;
        this->fontSize = 3;
        this->title = "SpaceRocket";

        Init(400, 225);
    }

    Font font;
    Text fps_text;
    
    Elipse elipse;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        fps_text = Text(1, 1);
        fps_text.setFont(font);
        fps_text.setFontSize(4.5);

        elipse = Elipse(30, 40, 10, 6, 5);
        elipse.SetPivot({0.5, 0.5});
    }

    bool boost = false;

    Color colorCounter = 0;
    float boostTimer = 0;
    float frameTimer = 1;
    float speed = 40;
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
            fps_text.setString("FPS " + std::to_string(int(1 / deltaTime)));
            frameTimer = 0;
        }

        if(input.isKeyDown(Keyboard::Key_Space))
            boost = true;

        // if(input.isKeyDown(Keyboard::Key_A))
        //     elipse.GetTransform().Rotate(-turnSpeed * DEG_TO_RAD * deltaTime);

        // if(input.isKeyDown(Keyboard::Key_D))
        //     elipse.GetTransform().Rotate(turnSpeed * DEG_TO_RAD * deltaTime);
            
        if(input.isKeyDown(Keyboard::Key_W))
            elipse.GetTransform().Move(elipse.GetTransform().right * speed * deltaTime);

        if(input.isKeyDown(Keyboard::Key_S))
            elipse.GetTransform().Move(-elipse.GetTransform().right * speed * deltaTime);

        if(boost)
        {
            speed = 300;
            turnSpeed = 250;
            boostTimer += deltaTime;

            elipse.SetFillColor(colorCounter++ % 255);
            if(boostTimer >= 1)
            {
                speed = 40;
                turnSpeed = 100;
                boost = false;
                boostTimer = 0;

                elipse.SetFillColor(Color256::Transparent);
            }
        }
    }

    void OnDraw(Screen &screen) override
    {
        elipse.Draw(screen);
        fps_text.Draw(screen);

        DrawLine(screen, elipse.GetTransformVertices()[0].x, elipse.GetTransformVertices()[0].y, screenMousePosition.x, screenMousePosition.y, Color256::LightRed);
        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color256::Black);
    }

    void OnQuit() override
    {

    }
};