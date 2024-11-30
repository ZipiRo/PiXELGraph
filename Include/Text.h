void CreateTextVertices(const std::string &string, std::vector<Vector2> &vertices, std::vector<unsigned int> &indices, Font &font)
{
    vertices.clear();
    indices.clear();

    int offset = 0;
    float advance = 0;
    float devance = 0;
    float letterCount = 0;
    float lines = 0;


    for(int i = 0; string[i]; i++)
    {
        if(string[i] == ' ') 
        {
            letterCount++;
            continue;
        }
        else if(string[i] == '\n')
        {
            advance = 0;
            letterCount = 0;
            lines += 1.5;
            continue;
        }

        Glyph glyph = font.Get(string[i]);

        devance = glyph.devance;

        for(Vector2 &vertex : glyph.vertices)
        {
            vertices.emplace_back(vertex + Vector2(((0.25 + advance) - devance) * letterCount, lines));
        }

        for(unsigned int &index : glyph.indices)
        {
            indices.emplace_back(index + offset);
        }

        offset += glyph.vertices.size();
        advance = glyph.advance;
        letterCount++;
    }
}

class Text
{
private:
    Font font;

    Transform transform;
    AABB boundingBox;

    int fontWeight;
    float fontSize;

    Color::Color fontColor;

    std::vector<Vector2> vertices;
    std::vector<Vector2> transformedVertices;
    std::vector<unsigned int> indices;

public:
    Text() {}
    Text(float x, float y);

    void Draw(Screen &screen);
    AABB GetBoundingBox();

    Transform &Transform();

    void setFont(const std::string &file);
    void setFont(const Font &font);
    void setString(const std::string &string);
    void setColor(Color::Color color);
    void setFontWeight(int weight);
    void setFontSize(float size);
};

Text::Text(float x, float y)
{
    this->transform.position = Vector2(x, y);
    this->fontWeight = 1;
    this->fontSize = 5;
    this->transform.ScaleTo({fontSize, fontSize});
    
    this->fontColor = Color::Black;
}

void Text::Draw(Screen &screen)
{
    if(transform.update)
    {
        transformedVertices = UpdateVertices(transform, vertices);
        boundingBox = UpdateBoundingBox(transformedVertices);
        transform.update = false;
    }

    if(fontColor == Color::Transparent) return;

    for(int i = 0; i + 1 <= indices.size(); i += 2)
    {   
        Vector2 a = transformedVertices[indices[i]];
        Vector2 b = transformedVertices[indices[i + 1]];

        if(fontWeight > 1)
        {
            DrawThickLine(screen, a.x, a.y, b.x, b.y, fontWeight, fontColor);
        }
        else
        {
            DrawLine(screen, a.x, a.y, b.x, b.y, fontColor);
        }
    }
}   

AABB Text::GetBoundingBox()
{
    if(transform.update)
    {
        transformedVertices = UpdateVertices(transform, vertices);
        boundingBox = UpdateBoundingBox(transformedVertices);
        transform.update = false;
    }

    return this->boundingBox;
}

Transform &Text::Transform()
{
    if(transform.update)
    {
        transformedVertices = UpdateVertices(transform, vertices);
        boundingBox = UpdateBoundingBox(transformedVertices);
        transform.update = false;
    }

    return this->transform;
}

void Text::setFont(const std::string &file)
{
    this->font.SetFont(file);
}

void Text::setFont(const Font &font)
{
    this->font = font;
}

void Text::setString(const std::string &string)
{
    CreateTextVertices(string, vertices, indices, font);
}

void Text::setColor(Color::Color color)
{
    this->fontColor = color;
}

void Text::setFontWeight(int weight)
{
    this->fontWeight = weight;
}

void Text::setFontSize(float size)
{
    this->fontSize = size;
    this->transform.ScaleTo({size, size});
}