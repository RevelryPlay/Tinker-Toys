#include <ArgoDraft/ConsoleMenu.hpp>
#include <iostream>

#include "src/ColorConverter.hpp"


int main( ) {

    constexpr RGBColor rgb   = { 0.5, 0.5, 0.5 };
    const auto         color = ColorConverter::toHEX( rgb );
    std::cout << "RGB: " << rgb.r << ", " << rgb.g << ", " << rgb.b << " -> HEX: " << color
              << "\n";


    std::cout << "Type `help` for a list of commands" << "\n";
    try {
        ArgoDraft::MainMenu menu;

        menu.AddAction( { "About",
                          "Get the projects description details",
                          [] {
                              std::cout << "This project is meant to be a playground for learning how to convert "
                                           "colors between formats."
                                        << "\n";
                              std::cout << "Currently the following formats are supported" << "\n";
                              std::cout << "CMYK, HEX, RGB, RGBA, HSL, HSI, HSV, HWB, Lab" << "\n";

                              std::cout << "Available commands:" << "\n";
                              std::cout << "Convert{formatIn}to{formatOut}({color})" << "\n";
                              std::cout << "Examples:" << "\n";

                              std::cout << "\n";
                              std::cout << "\n";
                              std::cout << "For more information, please see the help command" << "\n";
                          },
                          { "about" } } );

        // menu.AddAction( { "RGB->Hex",
        //                   "Convert RGB to Hex",
        //                   [] {
        //                       constexpr RGBColor rgb   = { 0.5, 0.5, 0.5 };
        //                       const auto         color = ColorConverter::toRGB( rgb );
        //                       std::cout << "RGB: " << rgb.r << ", " << rgb.g << ", " << rgb.b << " -> CMYK: "
        //                                 << "\n";
        //                   },
        //                   { "rgbhex" } } );

        menu.Init( );
    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what( ) << "\n";
    }

    return 0;
}
