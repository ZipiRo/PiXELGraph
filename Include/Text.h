void CreateTextVertices(const std::string &string, std::vector<Vector2> &vertices, std::vector<unsigned int> &indices, Font &font)
{
    vertices.clear();
    indices.clear();

    // add \n for new line text

    int offset = 0;
    int letterSpacing = 5;
    for(int i = 0; string[i]; i++)
    {
        if(string[i] == ' ') continue;

        Glyph glyph = font.Get(string[i]);
        for(Vector2 &vertex : glyph.vertices)
        {
            vertices.emplace_back(vertex + Vector2(letterSpacing * i, 0));
        }

        for(unsigned int &index : glyph.indices)
        {
            indices.emplace_back(index + offset);
        }

        offset += glyph.vertices.size();
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

    Transform &Transform();

    void setFont(const std::string &file);
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