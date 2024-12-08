#include "../Include/PixelGraph.h"

class Game : public Engine
{
public:
    Game()
    {
        this->FPS = 60;
        this->timeScale = 1;
        this->screenColor = Color255::White;

        Init(450, 300);
    }

private:
    Font font;
    Text fps_text;
    
    Elipse elipse;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        fps_text = Text(1, 1);
        fps_text.setFont(font);
        fps_text.setFontSize(4.5);

        elipse = Elipse(30, 40, 10, 6, 3);
        elipse.SetPivot({0.5, 0.5});
    }

    bool boost = false;

    Color colorCounter = 0;
    float boostTimer = 0;
    float frameTimer = 1;
    float speed = 40;
    float turnSpeed = 100;
    Vector2 mousePosition;
    Vector2 worldMousePosition;

    void OnUpdate(float deltaTime) override
    {   
        if(input.isKeyDown(Keyboard::Key_Escape))
            running = false;

        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            fps_text.setString("FPS " + std::to_string(int(1 / deltaTime * timeScale)));
            frameTimer = 0;
        }

        if(input.isKeyDown(Keyboard::Key_Space))
            boost = true;

        if(input.isKeyDown(Keyboard::Key_A))
            elipse.GetTransform().Rotate(-turnSpeed * DEG_TO_RAD * deltaTime);

        if(input.isKeyDown(Keyboard::Key_D))
            elipse.GetTransform().Rotate(turnSpeed * DEG_TO_RAD * deltaTime);
            
        if(input.isKeyDown(Keyboard::Key_W))
            elipse.GetTransform().Move(elipse.GetTransform().right * speed * deltaTime);

        if(input.isKeyDown(Keyboard::Key_S))
            elipse.GetTransform().Move(-elipse.GetTransform().right * speed * deltaTime);

        if(boost)
        {
            speed = 200;
            turnSpeed = 150;
            boostTimer += deltaTime;

            elipse.SetFillColor(colorCounter++ % 255);
            if(boostTimer >= 1)
            {
                speed = 40;
                turnSpeed = 100;
                boost = false;
                boostTimer = 0;

                elipse.SetFillColor(Color255::Transparent);
            }
        }
    }

    void OnDraw(Screen &screen) override
    {
        elipse.Draw(screen);
        fps_text.Draw(screen);

        // DrawLine(screen, 0, 0, mousePosition.x, mousePosition.y, Color255::Green);
    }

    void OnQuit() override
    {

    }
};