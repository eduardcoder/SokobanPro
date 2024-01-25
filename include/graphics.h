#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include "game.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <ncurses.h>

#define DEFAULT_SCREEN_WIDTH 1600 
#define DEFAULT_SCREEN_HEIGHT 900
#define TEXTURE_WIDTH 128 
#define TEXTURE_HEIGHT 128
#define FPS 60
#define SPEED 128.0 

typedef void (*DisplayFunction)(struct GameState *game);

typedef struct Entity {
    int isMoving;
    enum Direction direction;
    int frameClip;
    SDL_Rect sourceSprite;
    SDL_Rect destinationRender;    
    Location spriteUpClips[4];
    Location spriteDownClips[4];
    Location spriteRightClips[4];
    Location spriteLeftClips[4];
} Entity;

typedef struct GraphicsContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *gameTexture;
    int width;
    int height;
    Entity player;
    Entity box;
} GraphicsContext;

extern GraphicsContext graphicsContext;

void SDL_ErrorExit(const char *section, const char *error);
void initializeSprites();
void initializeSDL();
void finalizeSDL();
SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *filePath);
void renderMap(struct GameState *game);
void renderEntities(struct GameState *game);
void displaySDL(struct GameState *game);
void initializeNCurses();
void displayConsole(struct GameState *game);


#endif
