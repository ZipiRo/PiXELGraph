#pragma once

#define RESET_CURSOR_POSITION std::cout << "\033[H";
#define CLEAR_CONSOLE std::cout << "\033[2J";
#define RESET_PIXEL "\033[0m"

struct Pixel { Color::Color color; };

const int MAX_WIDTH = 500;
const int MAX_HEIGHT = 300;

class Screen
{
protected:
    int width;
    int height;

private:    
    Pixel Canvas[MAX_WIDTH * MAX_HEIGHT + 5];

public:
    Screen();
    Screen(int width, int height);

    void Display();
    void Clear(Color::Color color = Color::White);
    void PutPixel(int x, int y, Color::Color color);
    int get_width();
    int get_height();
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
}

void Screen::Display()
{
    RESET_CURSOR_POSITION
    
    std::string buffer;
    for(int i = 0; i < this->width * this->height; i++)
    {
        buffer += Canvas[i].color + ' ' + "\033[0m";
        if(!((i + 1) % this->width)) buffer += '\n';
    }

    std::cout << buffer;
}

void Screen::Clear(Color::Color color)
{
    for(int i = 0; i < this->width * this->height; i++)
        Canvas[i] = Pixel{color};
}

void Screen::PutPixel(int x, int y, Color::Color color)
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
        Canvas[y * this->width + x] = Pixel{color};
}

int Screen::get_width()
{
    return this->width;
}

int Screen::get_height()
{
    return this->height;
}

void DrawLine(Screen &screen, int x1, int y1, int x2, int y2, Color::Color color)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
            { x = x1; y = y1; xe = x2; }
        else
            { x = x2; y = y2; xe = x1;}

        screen.PutPixel(x, y, color);
        
        for (i = 0; x<xe; i++)
        {
            x = x + 1;
            if (px<0)
                px = px + 2 * dy1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            screen.PutPixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
            { x = x1; y = y1; ye = y2; }
        else
            { x = x2; y = y2; ye = y1; }

        screen.PutPixel(x, y, color);

        for (i = 0; y<ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            screen.PutPixel(x, y, color);
        }
    }
}