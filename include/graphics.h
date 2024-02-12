#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include "game.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720
#define FULLSCREEN_WIDTH 1920
#define FULLSCREEN_HEIGHT 1080
#define MIN_BLOCKS_WIDTH 16
#define MIN_BLOCKS_HEIGHT 8
#define TEXTURE_WIDTH 128 
#define TEXTURE_HEIGHT 128
#define FPS 60
#define SPEED 691.891 
#define TARGETS_CHAR_SIZE 16

typedef void (*DisplayFunction)(struct GameState *game);

typedef struct Text{
    SDL_Texture *texture;
    SDL_Rect destination;
} Text;

typedef struct Texts{
    Text victory;
    Text restart;
    Text targets;
    Text quit;
    Text name;
    Text fullscreen;
} Texts;

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
    TTF_Font *font;
    int width;
    int height;
    Entity player;
    Entity box;
    Texts *texts;
} GraphicsContext;

extern GraphicsContext graphicsContext;

void SDL_ErrorExit(const char *section, const char *error);
void initializeSprites();
void initializeSDL();
void destroysTextsTextures(Texts *texts);
void finalizeSDL();
SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *filePath);
Text makeText(const char *text, int x);
Text makeVictoryText(const char *text);
void updateRenderTexts(struct GameState *game);
void initializeTexts();
void renderMap(struct GameState *game);
void renderEntities(struct GameState *game);
void displaySDL(struct GameState *game);
void initializeNCurses();
void displayConsole(struct GameState *game);


#endif
