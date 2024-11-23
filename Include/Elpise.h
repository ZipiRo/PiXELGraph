#pragma once

std::vector<Vector2> CreateElipseVertices(float radiusX, float radiusY, const int point_count)
{
    std::vector<Vector2> vertices;

    float res = (2 * PI) / point_count;
    for(float angle = 0.f; angle <= 2 * PI; angle += res)
    {
        float x = cos(angle) * radiusX;
        float y = sin(angle) * radiusY;

        vertices.emplace_back(Vector2(x, y));
    }

    return vertices;
}

AABB UpdateElipseBoundingBox(const Transform &transform, float radiusX, float radiusY)
{   
    int left = transform.position.x - (radiusX * transform.scale.x);
    int top = transform.position.y - (radiusY * transform.scale.y);
    int right = transform.position.x + (radiusX * transform.scale.x);
    int bottom = transform.position.y + (radiusY * transform.scale.y);

    return AABB(left, top, right, bottom);
}

class Elipse : public Shape  
{
private:
    float radiusX, radiusY;
    int point_count;

public:
    Elipse () {}
    Elipse (float x, float y, float radiusX, float radiusY, const int point_count = 30);

    void Draw(Screen &screen) override;
    AABB GetBoundingBox() override;
};

Elipse::Elipse(float x, float y, float radiusX, float radiusY, const int point_count)
{
    this->transform.position = Vector2(x, y);
    this->radiusX = radiusX;
    this->radiusY = radiusY;
    this->point_count = point_count;
    this->outlineColor = Color::Transparent;
    this->fillColor = Color::Transparent;

    this->vertices = CreateElipseVertices(this->radiusX, this->radiusY, point_count);
    
    this->UPDATE = true;
}

void Elipse::Draw(Screen &screen)
{
    
    if(UPDATE)
    {
        transformedVertices = UpdateVertices(transform, vertices);
        boundingBox = (point_count > 15) ? UpdateElipseBoundingBox(transform, radiusX, radiusY) : UpdateBoundingBox(transformedVertices);
        UPDATE = false;
    }

    if(fillColor != Color::Transparent)
        FillShape(screen, boundingBox, transformedVertices, fillColor);

    if(outlineColor != Color::Transparent) 
        DrawLines(screen, transformedVertices, outlineColor);
}

AABB Elipse::GetBoundingBox()
{
    if(UPDATE)
    {
        transformedVertices = UpdateVertices(transform, vertices);
        boundingBox = (point_count > 15) ? UpdateElipseBoundingBox(transform, radiusX, radiusY) : UpdateBoundingBox(transformedVertices);
        UPDATE = false;
    }

    return boundingBox;
}