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

class Rectangle : public Shape
{
private:
    float width, height;

public:
    Rectangle() {}
    Rectangle(float x, float y, float width, float height);
};

Rectangle::Rectangle(float x, float y, float width, float height)
{
    this->transform.position = Vector2(x, y);
    this->width = width;
    this->height = height;
    this->outlineColor = Color::Transparent;
    this->fillColor = Color::Transparent;

    this->vertices = CreateRectangleVertices(this->height, this->width);

    this->UPDATE = true;
}