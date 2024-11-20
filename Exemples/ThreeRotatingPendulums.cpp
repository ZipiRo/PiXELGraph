#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>
#include "Color.h"
#include "Screen.h"
#include "Vector2.h"
#include "Transform.h"
#include "Object.h"
#include "Rectangle.h"

const float PI = 3.141592f;
const int WIDTH = 320;
const int HEIGHT = 200;

// 300x200 (CMD RATIO FONTSIZE=2 LINES=32 COLLS=100 )
// 432x240, 320x240, 160x120, 100x100, 120x90
// CMD Line height = 0.6

Screen screen(WIDTH, HEIGHT);

int main()
{
    float angle = 0;
	float anglee = 0;
	float angleee = 0;
	float angleeee = 0;
	float angleeeee = 0;

	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        screen.Clear();

        // Second
		int rx = 50, ry = 50; 
		int x = WIDTH / 2, y = HEIGHT / 2;
		int sx = rx, sy = ry;
		angle += 0.1f;
		int dx = sin(angle) * sx;
		int dy = cos(angle) * sy;
        DrawLine(screen, x, y, dx + x, dy + y, Color::Red);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		anglee += 0.2f;
		dx = sin(anglee) * sx;
		dy = cos(anglee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Yellow);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		angleee += 0.3f;
		dx = sin(angleee) * sx;
		dy = cos(angleee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Green);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		angleeee += 0.4f;
		dx = sin(angleeee) * sx;
		dy = cos(angleeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Cyan);
		
		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		angleeeee += 0.5f;
		dx = sin(angleeeee) * sx;
		dy = cos(angleeeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Purple);

		// Third
		x = WIDTH - WIDTH / 2 / 2, y = HEIGHT / 2;
		sx = rx, sy = ry;
		dx = sin(angle) * sx;
		dy = cos(angle) * sy;
        DrawLine(screen, x, y, dx + x, dy + y, Color::Red);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(anglee) * sx;
		dy = cos(anglee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Yellow);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleee) * sx;
		dy = cos(angleee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Green);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleeee) * sx;
		dy = cos(angleeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Cyan);
		
		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleeeee) * sx;
		dy = cos(angleeeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Purple);

		// First
		x = WIDTH / 2 / 2, y = HEIGHT / 2;
		sx = rx, sy = ry;
		dx = sin(angle) * sx;
		dy = cos(angle) * sy;
        DrawLine(screen, x, y, dx + x, dy + y, Color::Red);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(anglee) * sx;
		dy = cos(anglee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Yellow);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleee) * sx;
		dy = cos(angleee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Green);

		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleeee) * sx;
		dy = cos(angleeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Cyan);
		
		x = dx + x, y = dy + y;
		sx = sx / 2, sy = sy / 2;
		dx = sin(angleeeee) * sx;
		dy = cos(angleeeee) * sy;
		DrawLine(screen, x, y, dx + x, dy + y, Color::Purple);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}