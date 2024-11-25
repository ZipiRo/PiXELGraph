#pragma once

std::vector<Vector2> CreateRectangleVertices(float width, float height, float originX, float originY)
{
    std::vector<Vector2> vertices;

    float left = -width * originX;
    float right = left + width;
    float bottom = -height * originY;
    float top = bottom + height;

    vertices.emplace_back(Vector2(left, top));
    vertices.emplace_back(Vector2(right, top));
    vertices.emplace_back(Vector2(right, bottom));
    vertices.emplace_back(Vector2(left, bottom));

    return vertices;
}

class Rectangle : public Shape
{
private:
    float width, height;

public:
    Rectangle() {}
    Rectangle(float x, float y, float width, float height);

    void SetOrigin(Vector2 origin) override;
};

Rectangle::Rectangle(float x, float y, float width, float height)
{
    this->transform.position = Vector2(x, y);
    this->width = width;
    this->height = height;
    this->outlineColor = Color::Transparent;
    this->fillColor = Color::Transparent;

    this->vertices = CreateRectangleVertices(this->height, this->width, 0, 0);

    this->UPDATE = true;
}

void Rectangle::SetOrigin(Vector2 origin)
{
    vertices = CreateRectangleVertices(width, height, origin.x, origin.y);
}