# Snake Game

A simple cross platform template for setting up a project with the bleeding edge raylib code.
Works with C or C++.

![demo](./resources/demo.gif)

## Supported Platforms

Game supports the main 3 desktop platforms:

- Windows
- Linux
- MacOS

# Windows Users

There are two compiler toolchains available for windows, MinGW-W64 (a free compiler using GCC), and Microsoft Visual Studio

## Using MinGW-W64

- Double click the `build-MinGW-W64.bat` file
- CD into the folder in your terminal
- run `make`
- You are good to go

### Note on MinGW-64 versions

Make sure you have a modern version of MinGW-W64 (not mingw).
The best place to get it is from the W64devkit from
https://github.com/skeeto/w64devkit/releases
or the version installed with the raylib installer

#### If you have installed raylib from the installer

Make sure you have added the path

`C:\raylib\w64devkit\bin`

To your path environment variable so that the compiler that came with raylib can be found.

DO NOT INSTALL ANOTHER MinGW-W64 from another source such as msys2, you don't need it.

## Microsoft Visual Studio

- Run `build-VisualStudio2022.bat`
- double click the `.sln` file that is generated
- develop your game
- you are good to go

# Linux Users

- CD into the build folder
- run `./premake5 gmake2`
- CD back to the root
- run `make`
- you are good to go

# MacOS Users

- CD into the build folder
- run `./premake5.osx gmake2`
- CD back to the root
- run `make`
- you are good to go

# Output files

The built code will be in the bin dir

# Working directories and the resources folder

The example uses a utility function from `path_utils.h` that will find the resources dir and set it as the current working directory. This is very useful when starting out. If you wish to manage your own working directory you can simply remove the call to the function and the header.

# Changing to C++

Simply rename `src/main.c` to `src/main.cpp` and re-run the steps above and do a clean build.

# Using your own code

Simply remove `src/main.c` and replace it with your code, and re-run the steps above and do a clean build.

# Building for other OpenGL targets

If you need to build for a different OpenGL version than the default (OpenGL 3.3) you can specify an OpenGL version in your premake command line. Just modify the bat file or add the following to your command line

## For OpenGL 1.1

`--graphics=opengl11`

## For OpenGL 2.1

`--graphics=opengl21`

## For OpenGL 4.3

`--graphics=opengl43`

## For OpenGLES 2.0

`--graphics=opengles2`

## For OpenGLES 3.0

`--graphics=opengles3`

## Game executable

path: ./bin/Debug/raylib-quickstart

# License

MIT License Copyright (c) 2025 Ilyes Chaabane

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

## Takeaways

What a fun journey working with Raylib and C++ to make this game, I followed a guide and added my own touch to the game .
I am looking forward to expand my knowledge in Game Dev and work on more projects in the near future by the Will Of God.

### Thank You
