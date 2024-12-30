# **Latrop: OpenGL recreation of Valve's beloved game - Portal, but backwards!**

</br>
</br>

## **Project Overview**

**Latrop** is a 3D game developed in **OpenGL**, inspired by the concept of creating and utilizing portals to solve puzzles and progress through levels. This game was created as a university project for the course **"Programming in Graphical API"** at Silesian University of Science.

The main goal of this project was to explore graphical programming concepts, implement advanced rendering techniques, and demonstrate proficiency in using the OpenGL API for real-time 3D graphics.

</br>
</br>

## Table Of Contents

1. [Gameplay](#gameplay)
2. [Control Scheme](#control-scheme)
3. [Features](#features)
4. [Technical Details](#technical-details)
5. [Directory Structure](#directory-structure)
6. [Download precompiled release](#download-precompiled-release)
7. [How to Build and Run](#how-to-build-and-run)
   - [Requirements](#requirements)
   - [Building the Project](#building-the-project)
   - [Running the Game](#running-the-game)

</br>
</br>

## **Gameplay**

In **Latrop**, players navigate through a series of levels filled with challenges and obstacles (like the pit of acid). The player uses a portal gun to:

- Create portals on designated surfaces (some surfaces won't allow you to place the portal on them).
- Solve puzzles by strategically positioning portals.
- Overcome challenges such as traps.

The game combines logic, and creativity to complete each level.

</br>
</br>

## **Control scheme**

Player can use the following controls to play the game:

1. **Movement**

- `W/S/A/D` - Move forward, backward, left, and right,
- `Space` - Jump,

</br>

2. **Camera control**

- `Mouse` - Look around the game world,
- `Left Click` - Create a blue portal,
- `Right Click` - Create a orange portal.

</br>

3. **Additional commands**

- `Esc` - Pause / Resume the game,
- `Return` - Restart the level after death or completing a level,
- `1-9` - Select a level (or restart),
- `R` - Reset the portals,
- `B` - Toggle the normal mapping mode,
- `N` - Toggle the wireframe mode,

</br>
</br>

## **Features**

- **Portal Mechanics**: Create two interconnected portals to teleport across the game world.
- **3D Environment**: Fully rendered 3D levels designed using OpenGL using a **custom map generator**.
- **Physics Simulation**: Basic physics for realistic movement and interaction.
- **Resource Management**: Textures and maps are loaded dynamically during runtime.

</br>
</br>

## **Technical Details**

- **Programming Language**: C++
- **Graphics Library**: OpenGL
- **Development Tools**:
  - **CMake**: For project building and management.
  - **GLEW**: For OpenGL extension loading.
  - **GLUT**: For window creation and input handling.
- **Assets**: All resources (textures, maps, etc.) are stored in the `data` and `maps` directories inside of the `src` directory.

</br>
</br>

## **Directory Structure**

- `src/` - Contains the C++ source code files for the game and all of the assets (shaders, textures, and maps).
- `data/` - Includes textures and shaders.
- `maps/` - Contains level design files.
- `build/` - Directory for compiled binaries and temporary build files (created during the build process).

</br>
</br>

## **Download precompiled release**

You can find precompiled releases for both Linux and Windows in the [releases section](https://github.com/revalew/LATROP-Uni-PwAG/releases).

On Windows, the `latrop.exe` will display a warning that the application is potentially dangerous (I don't want to get into exe signing right now...). No malicious code has been injected into this game (yet... :skull: but you can check the [workflow file](./.github/workflows/create_release.yml) and [source code](./src/) yourself), so you can safely click `More info` and `Run anyway`.

</br>
</br>

## **How to Build and Run**

### **Requirements**

- C++ Compiler (e.g., GCC, Clang, MSVC)
- Git
- CMake (minimum version 3.5)
- OpenGL-compatible hardware
- OpenGL libraries:
  - GLEW
  - GLUT

</br>

### **Building the Project**

</br>

> [!NOTE]
>
> This section has been tested using GNU/Linux, but will work almost identically on Windows using CMake app.
>
> On Windows you have to manually download and link the required libraries in the Visual Studio project (configuration not included)

</br>

<ol>
<li> Clone the repository

</br>

```bash
git clone https://github.com/revalew/LATROP-Uni-PwAG.git
```

</br>
</li>
<li> Install required dependencies (e.g. using <code>dnf</code> on <b>RHEL distributions of Linux</b>)

</br>

```bash
sudo dnf install mesa-libGL-devel mesa-libEGL-devel glfw-devel glew-devel glm-devel renderdoc
```

</br>
</li>
<li> Navigate to the project directory

</br>

```bash
cd LATROP-Uni-PwAG
```

</br>
</li>
<li> Create a build directory

</br>

```bash
mkdir build && cd build
```

</br>
</li>
<li> Run <code>CMake</code> to configure the build

</br>

```bash
cmake ..
```

</br>

OR using `ccmake` with "GUI"

</br>

```bash
ccmake ..
```

</br>
</li>
<li> Compile the project (<code>-j$(nproc)</code> is using all of the available cores and can be modified to a different number based on the number of cores your CPU has, e.g. 12 for a 16 core CPU, i.e. <code>-j12</code>)

</br>

```bash
cmake --build . -j$(nproc)
```

</li>
</ol>

</br>

### **Running the Game**

After building, execute the game (_inside the build folder_):

```bash
./latrop
```
