#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>
#include <conio.h>

const int WIDTH = 160;
const int HEIGHT = 120;

// 432x240 / 320x240 / 160x120 / 100x100 / 120x90 //
// CMD Line height = 0.6 //

#define RESET_CURSOR_POSITION std::cout << "\033[H";
#define CLEAR_CONSOLE std::cout << "\033[2J";

const float PI = 3.141592f;

namespace Color
{   
    typedef std::string Color;

    const Color Black{"\033[40m"};
    const Color Red{"\033[41m"};
    const Color Green{"\033[42m"};
    const Color Yellow{"\033[43m"};
    const Color Blue{"\033[44m"};
    const Color Purple{"\033[45m"};
    const Color Cyan{"\033[46m"};
    const Color White{"\033[47m"};

    const Color IntenseBlack{"\033[100m"};
    const Color IntenseRed{"\033[101m"};
    const Color IntenseGreen{"\033[102m"};
    const Color IntenseYellow{"\033[103m"};
    const Color IntenseBlue{"\033[104m"};
    const Color IntensePurple{"\033[105m"};
    const Color IntenseCyan{"\033[106m"};
    const Color IntenseWhite{"\033[107m"};
}

namespace Key
{
	typedef int Key;
	
    const Key ESCAPE = 27;
    const Key ARROW_UP = 72;
    const Key ARROW_DOWN = 80;
    const Key ARROW_RIGHT = 77;
    const Key ARROW_LEFT = 75;
    const Key ENTER = 13;
    const Key SHIFT = 16;
    const Key CTRL = 17;
    const Key TAB = 9;
    const Key CAPSLOCK = 20;
    const Key SPACE = 32;
    const Key DELETE = 46;
}

struct Pixel
{
    Color::Color color = Color::White;
};

Pixel Screen[WIDTH * HEIGHT + 10];
Color::Color colors[20] = {Color::Black, Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan, Color::White,
							Color::IntenseBlack, Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntensePurple, Color::IntenseCyan, Color::IntenseWhite};

void FillScreen(Color::Color color = Color::White)
{
    for(int i = 0; i < WIDTH * HEIGHT; i++)
        Screen[i] = Pixel{color};
}

void DrawScreen()
{
    RESET_CURSOR_POSITION
    
    std::string buffer;
    for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        Pixel pixel = Screen[i];
        buffer += pixel.color + ' ' + "\033[0m";
        if(!((i + 1) % WIDTH)) buffer += '\n';
    }

    std::cout << buffer;
}

void PutPixel(int x, int y, Color::Color color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        Screen[y * WIDTH + x] = Pixel{color};
}

void Line(int x1, int y1, int x2, int y2, Color::Color color)
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

			PutPixel(x, y, color);
			
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
				PutPixel(x, y, color);
			}
		}
		else
		{
			if (dy >= 0)
				{ x = x1; y = y1; ye = y2; }
			else
				{ x = x2; y = y2; ye = y1; }

			PutPixel(x, y, color);

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
				PutPixel(x, y, color);
			}
		}
}

void FillScreenRandom()
{
	int randColor;
	for(int i = 0; i < WIDTH * HEIGHT; i++)
	{
		randColor = 0 + rand() % 8 - 0 + 1;
		Screen[i].color = colors[randColor];
	}
}

struct Point
{
	float x, y;
};

struct Rectangle
{
	float x, y;
	float width, height;
	std::vector<Point> vertices;
};

std::vector<Point> CreateRectangleVertices(float width, float height)
{
	std::vector<Point> vertices;

	float left = -width / 2.0f;
	float right = left + width;
	float bottom = -height / 2.0f;
	float top = bottom + height;

	vertices.emplace_back(Point{left, top});
	vertices.emplace_back(Point{right, top});
	vertices.emplace_back(Point{right, bottom});
	vertices.emplace_back(Point{left, bottom});

	return vertices;
}

std::vector<Point> RotateZ(const std::vector<Point> &vertices, float angle)
{
	std::vector<Point> transformVertices;

	for(Point vertex : vertices)
	{
		float dx = cos(angle) * vertex.x - sin(angle) * vertex.y;
		float dy = sin(angle) * vertex.x + cos(angle) * vertex.y;
		transformVertices.emplace_back(Point{dx, dy});
	}

	return transformVertices;
}

void DrawRectangle(int x, int y, const std::vector<Point> &vertices, Color::Color color)
{
	for(auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
	{
		auto next_vertex = std::next(vertex);
		if(next_vertex == vertices.end())
			next_vertex = vertices.begin(); 
		
		Point vertexA = *vertex;
		Point vertexB = *next_vertex;

		Line(vertexA.x + x, vertexA.y + y, vertexB.x + x, vertexB.y + y, color);
	}
}

int main()
{
	int curentKey;
	int running = true;

    while (running)
    {   
		if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == Key::ESCAPE) running = false; 

		curentKey = 0;

    	FillScreen();

        DrawScreen();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}