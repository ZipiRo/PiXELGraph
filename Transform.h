#pragma once

class Transform
{
private:
    float sinTheta, cosTheta;

public:
    Vector2 position;
    Vector2 scale;
    float angle;

    Transform();
    Transform(float x, float y, float scale_x, float scale_y, float angle);

    Vector2 TransformVertex(Vector2 vertex);
    void ThetaUpdate();
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

void Transform::ThetaUpdate()
{
    this->sinTheta = sinf(this->angle);
    this->cosTheta = cosf(this->angle);
}

Vector2 Transform::TransformVertex(Vector2 vertex)
{
    float sx = vertex.x * this->scale.x;
    float sy = vertex.y * this->scale.y;

    float rx = this->cosTheta * sx - this->sinTheta * sy;
    float ry = this->sinTheta * sx + this->cosTheta * sy;

    float tx = rx + this->position.x;
    float ty = ry + this->position.y;

    return Vector2(tx, ty);
}