#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH 100
#define CHECK_NULL(op)	do {if((op) == NULL) {perror (#op); exit(EXIT_FAILURE);}\
			} while (0)

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

/**
 * 0struct GameState
 * @brief 
 * */
struct GameState {
	enum CellContent** game_grid;
	char* map_path;
	int rows;
	int columns;
	int playerX;
	int playerY;
	int total_targets;
	int targets_Completed;
	int playing;
	int verify_option;
};


void initializeGame(struct GameState* game, char* file_path);
void restartGame(struct GameState* game);
int verifyTargets(struct GameState* game);
void freeLevel(struct GameState* game);


#endif
