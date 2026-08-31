xcube2d
=======

A simple 2D game engine based on SDL 3.0 to teach core game elements.

### Dependencies

To simplify development, the following libraries are included:

* SDL 3
* SDL_image 3
* SDL_mixer 3
* SDL_ttf 3

### Build

The project is configured to be developed on Windows, so it only includes Windows-specific SDL versions, however you should be able to build on Linux and Mac OS by getting appropriate SDL distributions.

To build, you will need:

* 	CMake 4.3.+  (https://cmake.org/download/)  Latest 4.3 Release (4.3.+) Binary zip file
*	Visual Studio 2026

Extract and Rename your cmake folder to cmake-4.4.3   (or whatever version you have).

1. Download this repository by clicking "Clone or download" -> Download zip.
2. Extract the zip file and rename `xcube2d-SDL3-master` to `xcube`.

Open the command line (via [Git Bash](https://gitforwindows.org/) (git for windows")):

```
cd xcube
mkdir build
cd build

move to the downloaded  cmake-4.3.3 into the build directory 
run

./cmake-4.3.3/bin/cmake.exe .. -G "Visual Studio 18 2026"

```

After this, a ".sln" will be generated in `build/`.

After this, a ".sln" will be generated in build/.
1.	Open the ".sln" file with Visual Studio 2026.
2.	Right click on MyGame in project explorer and select as startup project.
3.	Right click on MyGame again and select Properties.
4.	In the properties window, Linker -> System and change SubSystem to Console.
5.	Copy the res/ directory to the build directory.

You can now run the demo from Visual Studio via Local Windows Debugger.


### Task

**Read the assignment brief!**

You should only modify:

* MyEngineSystem.h
* MyEngineSystem.cpp
* MyGame.h
* MyGame.cpp