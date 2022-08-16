# GLGrass

![screenshot.png](https://raw.githubusercontent.com/SomePineaple/GLGrass/master/screenshot.png)

## About

Personal project where I try to render decent looking modeled grass using opengl while still maintaining usable
framerates (120 fps on my laptop with an 11th gen i5-1135G7 and integrated IrisXe graphics). Inspired by Acerola and his
grass rendering YouTube series. 

## Features

- Chunking
- Culling of chunks outside of view
- Fog
- LOD

## Getting Started / Building

### Linux

Dependencies:
 - CMake
 - Make
 - Various X11 related development packages for GLFW. 
Click [here](https://www.glfw.org/docs/latest/compile.html#compile_deps) for more info.
 - OpenGL development package.

First clone the repository `git clone --recursive https://github.com/SomePineaple/GLGrass`.
Then `cd GLGrass`, and
`mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make` to build.
You can then run the project with `./glgrass`.

### Windows

Google how to build CMake project on Windows.
