#ifndef EVENT_HANDLER_HEADER
#define EVENT_HANDLER_HEADER

#include <SDL2/SDL.h>
#include "../include/player.h"
#include "game.h"
#include "input.h"
#include <ncurses.h>


void handleEvents(struct GameState* game, Player* player);
void handleEventsSDL2(struct GameState* game, Player* player);


#endif 
