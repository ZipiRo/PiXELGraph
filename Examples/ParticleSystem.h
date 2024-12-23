#include "../Include/PixelGraph.h"

class Particle
{
public:
    Vector2 position;
    Vector2 direction;
    float magnitude;
    Color256 color;
    float alivetimer;
    
    Particle () {}
    Particle (Vector2 position, Vector2 direction, float magnitude, Color256 color)
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
    Vector2 position;
    
    int particleCount;
    float aliveTime;

public:    
    std::list<Particle> particles;

    ParticleSystem () {}
    ParticleSystem (Vector2 position, int count, float aliveTime)
    {
        this->position = position;
        this->particleCount = count;
        this->aliveTime = aliveTime;
    }

    void Radial(float magnitude)
    {
        float angle_it = (2 * PI) / particleCount;

        for(float angle = 0; angle < 2 * PI; angle += angle_it)
        {
            Vector2 direction(cos(angle), sin(angle));
            Particle new_Particle(position, direction, magnitude, Color256(int(angle)));

            this->particles.emplace_back(new_Particle);
        }
    }

    void Update(float deltaTime, Box screenBounds)
    {  
        // for(auto particle_it = particles.begin(); particle_it != particles.end(); ++particle_it)
        // {
        //     Particle particle = *particle_it;

        //     if
        //     (
        //         particle.alivetimer > 5.0 ||
        //         particle.position.x > screenBounds.right || 
        //         particle.position.x < screenBounds.left ||
        //         particle.position.y > screenBounds.bottom || 
        //         particle.position.y < screenBounds.top
        //     )
        //     {
        //         particles.remove(*particle_it);
        //     }
        // }

        for(Particle &particle : this->particles)
        {
            Vector2 direction = particle.direction;
            float magnitude = particle.magnitude;

            particle.position += direction * magnitude * deltaTime; 
            
            particle.color = Color256(int(particle.alivetimer * 100) % 256);

            particle.alivetimer += deltaTime;
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
        this->backgroundColor = Color256::Black; 
        this->windowTitle = L"ParticleSystem v1.0";
        this->timeScale = 1;
        this->FPS = 120;

        Init(1920 / 5, 1080 / 5, 5);
    }

private:
    Box screenBounds;

    ParticleSystem s1;
    
    Elipse elipse;

    void OnStart() override
    {
        elipse = Elipse(0, 0, 3, 3);
        elipse.SetPivot({0.5, 0.5});

        screenBounds = GetScreenBounds();
        s1 = ParticleSystem(ZERO, 20, 5);
    }

    float frameTimer = 1;

    Vector2 mousePosition;
    Vector2 screenMousePosition;

    void OnUpdate(float deltaTime) override
    {   
        mousePosition = Vector2(input.GetMousePositionX(), input.GetMousePositionY());
        screenMousePosition = mousePosition / FontSize();

        frameTimer += deltaTime;
        if(frameTimer >= 1)
        {
            SetWindowTitle(windowTitle + L" | FPS: " + std::to_wstring(int (1 / deltaTime)) + L" | DT: " + std::to_wstring(deltaTime) + L" MS");
            frameTimer = 0;
        }


        if(input.isKeyDown(Key_Escape)) Quit();
        if(input.isKeyDown(Key_R)) s1.Reset();

        if(input.isMouseButtonDown(Mouse::Right))
        {
            s1.SetPosition(screenMousePosition);
            s1.Radial(10);
        }

        s1.Update(deltaTime, screenBounds);
    }

    void OnDraw(Screen &screen) override
    {
        for(const Particle &particle : s1.particles)
        {
            screen.PlotPixel(particle.position.x, particle.position.y, particle.color);
            // elipse.SetFillColor(particle.color);
            // elipse.SetOutlineColor(particle.color);
            // elipse.GetTransform().MoveTo(particle.position);
            // elipse.GetTransform().RotateTo(atan2(particle.direction.y, particle.direction.x));
            // elipse.Draw(screen);
        }       
    }

    void OnQuit() override
    {

    }
};