/**
 * @file eventHandler.h
 * @brief Header file containing declarations related to event handling in the game.
 *
 * This file includes declarations for event handling functions and constants
 * used in the game.
 */

#ifndef EVENT_HANDLER_HEADER
#define EVENT_HANDLER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_events.h>
#include <ncurses.h>
#include "graphics.h"

/**
 * @brief Represents the time interval for player movement.
 *
 * This constant defines the interval (in milliseconds) between consecutive
 * movements of the player in the game.
 */
#define MOVE_INTERVAL 185

/**
 * @brief Represents a function pointer type for event handling.
 *
 * This typedef defines a function pointer type that points to a function
 * handling events in the game.
 */
typedef void (*EventHandlingFunction)(struct GameState *game);

/**
 * @brief Handles events for the console-based version of the game.
 *
 * This function handles events for the console-based version of the game,
 * updating the game state accordingly.
 *
 * @param gameState A pointer to the GameState structure representing the current game state.
 */
void handleEventsConsole(struct GameState *gameState);

/**
 * @brief Handles events for the SDL2-based version of the game.
 *
 * This function handles events for the SDL2-based version of the game,
 * updating the game state accordingly.
 *
 * @param gameState A pointer to the GameState structure representing the current game state.
 */
void handleEventsSDL2(struct GameState *gameState);


#endif 
