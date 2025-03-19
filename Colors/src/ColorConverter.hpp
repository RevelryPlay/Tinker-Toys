#pragma once
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

struct CMYKColor {
    float c, m, y, k;
};

typedef std::string HEXColor;  // 6 characters
typedef std::string HEXAColor; // 8 characters

struct HSLColor {
    float h, s, l;
};

struct HSIColor {
    float h, s, i;
};

struct HSVColor {
    float h, s, v;
};

struct HWBColor {
    float h, w, b;
};

struct LABColor {
    float l, a, b;
};

struct RGBColor {
    float r, g, b;
};

struct RGBAColor {
    float r, g, b, a;
};

struct ColorConverter {
    ColorConverter( )  = default;
    ~ColorConverter( ) = default;

    template < typename T >
    static CMYKColor toCMYK( T color );

    template < typename T >
    static HEXColor toHEX( T color );

    template < typename T >
    static HEXAColor toHEXA( T color );

    template < typename T >
    static HSLColor toHSL( T color );

    template < typename T >
    static HSIColor toHSI( T color );

    template < typename T >
    static HSVColor toHSV( T color );

    template < typename T >
    static LABColor toLAB( T color );

    template < typename T >
    static RGBColor toRGB( T color );

    template < typename T >
    static RGBAColor toRGBA( T color );
};
