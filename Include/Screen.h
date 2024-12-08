#pragma once

#define CLEAR_CONSOLE std::cout << "\e[2J";

#define RESET_CURSOR_POSITION "\e[H";
#define RESET_PIXEL = "\e[0m";

const int MAX_WIDTH = 500;
const int MAX_HEIGHT = 300;

class Screen
{
private:  
    int width;
    int height;

    std::vector<Color> screen;

public:
    Screen();
    Screen(int width, int height);

    void Display();
    void Clear(Color color = Color255::White);
    void PlotPixel(int x, int y, Color color);
    int GetWidth();
    int GetHeight();
};

Screen::Screen()
{
    this->width = 0;
    this->height = 0;
}

Screen::Screen(int width, int height)
{
    this->width = (width > MAX_WIDTH) ? MAX_WIDTH : width;
    this->height = (height > MAX_HEIGHT) ? MAX_HEIGHT : height;
    this->screen = std::vector<Color>(this->width * this->height);
}

void Screen::Display()
{   
    std::string buffer; // MAKE A BUFFER
    buffer.reserve(width * height * 20);

    buffer += RESET_CURSOR_POSITION;
    for(int i = 0; i < width * height; i++) // ITTERATE THE SCREEN PIXELS
    {
        buffer += "\e[48;5;" + std::to_string(screen[i]) + "m \e[0m" ; // ADD TO BUFFER COLORED PIXEL, A SPACE AND RESET THE PIXEL
        if((i + 1) % width == 0) 
            buffer += '\n'; // ADD TO BUFFER NEW LINE IF WE GOT TO THE WIDTH LIMIT
    }

    std::cout << buffer; // THROW EVERYTHING AT ONCE AT THE CONSOLE
}

void Screen::Clear(Color color)
{
    std::fill(screen.begin(), screen.end(), color);
}

void Screen::PlotPixel(int x, int y, Color color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        screen[y * width + x] = color;
}

int Screen::GetWidth()
{
    return this->width;
}

int Screen::GetHeight()
{
    return this->height;
}

void DrawLine(Screen &screen, int x1, int y1, int x2, int y2, Color color)
{
    // Initialize variables
    int x, y;                     // Current pixel coordinates
    int dx = x2 - x1;             // Difference in x-coordinates
    int dy = y2 - y1;             // Difference in y-coordinates
    int dx1 = abs(dx);            // Absolute value of dx
    int dy1 = abs(dy);            // Absolute value of dy
    int px = 2 * dy1 - dx1;       // Decision parameter for shallow slopes
    int py = 2 * dx1 - dy1;       // Decision parameter for steep slopes
    int xe, ye, i;                // Loop control variables

    // Case 1: Line with a shallow slope (|dy| <= |dx|)
    if (dy1 <= dx1)
    {
        // Determine starting and ending points for iteration
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        // Draw the first pixel
        screen.PlotPixel(x, y, color);

        // Draw the rest of the line
        for (i = 0; x < xe; ++i)
        {
            x = x + 1; // Increment x-coordinate
            if (px < 0)
            {
                // Keep y constant
                px = px + 2 * dy1;
            }
            else
            {
                // Increment or decrement y based on line direction
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y = y + 1;
                else
                    y = y - 1;

                px = px + 2 * (dy1 - dx1);
            }

            // Draw the current pixel
            screen.PlotPixel(x, y, color);
        }
    }
    // Case 2: Line with a steep slope (|dy| > |dx|)
    else
    {
        // Determine starting and ending points for iteration
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        // Draw the first pixel
        screen.PlotPixel(x, y, color);

        // Draw the rest of the line
        for (i = 0; y < ye; ++i)
        {
            y = y + 1; // Increment y-coordinate
            if (py <= 0)
            {
                // Keep x constant
                py = py + 2 * dx1;
            }
            else
            {
                // Increment or decrement x based on line direction
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x = x + 1;
                else
                    x = x - 1;

                py = py + 2 * (dx1 - dy1);
            }

            // Draw the current pixel
            screen.PlotPixel(x, y, color);
        }
    }
}

void DrawThickLine(Screen &screen, int x1, int y1, int x2, int y2, int thickness, Color color)
{
    for (int i = -thickness / 2; i <= thickness / 2; ++i)
    {
        if (abs(x2 - x1) >= abs(y2 - y1))
            DrawLine(screen, x1, y1 + i, x2, y2 + i, color);
        else
            DrawLine(screen, x1 + i, y1, x2 + i, y2, color);
    }
}

void DrawLines(Screen &screen, const std::vector<Vector2> &vertices, Color color, int thickness = 1)
{
    for(auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
    {
        auto next_vertex = std::next(vertex);
        if(next_vertex == vertices.end())
            next_vertex = vertices.begin(); 
        
        Vector2 vertexA = *vertex;
        Vector2 vertexB = *next_vertex;
        if(thickness > 1) DrawThickLine(screen, vertexA.x, vertexA.y, vertexB.x, vertexB.y, thickness, color);
            else DrawLine(screen, vertexA.x, vertexA.y, vertexB.x, vertexB.y, color);
    }
}