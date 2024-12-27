#Tinker Toys

## Description

This project is a collection of smaller focused projects developed while I work to learn
more complicated C++ concepts and approaches.

## Projects

### ArgoDraft

This is a shared library between my various projects that provides methods for logging and CLI
menus and options.

### DSA

This is a collection of data structures and algorithms that I have implemented in C++.

### Net Toys

This is a collection of networking projects exploring server and client communications using various
methods.

### OpenGL

This is a collection of projects that use OpenGL to render graphics.

#### imgui

This is a project that uses the imgui library to create a GUI for experimenting with OpenGL.

#### UI-Basics

This project is looking at the basics of creating generic primitives using OpenGL.

### Threaded

This is a collection of projects that explore threading in C++.

## Getting Started

### Prerequisites

- CMake
- C++ Compiler
- Vcpkg

### Building the shared libraries

In the root directory of the project, run the following script to build the shared libraries,
and automatically copy them to the individual project directories.:

```bash
#For development builds use:
./build_libs.sh

#For release builds use:
./build_libs.sh release
```

### Building the projects using the CLI

After building the shared libraries, you can build the individual projects by navigating to the
desired project directory and running the following commands:

```bash

#cmake will do something here

```

### Building the projects using JetBrains CLion

- Open the root directory of the project in CLion
- Tell CLion to use the CMakeLists.txt file in the desired project directory
- Build the project using the CLion build tools

### Building the projects using Visual Studio

TBD
