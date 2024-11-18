#pragma once

class Object
{
protected:
    Transform transform;
    float width, height;

    Color::Color color;

    bool UPDATE_VERTICES = true;
         
public:
    Object();

    virtual void Draw(Screen &screen) = 0;

    void Rotate(float amount);
    void RotateTo(float angle);
    void Move(Vector2 amount);
    void MoveTo(Vector2 position);
    void Scale(Vector2 amount);
    void ScaleTo(Vector2 scale);
};

Object::Object()
{
    this->width = 0;
    this->height = 0;
}

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
