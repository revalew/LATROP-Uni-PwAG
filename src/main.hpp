#ifndef __MAIN_HPP
#define __MAIN_HPP

// #define DEFAULT_WIDTH 800
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
// #define DEFAULT_HEIGHT 600
#define FRAMETIME 17 // Delay between updates (FPS = 1/FRAMETIME)
#define CONST_DT 0.017f // FRAMETIME in seconds. Used for updating game logic
#define RADDEG 57.29577951308232088 // 180/PI

#ifdef _WIN32
    #include <windows.h>
    #include <GL/glew.h>
    #include <GL/freeglut.h>
    #include <GL/glext.h>
#elif defined(__linux__)
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GL/glext.h>
#endif

#include "player.hpp"
#include "map.hpp"

// Main functions
void update(int);
void respawn();
void nextLevel();
void draw();
void drawOverlay();
void drawPortals();
GLuint createTexture(const char *filename);
void loadTextures();
void setup(int *, char **);
// Callback functions
void mouse_moved(int, int);
void mouse_pressed(int, int, int, int);
void key_down(unsigned char, int, int);
void key_up(unsigned char, int , int);
void resize(int, int);
void window_status(int state);

int width, height;	/**< Screen width and height */
int mousex, mousey; /**< Current mouse position */
bool keystates[256];/**< State of all ASCII keyboard keys */
bool paused;		/**< True if the game is currently paused */
bool nmap_enabled;  /**< True if normal mapping is enabled */
float fade;  		/**< Used for screen fading */

Player player;
Map map;
int current_level;

#endif
