#include "../Include/PixelGraph.h"

class Particle
{
public:
    Vector2 position;
    Vector2 direction;
    float magnitude;
    Color color;
    float alivetimer;
    
    Particle () {}
    Particle (Vector2 position, Vector2 direction, float magnitude, Color color)
    {
        this->position = position;
        this->direction = direction;
        this->magnitude = magnitude;
        this->color = color;
        this->alivetimer = 0;
    }
};

class ParticleSystem
{
private:
    std::list<Particle> particles;
    Vector2 position;
    
    int particleCount;
    float aliveTime;

public:    

    ParticleSystem () {}
    ParticleSystem (int count, float aliveTime)
    {
        this->position = ZERO;
        this->particleCount = count;
        this->aliveTime = aliveTime;
    }

    void Radial(float magnitude)
    {
        float angle_it = (2 * PI) / particleCount;

        for(float angle = 0; angle < 2 * PI; angle += angle_it)
        {
            Vector2 direction(cos(angle), sin(angle));
            Particle new_Particle(position, direction, magnitude, Color::Blue);

            this->particles.emplace_back(new_Particle);
        }
    }

    void RandomDirection()
    {
        srand(time(NULL));

        for(int i = 0; i < particleCount; i++)
        {
            int neg = rand() % 2;
            float x = float(1 + rand() % (100 - 1 + 1)) / 100.0f * (!neg ? -1 : 1);
            neg = rand() % 2;
            float y = float(1 + rand() % (100 - 1 + 1)) / 100.0f * (!neg ? -1 : 1);

            float magnitude = 1 + rand() % (100 - 1 + 1);

            Vector2 direction = Vector2(x, y);
            direction = Normalize(direction);
            Particle new_Particle(position, direction, magnitude, Color::Blue);

            this->particles.emplace_back(new_Particle);
        }
    }

    void Update(float deltaTime, Box screenBounds)
    {  
        for (auto particle_it = particles.begin(); particle_it != particles.end();)
        {
            Particle& particle = *particle_it;

            if (particle.alivetimer > aliveTime ||
                particle.position.x > screenBounds.right || 
                particle.position.x < screenBounds.left ||
                particle.position.y > screenBounds.bottom || 
                particle.position.y < screenBounds.top)
            {
                particle_it = particles.erase(particle_it);
            }
            else
            {
                ++particle_it;
            }
        }


        for(Particle &particle : this->particles)
        {
            Vector2 direction = particle.direction;
            float magnitude = particle.magnitude;

            particle.position += direction * magnitude * deltaTime; 
            
            // particle.color = COLOR(int(particle.alivetimer * 100) % 256);

            particle.alivetimer += deltaTime;
        }      
    }

    void Draw(Screen &screen)
    {
        Elipse elipse = Elipse(0, 0, 3, 3, 12);
        for(const Particle &particle : particles)
        {
            screen.PlotPixel(particle.position.x, particle.position.y, particle.color);
            // elipse.GetTransform().RotateTo(atan2(particle.direction.y, particle.direction.x));
            // elipse.GetTransform().MoveTo(particle.position);
            // elipse.SetFillColor(particle.color);
            // elipse.SetOutlineColor(particle.color);
            // elipse.Draw(screen);
        }
    }

    void Reset()
    {
        this->particles.clear();
    }

    void SetPosition(Vector2 position)
    {
        this->position = position;
    }
};

class Game : public PiXELGraph
{
public:
    Game()
    {
        this->backgroundColor = Color::White; 
        this->windowTitle = L"SpaceRocket v1.0";
        this->timeScale = 1;
        this->FPS = 99999;

        Init(1240 / 3, 720 / 3 , 3);
    }

    struct Projectile
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

    std::list<Projectile> bullets;
    int aliveTime = 2;

    ParticleSystem particleSystem;

    void OnStart() override
    {
        screenBounds = GetScreenBounds();

        elipse = Elipse(0, 0, 5, 3);
        elipse.SetPivot({0.5, 0.5});

        particleSystem = ParticleSystem(50, .4);

        font = Font("Resources/basic.f2p");
        T_FPS = Text(1, 1);
        T_FPS.SetFont(font);
        T_FPS.SetFontSize(4.5);

        T_ParticleCount = Text(1, screenBounds.bottom - 5);
        T_ParticleCount.SetFont(font);
        T_ParticleCount.SetFontSize(4.5);

        player = new Elipse(30, 40, 10, 6, 3);
        player->SetFillColor(Color::Red);
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

    int colorCounter = 0;

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

        T_ParticleCount.SetString(std::to_string(bullets.size()));

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

        if(input.isMouseButtonDown(Mouse::Left))
        {
            Projectile new_Particle {player->GetTransform().position + player->GetTransform().right * 10, 
                                player->GetTransform().right, 50, 
                                Color::Red};
            
            bullets.push_back(new_Particle);
        }

        if(input.isKeyDown(Keyboard::Key_Q))
        {
            SetTimeScale(0.5);
            player->SetFillColor(Color::LightBlue);
            slowmo = true;
        }

        if(input.isKeyDown(Keyboard::Key_Space))
            boost = true;
        
        direction = screenMousePosition - player->GetTransform().position;
        angle = atan2(direction.y, direction.x);

        player->GetTransform().RotateTo(angle);
        
        for(Projectile &particle : bullets)
        {
            particle.alive += deltaTime;

            Vector2 direction = particle.direction;
            float magnitude = particle.magnitude;

            particle.position += direction * magnitude * deltaTime; 
        }

        for(auto bullet_it = bullets.begin(); bullet_it != bullets.end();)
        {
            Projectile& particle = *bullet_it;

            if (particle.position.x > screenBounds.right - 5 ||
                particle.position.x < screenBounds.left + 5 ||
                particle.position.y > screenBounds.bottom - 5|| 
                particle.position.y < screenBounds.top + 5 ||
                particle.alive > aliveTime)
            {
                particleSystem.SetPosition(particle.position);
                particleSystem.RandomDirection();

                bullet_it = bullets.erase(bullet_it);
            }
            else
            {
                ++bullet_it;
            }
        }

        particleSystem.Update(deltaTime, screenBounds);

        if(slowmo)
        {
            slowmoTimer += deltaTime;

            if(slowmoTimer >= 2)
            {
                SetTimeScale(1);
                player->SetFillColor(Color::Red);
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

        for(const Projectile &particle : bullets)
        {
            // screen.PlotPixel(particle.position.x, particle.position.y, particle.color);
            elipse.GetTransform().RotateTo(atan2(particle.direction.y, particle.direction.x));
            elipse.SetFillColor(particle.color);
            elipse.SetOutlineColor(particle.color);
            elipse.GetTransform().MoveTo(particle.position);
            elipse.Draw(screen);
        }

        particleSystem.Draw(screen);

        screen.PlotPixel(screenMousePosition.x, screenMousePosition.y, Color::Black);
    }

    void OnQuit() override
    {
        delete player;
    }
};