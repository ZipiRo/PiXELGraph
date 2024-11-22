#pragma once

class Polygon : public Object
{
private:
    std::vector<Vector2> vertices;
    std::vector<Vector2> T_vertices;

public:
    Polygon() {}
    Polygon(const std::vector<Vector2> &vertices, float x, float y, Color::Color);

    void Draw(Screen &screen) override;
    std::vector<Vector2> get_T_vertices() override;
};

Polygon::Polygon(const std::vector<Vector2> &vertices, float x, float y, Color::Color)
{
    this->transform.position = Vector2(x, y);
    this->color = color;

    this->vertices = vertices;

    this->UPDATE_VERTICES = true;
}

void Polygon::Draw(Screen &screen)
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

std::vector<Vector2> Polygon::get_T_vertices()
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);
        
    UPDATE_VERTICES = false;

    return T_vertices;
}