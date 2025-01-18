#pragma once

float Length(Vector2 &vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Distance(Vector2 a, Vector2 b) 
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);
}

Vector2 Normalize(Vector2 &vector)
{
    float length = Length(vector);
    vector.x /= length;
    vector.y /= length;
    
    return vector;
}

float DotProduct(Vector2 a, Vector2 b) 
{
    return a.x * b.x + a.y * b.y;
}

float CrossProduct(Vector2 a, Vector2 b) 
{
    return a.x * b.y - a.y * b.x;
}