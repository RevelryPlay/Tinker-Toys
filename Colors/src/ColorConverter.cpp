#include "ColorConverter.hpp"

template < typename T >
CMYKColor ColorConverter::toCMYK( T color ) {
    return { 0, 0, 0, 0 };
}

template < typename T >
HEXColor ColorConverter::toHEX( T color ) {
    // If the color is a HEX value and has a HEX length of 6, return it
    if ( std::is_same_v< T, HEXColor > && color.length( ) == 6 ) {
        return color;
    }

    // If the color is a HEXA value and has a HEX length of 8, return the first 6 characters
    if ( std::is_same_v< T, HEXColor > && color.length( ) == 8 ) {
        return color.substr( 0, 6 );
    }

    // if the color is a HEX value and has a length, not 7 or 9 return an empty string
    if ( std::is_same_v< T, std::string > && color.length( ) != 7 && color.length( ) != 9 ) {
        return "";
    }


    // If the color is RGB or RGBA, convert it to HEX
    if ( std::is_same_v< T, RGBColor > || std::is_same_v< T, RGBAColor > ) {
        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( color.r * 255 );
        ss << std::setw( 2 ) << static_cast< int >( color.g * 255 );
        ss << std::setw( 2 ) << static_cast< int >( color.b * 255 );
        return { ss.str( ) };
    }

    // If the color is CMYK, convert it to HEX
    if ( std::is_same_v< T, CMYKColor > ) {
        float c = color.c;
        float m = color.m;
        float y = color.y;
        float k = color.k;

        float r = 1 - std::min( 1.0f, c * ( 1 - k ) + k );
        float g = 1 - std::min( 1.0f, m * ( 1 - k ) + k );
        float b = 1 - std::min( 1.0f, y * ( 1 - k ) + k );

        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( r * 255 );
        ss << std::setw( 2 ) << static_cast< int >( g * 255 );
        ss << std::setw( 2 ) << static_cast< int >( b * 255 );
        return { ss.str( ) };
    }

    // If the color is HSL, convert it to HEX
    if ( std::is_same_v< T, HSLColor > ) {
        float h = color.h;
        float s = color.s;
        float l = color.l;

        float c = ( 1 - std::abs( 2 * l - 1 ) ) * s;
        float x = c * ( 1 - std::abs( std::fmod( h / 60, 2 ) - 1 ) );
        float m = l - c / 2;

        float r = 0;
        float g = 0;
        float b = 0;

        if ( h >= 0 && h < 60 ) {
            r = c;
            g = x;
        } else if ( h >= 60 && h < 120 ) {
            r = x;
            g = c;
        } else if ( h >= 120 && h < 180 ) {
            g = c;
            b = x;
        } else if ( h >= 180 && h < 240 ) {
            g = x;
            b = c;
        } else if ( h >= 240 && h < 300 ) {
            r = x;
            b = c;
        } else if ( h >= 300 && h < 360 ) {
            r = c;
            b = x;
        }

        r = ( r + m ) * 255;
        g = ( g + m ) * 255;
        b = ( b + m ) * 255;

        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( r );
        ss << std::setw( 2 ) << static_cast< int >( g );
        ss << std::setw( 2 ) << static_cast< int >( b );
        return { ss.str( ) };
    }

    // If the color is HSI, convert it to HEX
    if ( std::is_same_v< T, HSIColor > ) {
        float h = color.h;
        float s = color.s;
        float i = color.i;

        float r = 0;
        float g = 0;
        float b = 0;

        float x = i * ( 1 - s );
        if ( h < 120 ) {
            b = x;
            r = i * ( 1 + s * std::cos( h ) / std::cos( 60 - h ) );
            g = 3 * i - ( r + b );
        } else if ( h < 240 ) {
            h -= 120;
            r = x;
            g = i * ( 1 + s * std::cos( h ) / std::cos( 60 - h ) );
            b = 3 * i - ( r + g );
        } else {
            h -= 240;
            g = x;
            b = i * ( 1 + s * std::cos( h ) / std::cos( 60 - h ) );
            r = 3 * i - ( g + b );
        }

        r = r * 255;
        g = g * 255;
        b = b * 255;

        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( r );
        ss << std::setw( 2 ) << static_cast< int >( g );
        ss << std::setw( 2 ) << static_cast< int >( b );
        return { ss.str( ) };
    }

    // If the color is HSV, convert it to HEX
    if ( std::is_same_v< T, HSVColor > ) {
        float h = color.h;
        float s = color.s;
        float v = color.v;

        float c = v * s;
        float x = c * ( 1 - std::abs( std::fmod( h / 60, 2 ) - 1 ) );
        float m = v - c;

        float r = 0;
        float g = 0;
        float b = 0;

        if ( h >= 0 && h < 60 ) {
            r = c;
            g = x;
        } else if ( h >= 60 && h < 120 ) {
            r = x;
            g = c;
        } else if ( h >= 120 && h < 180 ) {
            g = c;
            b = x;
        } else if ( h >= 180 && h < 240 ) {
            g = x;
            b = c;
        } else if ( h >= 240 && h < 300 ) {
            r = x;
            b = c;
        } else if ( h >= 300 && h < 360 ) {
            r = c;
            b = x;
        }

        r = ( r + m ) * 255;
        g = ( g + m ) * 255;
        b = ( b + m ) * 255;

        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( r );
        ss << std::setw( 2 ) << static_cast< int >( g );
        ss << std::setw( 2 ) << static_cast< int >( b );
        return { ss.str( ) };
    }

    // If the color is LAB, convert it to HEX
    if ( std::is_same_v< T, LABColor > ) {

        float y = ( color.l + 16 ) / 116;
        float x = color.a / 500 + y;
        float z = y - color.b / 200;

        x = x > 0.206893034 ? 100 * x * x * x : ( x - 16 / 116 ) / 7.787;
        y = y > 0.206893034 ? 100 * y * y * y : ( y - 16 / 116 ) / 7.787;
        z = z > 0.206893034 ? 100 * z * z * z : ( z - 16 / 116 ) / 7.787;

        float r = x * 3.2406 + y * -1.5372 + z * -0.4986;
        float g = x * -0.9689 + y * 1.8758 + z * 0.0415;
        float b = x * 0.0557 + y * -0.2040 + z * 1.0570;

        r = r > 0.0031308 ? 1.055 * std::pow( r, 1 / 2.4 ) - 0.055 : 12.92 * r;
        g = g > 0.0031308 ? 1.055 * std::pow( g, 1 / 2.4 ) - 0.055 : 12.92 * g;
        b = b > 0.0031308 ? 1.055 * std::pow( b, 1 / 2.4 ) - 0.055 : 12.92 * b;

        r = r * 255;
        g = g * 255;
        b = b * 255;

        std::stringstream ss;
        ss << std::hex << std::setfill( '0' );
        ss << "#" << std::setw( 2 ) << static_cast< int >( r );
        ss << std::setw( 2 ) << static_cast< int >( g );
        ss << std::setw( 2 ) << static_cast< int >( b );
        return { ss.str( ) };
    }

    // If the color is unknown, return an empty string
    return { "" };
}

template < typename T >
std::string ColorConverter::toHEXA( T color ) {
    return { "" };
}

template < typename T >
HSLColor ColorConverter::toHSL( T color ) {
    return { 0, 0, 0 };
}

template < typename T >
HSIColor ColorConverter::toHSI( T color ) {
    return { 0, 0, 0 };
}

template < typename T >
HSVColor ColorConverter::toHSV( T color ) {
    return { 0, 0, 0 };
}
template < typename T >
LABColor ColorConverter::toLAB( T color ) {
    return { 0, 0, 0 };
}

template < typename T >
RGBColor ColorConverter::toRGB( T color ) {
    return { 0, 0, 0 };
}

template < typename T >
RGBAColor ColorConverter::toRGBA( T color ) {
    return { 0, 0, 0, 0 };
}
