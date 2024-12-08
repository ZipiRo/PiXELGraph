#pragma once

class Polygon : public Shape
{
public:
    Polygon() {}
    Polygon(const std::vector<Vector2> &vertices, float x, float y);
};

Polygon::Polygon(const std::vector<Vector2> &vertices, float x, float y)
{
    this->transform.position = Vector2(x, y);
    this->outlineThickness = 1;
    this->outlineColor = outlineColor;
    this->outlineColor = Color255::Black;
    this->fillColor = Color255::Transparent;

    this->vertices = vertices;

    this->transform.update = true;
}