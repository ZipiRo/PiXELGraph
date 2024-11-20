#pragma once

std::vector<Vector2> CreateRectangleVertices(float width, float height)
{
    std::vector<Vector2> vertices;

        float left = -width / 2.0f;
        float right = left + width;
        float bottom = -height / 2.0f;
        float top = bottom + height;

        vertices.push_back(Vector2(left, top));
        vertices.push_back(Vector2(right, top));
        vertices.push_back(Vector2(right, bottom));
        vertices.push_back(Vector2(left, bottom));

    return vertices;
}

std::vector<Vector2> UpdateVertices(Transform transfrom, const std::vector<Vector2> &vertices)
{
    std::vector<Vector2> T_vertices;

    transfrom.SinCosUpdate();

    for(const Vector2 &vertex : vertices)
        T_vertices.emplace_back(transfrom.TransformVertex(vertex));

    return T_vertices;
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
};

Rectangle::Rectangle(float x, float y, float width, float height, Color::Color color)
{
    this->transform.position = Vector2(x, y);
    this->width = width;
    this->height = height;
    this->color = color;

    this->vertices = CreateRectangleVertices(this->height, this->width);
    this->T_vertices = vertices;
}

void Rectangle::Draw(Screen &screen)
{
    if(UPDATE_VERTICES)
        this->T_vertices = UpdateVertices(this->transform, this->vertices);

    for(auto vertex = T_vertices.begin(); vertex != T_vertices.end(); ++vertex)
	{
		auto next_vertex = std::next(vertex);
		if(next_vertex == T_vertices.end())
			next_vertex = T_vertices.begin(); 
		
		Vector2 vertexA = *vertex;
		Vector2 vertexB = *next_vertex;

		DrawLine(screen, vertexA.x, vertexA.y, vertexB.x, vertexB.y, color);
	}
    
    this->UPDATE_VERTICES = false;
}