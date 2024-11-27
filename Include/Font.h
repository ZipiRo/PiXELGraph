struct Glyph
{
    std::vector<Vector2> vertices;
    std::vector<unsigned int> indices;
};

void CreateFontTable(const std::string &file, std::map<char, Glyph>& glyphs)
{
    std::ifstream FILE(file);
    if(!FILE) 
    {
        std::cerr << "Failed to create font table from file: " << file << std::endl;
        return;
    }
    
    glyphs.clear();
    
    char buffer[60];
    while (FILE)
    {
        FILE.getline(buffer, sizeof(buffer));

        if (strchr(buffer, '}'))
            continue;

        char c = buffer[0];
        Glyph glyph;

        if (!strchr(buffer, '{'))
            continue;

        int a = 0, b = 0;
        int vertexCounter = 0;
        int stateCounter = 0;

        FILE.getline(buffer, sizeof(buffer));

        int i = 0;
        bool valid = false;
        while (!valid)
        {
            if (stateCounter == 0)
            {
                if (buffer[i] == ';')
                {
                    stateCounter++;
                    FILE.getline(buffer, sizeof(buffer));
                    i = -1;
                }

                if (buffer[i] >= '0' && buffer[i] <= '9')
                {
                    if (vertexCounter == 0)
                        a = buffer[i] - '0';
                    else if (vertexCounter == 1)
                        b = buffer[i] - '0';

                    vertexCounter++;
                }

                if (vertexCounter > 1)
                {
                    glyph.vertices.emplace_back(Vector2(a, b));
                    vertexCounter = 0;
                }
            }
            else if (stateCounter == 1)
            {
                if (buffer[i] == ';')
                {
                    stateCounter++;
                    valid = true;
                }

                if (buffer[i] >= '0' && buffer[i] <= '9')
                {
                    glyph.indices.emplace_back(buffer[i] - '0');
                }
            }
            i++;
        }

        glyphs.insert({c, glyph});
    }
}
 
class Font
{
private:
    std::map<char, Glyph> glyphs;

public:
    Font() {};
    Font(const std::string &file);

    void SetFont(const std::string &file);
    Glyph Get(char character);
};

Font::Font(const std::string &file)
{
    CreateFontTable(file, glyphs);
}

void Font::SetFont(const std::string &file)
{
    CreateFontTable(file, glyphs);
}

Glyph Font::Get(char character)
{
    return glyphs[character];
}
