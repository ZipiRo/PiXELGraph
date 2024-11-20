#pragma once

class Object
{
protected:
    Transform transform;

    Color::Color color;

    bool UPDATE_VERTICES;
         
public:
    Object() {}

    virtual void Draw(Screen &screen) = 0;
    virtual std::vector<Vector2> get_T_vertices() = 0;

    void Rotate(float amount);
    void RotateTo(float angle);
    void Move(Vector2 amount);
    void MoveTo(Vector2 position);
    void Scale(Vector2 amount);
    void ScaleTo(Vector2 scale);
    void set_Color(Color::Color color);
};

void Object::ScaleTo(Vector2 scale)
{
    this->transform.scale = scale;
    UPDATE_VERTICES = true;
}

void Object::Scale(Vector2 amount)
{
    this->transform.scale += amount;
    UPDATE_VERTICES = true;
}

void Object::Rotate(float amount)
{
    this->transform.angle += amount;
    UPDATE_VERTICES = true;
}

void Object::RotateTo(float angle)
{
    this->transform.angle = angle;
    UPDATE_VERTICES = true;
}

void Object::Move(Vector2 amount)
{
    this->transform.position += amount;
    UPDATE_VERTICES = true;
}

void Object::MoveTo(Vector2 position)
{
    this->transform.position = position;
    UPDATE_VERTICES = true;
}

void Object::set_Color(Color::Color color)
{
    this->color = color;
}

std::vector<Vector2> UpdateVertices(Transform transfrom, const std::vector<Vector2> &vertices)
{
    std::vector<Vector2> T_vertices;

    transfrom.SinCosUpdate();

    for(const Vector2 &vertex : vertices)
        T_vertices.emplace_back(transfrom.TransformVertex(vertex));

    return T_vertices;
}