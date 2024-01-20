#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include "game.h"
#include <SDL2/SDL.h>
#include <ncurses.h>

typedef struct SDLContext {
  SDL_Window *window;    
  SDL_Renderer *renderer; 
  int width;            
  int height;            
} SDLContext;

void displayConsole(struct GameState *game);
int initializeSDL();
void finalizeSDL();


#endif
