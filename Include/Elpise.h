#pragma once

std::vector<Vector2> CreateElipseVertices(float radiusX, float radiusY, const int point_count)
{
    std::vector<Vector2> vertices;

    float res = (2 * PI) / point_count;
    for(float angle = 0.f; angle <= 2 * PI; angle += res)
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
    Elipse (float x, float y, float radiusX, float radiusY, Color::Color color, const int point_count = 30);

    void Draw(Screen &screen) override;
    std::vector<Vector2> get_T_vertices() override;
};

Elipse::Elipse(float x, float y, float radiusX, float radiusY, Color::Color color, const int point_count)
{
    this->transform.position = Vector2(x, y);
    this->radiusX = radiusX;
    this->radiusY = radiusY;
    this->color = color;

    this->vertices = CreateElipseVertices(this->radiusX, this->radiusY, point_count);
    
    this->UPDATE_VERTICES = true;
}

void Elipse::Draw(Screen &screen)
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);

    for(auto vertex = T_vertices.begin(); vertex != T_vertices.end(); ++vertex)
	{
		auto next_vertex = std::next(vertex);
		if(next_vertex == T_vertices.end())
			next_vertex = T_vertices.begin(); 
		
		Vector2 vertexA = *vertex;
		Vector2 vertexB = *next_vertex;

		DrawLine(screen, vertexA.x, vertexA.y, vertexB.x, vertexB.y, color);
	}

    UPDATE_VERTICES = false;
}

std::vector<Vector2> Elipse::get_T_vertices()
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);
        
    UPDATE_VERTICES = false;

    return T_vertices;
}