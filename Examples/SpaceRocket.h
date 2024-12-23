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

    struct Particle
    {
        Vector2 position;
        Vector2 direction;
        float magnitude;
        Color color;
        float alive;
    };

    Box screenBounds;
    Font font;
    Text T_FPS;
    Text T_ParticleCount;
    
    Shape *player;

    Elipse elipse;

    std::list<Particle> particles;

    void OnStart() override
    {
        screenBounds = GetScreenBounds();

        elipse = Elipse(0, 0, 5, 3, 3);
        elipse.SetPivot({0.5, 0.5});

        font = Font("Resources/basic.f2p");
        T_FPS = Text(1, 1);
        T_FPS.SetFont(font);
        T_FPS.SetFontSize(4.5);

        T_ParticleCount = Text(1, screenBounds.bottom - 5);
        T_ParticleCount.SetFont(font);
        T_ParticleCount.SetFontSize(4.5);

        player = new Elipse(30, 40, 10, 6, 3);
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
    float rocketTurnSpeed = 100;
    float rocketSpeed = 100;

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

        T_ParticleCount.SetString(std::to_string(particles.size()));

        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / FontSize();

        if(input.isKeyDown(Keyboard::Key_W))
            player->GetTransform().Move(player->GetTransform().right * rocketSpeed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_S))
            player->GetTransform().Move(-player->GetTransform().right * rocketSpeed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_A))
            player->GetTransform().Move(player->GetTransform().up * rocketSpeed * deltaTime);
        if(input.isKeyDown(Keyboard::Key_D))
            player->GetTransform().Move(-player->GetTransform().up * rocketSpeed * deltaTime);

        if(input.isMouseButtonDown(Mouse::Right))
        {
            Particle new_Particle {player->GetTransform().position + player->GetTransform().right * 10, 
                                player->GetTransform().right, 50, 
                                Color256(colorCounter++ % 256)};
            
            particles.push_back(new_Particle);
        }

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
        
        for(Particle &particle : particles)
        {
            particle.alive += deltaTime;

            Vector2 direction = particle.direction;
            float magnitude = particle.magnitude;

            particle.position += direction * magnitude * deltaTime; 
        }

        for(auto particle_it = particles.begin(); particle_it != particles.end(); ++particle_it)
        {
            Particle particle = *particle_it;

            if(particle.position.x > screenBounds.right || 
                particle.position.x < screenBounds.left ||
                particle.position.y > screenBounds.bottom || 
                particle.position.y < screenBounds.top ||
                particle.alive > 5.0)
            {
                particles.erase(particle_it);
            }
        }

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
            rocketSpeed = 200;
            rocketTurnSpeed = 150;
            boostTimer += deltaTime;

            if(boostTimer >= 1)
            {
                rocketSpeed = 100;
                rocketTurnSpeed = 100;
                boost = false;
                boostTimer = 0;
            }
        }
    }

    void OnDraw(Screen &screen) override
    {
        player->Draw(screen);
        T_FPS.Draw(screen);
        T_ParticleCount.Draw(screen);

        for(const Particle &particle : particles)
        {
            // screen.PlotPixel(particle.position.x, particle.position.y, particle.color);
            elipse.GetTransform().RotateTo(atan2(particle.direction.y, particle.direction.x));
            elipse.SetFillColor(particle.color);
            elipse.SetOutlineColor(particle.color);
            elipse.GetTransform().MoveTo(particle.position);
            elipse.Draw(screen);
        }

        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color256::Black);
    }

    void OnQuit() override
    {
        delete player;
    }
};