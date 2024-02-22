/**
 * @file player.h
 * @brief Defines functions and structures related to the game player. 
 * This file manages player actions in the game, checking the feasibility 
 * of player movements and pushing boxes.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"  

/**
 * @enum Direction 
 * @brief Represents the possible directions the player can move.
 */
enum Direction {
    UP,     /**< Move up */
    DOWN,   /**< Move down */
    LEFT,   /**< Move left */
    RIGHT   /**< Move right */
};

/**
 * @brief Initializes the player in the game.
 */
void initializePlayer();

/**
 * @brief Gets the content of the cell at the specified location in the level grid.
 * 
 * @param levelGrid The 2D array representing the level grid.
 * @param location The location of the cell.
 * @return The content of the cell at the specified location.
 */
char getCellContent(enum CellContent **levelGrid, Location location);

/**
 * @brief Updates the map after the player's movement.
 * 
 * @param levelGrid The 2D array representing the level grid.
 * @param currentPosition The current position of the player.
 * @param nextPosition The next position the player is moving to.
 */
void updateMap(enum CellContent **levelGrid, Location currentPosition, Location nextPosition);

/**
 * @brief Moves a box in the game.
 * 
 * @param gameState The current state of the game.
 * @param current The current location of the box.
 * @param next The location to which the box is being moved.
 * @return 1 if the box is moved successfully, 0 otherwise.
 */
int moveBox(struct GameState *gameState, Location current, Location next);

/**
 * @brief Handles the new position after the player's movement.
 * 
 * @param game The current state of the game.
 * @param nextCell The location the player is moving to.
 * @param cellAfterNew The location the player will be after the movement.
 */
void handleNewPosition(struct GameState *game, Location nextCell, Location cellAfterNew);

/**
 * @brief Moves the player in the specified direction.
 * 
 * @param game The current state of the game.
 * @param direction The direction in which the player is moving.
 */
void movePlayer(struct GameState *game, enum Direction direction);

#endif /* PLAYER_H */

