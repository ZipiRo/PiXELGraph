#pragma once

class Transform
{
private:
    float sin0 = 0.f, cos0 = 1.f;

public:
    Vector2 position;
    Vector2 scale;
    float angle;

    Transform();
    Transform(float x, float y, float scale_x, float scale_y, float angle);

    Vector2 TransformVertex(Vector2 vertex);
    Vector2 SinCosUpdate();
};

Transform::Transform()
{
    this->position = Zero;
    this->scale = Vector2(1.f, 1.f);
    this->angle = 0;
}

Transform::Transform(float x, float y, float scale_x, float scale_y, float angle)
{
    this->position = Vector2(x, y);
    this->scale = Vector2(scale_x, scale_y);
    this->angle = angle;
}

Vector2 Transform::SinCosUpdate()
{
    this->sin0 = sin(this->angle);
    this->cos0 = cos(this->angle);

    return {cos0, sin0};
}

Vector2 Transform::TransformVertex(Vector2 vertex)
{
    float sx = vertex.x * this->scale.x;
    float sy = vertex.y * this->scale.y;

    float rx = this->cos0 * sx - this->sin0 * sy;
    float ry = this->sin0 * sx + this->cos0 * sy;

    float tx = rx + this->position.x;
    float ty = ry + this->position.y;

    return {tx, ty};
}