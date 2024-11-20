#pragma once

std::vector<Vector2> CreateRectangleVertices(float width, float height)
{
    std::vector<Vector2> vertices;

        float left = -width / 2.0f;
        float right = left + width;
        float bottom = -height / 2.0f;
        float top = bottom + height;

        vertices.emplace_back(Vector2(left, top));
        vertices.emplace_back(Vector2(right, top));
        vertices.emplace_back(Vector2(right, bottom));
        vertices.emplace_back(Vector2(left, bottom));

    return vertices;
}

class Rectangle : public Object
{
private:
    float width, height;
    std::vector<Vector2> vertices;
    std::vector<Vector2> T_vertices;

public:
    Rectangle() {}
    Rectangle(float x, float y, float width, float height, Color::Color color);

    void Draw(Screen &screen) override;
    std::vector<Vector2> get_T_vertices() override;
};

Rectangle::Rectangle(float x, float y, float width, float height, Color::Color color)
{
    this->transform.position = Vector2(x, y);
    this->width = width;
    this->height = height;
    this->color = color;

    this->vertices = CreateRectangleVertices(this->height, this->width);
    this->T_vertices = vertices;

    this->UPDATE_VERTICES = true;
}

void Rectangle::Draw(Screen &screen)
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

std::vector<Vector2> Rectangle::get_T_vertices()
{
    if(UPDATE_VERTICES)
        T_vertices = UpdateVertices(transform, vertices);
        
    UPDATE_VERTICES = false;

    return T_vertices;
}