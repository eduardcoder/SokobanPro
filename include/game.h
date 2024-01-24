#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 100

#define CHECK_NULL(op)	do {if((op) == NULL) {perror (#op); exit(EXIT_FAILURE);}\
			} while (0)

enum GameMode {
    CONSOLE_MODE,
    GRAPHICS_MODE
};

/**
 * @enum CaseType
 * @brief 
 *
 **/
enum CellContent {
	EMPTY = ' ',
	WALL = '#',
	BOX = '$',
	PLAYER = '@',
	TARGET = 'o',
	BOX_ON_TARGET = '*',
	PLAYER_ON_TARGET = 'a'
};

typedef struct {
	int x;
	int y;
} Location;

/**
 * 0struct GameState
 * @brief 
 * */
struct GameState {
	enum CellContent **levelGrid;
	char* mapPath;
	int rows;
	int columns;
	Location playerPosition;
	int totalTargets;
	int completedTargets;
	int playing;
	int options;
};

enum GameMode getMode(int argc, char *argv[]);
void initializeGame(struct GameState *gameState, char *filePath);
void restartGame(struct GameState *gameState);
int verifyTargets(struct GameState *gameState);
void freeLevel(struct GameState *gameState);


#endif
