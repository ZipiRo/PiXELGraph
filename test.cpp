#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include "Include/Vector2.h"
#include "Include/Font.h"

Font font("pixel.font");

int main()
{ 
    for(const auto &pair : font.glyphs)
    {
        std::cout << "Letter: " << pair.first << '\n';
        Glyph glyph = pair.second;

        std::cout << "Vertices: \n";
        for(const Vector2& vertex : glyph.vertices)
        {
            std::cout << "x:" << vertex.x << " y:" << vertex.y << '\n';
        }

        std::cout << "Indeces: \n";
        for(const int& indece : glyph.indices)
        {
            std::cout << indece << ' ';
        }
        std::cout << "\n\n";
    }


    return 0;
}