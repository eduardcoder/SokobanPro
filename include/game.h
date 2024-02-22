/**
 * @file game.h
 * @brief Header file containing declarations related to the game functionality.
 *
 * This file includes declarations for enums, structs, and functions
 * related to the game's functionality.
 */

#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 100

#define CHECK_NULL(op)	do {if((op) == NULL) {perror (#op); exit(EXIT_FAILURE);}\
			} while (0)

/**
 * @enum GameMode
 * @brief Represents different modes of the game (console or graphics).
 */
enum GameMode {
    CONSOLE_MODE,   /**< Console mode. */
    GRAPHICS_MODE   /**< Graphics mode. */
};

/**
 * @enum CellContent
 * @brief Enumerates possible content types for each cell in the game.
 */
enum CellContent {
    EMPTY = ' ',            /**< Empty cell. */
    WALL = '#',             /**< Wall cell. */
    BOX = '$',              /**< Box cell. */
    PLAYER = '@',           /**< Player cell. */
    TARGET = 'o',           /**< Target cell. */
    BOX_ON_TARGET = '*',    /**< Box on target cell. */
    PLAYER_ON_TARGET = 'a'  /**< Player on target cell. */
};

/**
 * @struct Location
 * @brief Represents a 2D coordinate (x, y) in the game grid.
 */
typedef struct {
    int x;  /**< X-coordinate. */
    int y;  /**< Y-coordinate. */
} Location;

/**
 * @struct GameState
 * @brief Represents the current state of the game.
 */
struct GameState {
    enum CellContent **levelGrid;  /**< 2D array representing the game grid. */
    char *mapPath;                 /**< Path to the game map file. */
    int rows;                      /**< Number of rows in the game grid. */
    int columns;                   /**< Number of columns in the game grid. */
    Location playerPosition;       /**< Current player position. */
    int totalTargets;              /**< Total number of targets in the game. */
    int completedTargets;          /**< Number of targets completed by the player. */
    int playing;                   /**< Flag indicating whether the game is in progress. */
    int options;                   /**< Flag indicating whether to show options on the screen. */
    int fullscreen;                /**< Flag indicating whether the game is in fullscreen mode. */
};

/**
 * @brief Obtains the game mode based on command line arguments.
 *
 * This function parses command line arguments to determine the game mode.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * 
 * @return The GameMode enum representing the selected game mode.
 */
enum GameMode getMode(int argc, char *argv[]);

/**
 * @brief Initializes the game state using the specified file.
 *
 * This function initializes the game state structure using the information
 * stored in the specified file.
 *
 * @param gameState A pointer to the GameState structure to be initialized.
 * @param filePath The path to the file containing the game state information.
 */
void initializeGame(struct GameState *gameState, char *filePath);

/**
 * @brief Restarts the game by resetting the game state.
 *
 * This function resets the provided game state structure, allowing the game
 * to start anew.
 *
 * @param gameState A pointer to the GameState structure to be restarted.
 */
void restartGame(struct GameState *gameState);

/**
 * @brief Verifies if all targets have been completed in the current game state.
 *
 * This function checks whether all targets in the provided game state have
 * been successfully completed. If all targets are completed, the function returns 1;
 * otherwise, it returns 0.
 *
 * @param gameState A pointer to the GameState structure to be checked for target completion.
 *
 * @return 1 if all targets are completed, 0 otherwise.
 */int verifyTargets(struct GameState *gameState);

/**
 * @brief Frees the resources associated with the game level.
 *
 * This function releases any dynamically allocated memory or resources
 * associated with the game level in the provided game state structure.
 *
 * @param gameState A pointer to the GameState structure to free the level resources.
 */
void freeLevel(struct GameState *gameState);


#endif /* GAME_H */
