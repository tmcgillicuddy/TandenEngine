# Tanden Engine

<img src="https://github.com/tmcgillicuddy/TandenEngine/blob/develop/Documents/TandenLogo.png" width="400" />

[![Build](https://ci.appveyor.com/api/projects/status/32r7s2skrgm9ubva?svg=true)](https://ci.appveyor.com/project/tmcgillicuddy/TandenEngine)
[![CircleCI](https://circleci.com/gh/tmcgillicuddy/TandenEngine/tree/develop.svg?style=svg)](https://circleci.com/gh/tmcgillicuddy/TandenEngine/tree/develop)

## Features
Current Features Supported:
 * Vulkan Rendering
 * Rigidbody Dynamics
 * Model file loading
 * Image file loading
 * Scene, Prefab, and Material saving
 * Component System
 * Ray Tracing

## Dependecies
Tanden Engine uses these libraries:

 * [Vulkan](https://www.khronos.org/vulkan) - Vulkan interface
 * [GLFW](https://github.com/glfw/glfw) - Window creation
 * [Imgui](https://github.com/ocornut/imgui) - GUI generation
 * [TinyObjLoader](https://github.com/syoyo/tinyobjloader) - Obj File Loading
 * [Stb](https://github.com/nothings/stb) - Image File Loading

### Required Cygwin Packages

* gcc-g++
* gdb
* libX11-devel
* libXcursor-devel
* libXi-devel
* libXinerma-devel
* libXrandr-devel
* make
* xorg-cf-files

## Compiling:
Clone the repo and run 'git submodule update --init --recursive' to get the submodules

Make sure you have [CMake](https://cmake.org/download/) and the [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows) downloaded and installed.

## Using cpplint:

### Installing
Use ``` pip ``` to install cpplint with the bash command:

 ```
 C:/Python27/Scripts/pip.exe install cpplint --user
```
then set up alias for cpplint

On Desktop:

 ``` 
 touch bashsrc
 
 vim bashsrc
 ```
 
Insert line and save:

  ```
  alias lint='C:/Python27/Scripts/cpplint.exe'
  ```
  
On Desktop

```
source bashsrc
```

Now ```lint``` will run cpplint on given files

### Running

Navigate to the engine directory and run the ```lint``` command with the ```--recursive``` flag

```
lint --recursive --quiet TandenEngine/Source/....
``` 
