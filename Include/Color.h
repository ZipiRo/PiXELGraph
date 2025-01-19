#pragma once

#ifdef COLOR_RGB

class Color
{
public:
    int r, g, b;

    Color()
    {
        r = 0;
        g = 0;
        b = 0;
    }

    Color(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool operator!= (const Color &other) const
    {
        return r != other.r || g != other.g || b != other.b;
    }

    bool operator== (const Color &other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    static const Color Transparent;
    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Purple;
    static const Color Gray;
    static const Color LightRed;
    static const Color LightGreen;
    static const Color LightBlue;
    static const Color LightYellow;
    static const Color LightCyan;
    static const Color LightPurple;
};

const Color Color::Transparent = Color(0, 0, -1);
const Color Color::White = Color(255, 255, 255);
const Color Color::Black = Color(0, 0, 0);
const Color Color::Red = Color(255, 0, 0);
const Color Color::Green = Color(0, 255, 0);
const Color Color::Blue = Color(0, 0, 255);
const Color Color::Yellow = Color(255, 255, 0);
const Color Color::Cyan = Color(0, 255, 255);
const Color Color::Purple = Color(255, 0, 255);
const Color Color::Gray = Color(128, 128, 128);
const Color Color::LightRed = Color(255, 128, 128);
const Color Color::LightGreen = Color(128, 255, 128);
const Color Color::LightBlue = Color(128, 128, 255);
const Color Color::LightYellow = Color(255, 255, 128);
const Color Color::LightCyan = Color(128, 255, 255);
const Color Color::LightPurple = Color(255, 128, 255);

#endif

#ifndef COLOR_RGB

class Color
{
public:
    int code;

    Color()
    {
        code = -1;
    }

    Color(int code)
    {
        this->code = code;
    }

    bool operator!= (const Color &other) const
    {
        return code != other.code;
    }

    bool operator== (const Color &other) const
    {
        return code == other.code;
    }

    static const Color Transparent;
    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Purple;
    static const Color Gray;
    static const Color LightRed;
    static const Color LightGreen;
    static const Color LightBlue;
    static const Color LightYellow;
    static const Color LightCyan;
    static const Color LightPurple;
    static const Color LightWhite;
};


#ifdef COLOR_16

const Color Color::Transparent = -1;
const Color Color::White = 107;
const Color Color::Black = 40;
const Color Color::Red = 41;
const Color Color::Green = 42;
const Color Color::Blue = 44;
const Color Color::Yellow = 43;
const Color Color::Cyan = 46;
const Color Color::Purple = 45;
const Color Color::Gray = 100;
const Color Color::LightRed = 101;
const Color Color::LightGreen = 102;
const Color Color::LightBlue = 104;
const Color Color::LightYellow = 103;
const Color Color::LightCyan = 106;
const Color Color::LightPurple = 105;
const Color Color::LightWhite = 47;

#endif

#ifdef COLOR_256

const Color Color::Transparent = -1;
const Color Color::White = 255;
const Color Color::Black = 16;
const Color Color::Red = 124;
const Color Color::Green = 40;
const Color Color::Blue = 18;
const Color Color::Yellow = 220;
const Color Color::Cyan = 51;
const Color Color::Purple = 53;
const Color Color::Gray = 242;
const Color Color::LightRed = 196;
const Color Color::LightGreen = 46;
const Color Color::LightBlue = 21;
const Color Color::LightYellow = 226;
const Color Color::LightCyan = 87;
const Color Color::LightPurple = 55;

#endif

#endif