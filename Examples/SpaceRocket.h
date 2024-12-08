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
    Font font;
    Text fps_text;
    Text mCoord;
    Text rCoord;
    
    Rectangle rec;
    Elipse elipse;

    void OnStart() override
    {
        font = Font("Resources/basic.f2p");
        fps_text = Text(1, 1);
        fps_text.setFont(font);
        fps_text.setFontSize(4.5);

        mCoord = Text(10, 10);
        mCoord.setFont(font);

        rCoord = Text(10, 20);
        rCoord.setFont(font);

        elipse = Elipse(30, 40, 10, 6, 3);
        elipse.SetFillColor(Color::Red);
        elipse.SetPivot({0.5, 0.5});

        rec = Rectangle(0, 0, 4, 4);
        rec.SetFillColor(Color::Red);
        rec.SetPivot({0.5, 0.5});
    }

    bool boost = false;

    int colorCounter = 0;
    float boostTimer = 0;
    float frameTimer = 1;
    float speed = 40;
    float turnSpeed = 100;
    Vector2 mousePosition;
    Vector2 windowMousePosition;

    void OnUpdate(float deltaTime) override
    {   
        mousePosition = Vector2(input.getMousePositionX(), input.getMousePositionY());
        mousePosition /= 10;

        if(input.isKeyUp(Keyboard::Key_Escape))
            running = false;

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            fps_text.setString("FPS " + std::to_string(int(1 / deltaTime * timeScale)));
            frameTimer = 0;
        }

        mCoord.setString("X " + std::to_string(int(mousePosition.x)) + " Y " + std::to_string(int(mousePosition.y)));
        // rCoord.setString("X " + std::to_string(int(mousePosition.x + 10)) + " Y " + std::to_string(int(mousePosition.y + 10)));

        rec.GetTransform().MoveTo(mousePosition);

        if(input.isMouseButtonDown(Mouse::Left))
            rec.SetFillColor(Color::Green);

        if(input.isMouseButtonDown(Mouse::Right))
            rec.SetFillColor(Color::Red);

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

            elipse.SetFillColor(Color(colorCounter++ % 16));
            
            if(boostTimer >= 1)
            {
                speed = 40;
                turnSpeed = 100;
                boost = false;
                boostTimer = 0;

                elipse.SetFillColor(Color::Red);
            }
        }
    }

    void OnDraw(Screen &screen) override
    {
        elipse.Draw(screen);
        rec.Draw(screen);
        fps_text.Draw(screen);
        mCoord.Draw(screen);
        rCoord.Draw(screen);
    }

    void OnQuit() override
    {
        std::ofstream out("data.out");
        out << "x " << mousePosition.x << " y " << mousePosition.y;
        out.close();
    }
};