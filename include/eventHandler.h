#ifndef EVENT_HANDLER_HEADER
#define EVENT_HANDLER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_events.h>
#include <ncurses.h>
#include "graphics.h"

typedef void (*EventHandlingFunction)(struct GameState *game);

void handleEventsConsole(struct GameState *gameState);
void handleEventsSDL2(struct GameState *gameState);


#endif 
