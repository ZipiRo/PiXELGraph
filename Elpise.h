std::vector<Vector2> CreateElipseVertices(float radiusX, float radiusY)
{
    std::vector<Vector2> vertices;

    for(float angle = 0.01f; angle < 2 * 3.141592f; angle += 0.01f)
    {
        float x = cos(angle) * radiusX;
        float y = sin(angle) * radiusY;

        vertices.emplace_back(Vector2(x, y));
    }

    return vertices;
}

class Elipse : public Object  
{
private:
    float radiusX, radiusY;
    std::vector<Vector2> vertices;
    std::vector<Vector2> T_vertices;

public:
    Elipse () {}
    Elipse (float x, float y, float radiusX, float radiusY, Color::Color color);

    void Draw(Screen &screen) override;
    std::vector<Vector2> get_T_vertices() override;
};

Elipse::Elipse(float x, float y, float radiusX, float radiusY, Color::Color color)
{
    this->transform.position = Vector2(x, y);
    this->radiusX = radiusX;
    this->radiusY = radiusY;
    this->color = color;

    this->vertices = CreateElipseVertices(this->radiusX, this->radiusY);
    this->T_vertices = vertices;

    this->UPDATE_VERTICES = true;
}

void Elipse::Draw(Screen &screen)
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);

    for(auto vertex : T_vertices)
        screen.PutPixel(vertex.x, vertex.y, color);

    UPDATE_VERTICES = false;
}

std::vector<Vector2> Elipse::get_T_vertices()
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);
        
    UPDATE_VERTICES = false;

    return T_vertices;
}