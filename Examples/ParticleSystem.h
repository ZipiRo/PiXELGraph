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
        this->position = Vector2::ZERO;
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
            direction = Vector2::Normalize(direction);
            Particle new_Particle(position, direction, magnitude, Color::White);

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
            
            // particle.color = Color(int(particle.alivetimer * 100) % 256);

            particle.alivetimer += deltaTime;
        }      
    }

    void Draw(Screen &screen)
    {
        for(const Particle &particle : particles)
        {
            screen.PlotPixel(particle.position.x, particle.position.y, particle.color);
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
        this->backgroundColor = Color::Black; 
        this->windowTitle = L"ParticleSystem v1.0";
        this->timeScale = 1;
        this->FPS = 120;

        Init(1240 / 3, 720 / 3, 3);
    }

private:
    Box screenBounds;

    ParticleSystem particleSystem;
    
    Elipse elipse;
    Rectangle cursor;

    void OnStart() override
    {
        elipse = Elipse(0, 0, 3, 3, 2);
        elipse.SetPivot({0.5, 0.5});

        cursor = Rectangle(0, 0, .5, .5);
        cursor.SetFillColor(Color::White);
        cursor.SetOutlineColor(Color::White);

        screenBounds = GetScreenBounds();
        particleSystem = ParticleSystem(123, 5);
    }

    float frameTimer = 1;

    Vector2 mousePosition;
    Vector2 screenMousePosition;

    void OnUpdate(float deltaTime) override
    {   
        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / GetFontSize();

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            SetWindowTitle(windowTitle + L" | FPS: " + std::to_wstring(int (1 / deltaTime)) + L" | DT: " + std::to_wstring(deltaTime) + L" MS");
            frameTimer = 0;
        }

        if(input.isKeyDown(Key_Escape)) Quit();
        if(input.isKeyDown(Key_R)) particleSystem.Reset();

        if(input.isMouseButtonDown(Mouse::Left))
        {
            particleSystem.SetPosition(screenMousePosition);
            particleSystem.RandomDirection();
        }

        cursor.GetTransform().MoveTo(screenMousePosition);

        particleSystem.Update(deltaTime, screenBounds);
    }

    void OnDraw(Screen &screen) override
    {
        particleSystem.Draw(screen);   
        cursor.Draw(screen);
    }

    void OnQuit() override
    {

    }
};