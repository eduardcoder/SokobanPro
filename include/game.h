#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

/**
 * @enum CaseType
 * @brief 
 *
 **/
enum CellContent {
	EMPTY = ' ',
	WALL = '#',
	BOX = '*',
	PLAYER = '@',
	TARGET = 'o',
	BOX_ON_TARGET = '.',
	PLAYER_ON_TARGET = '+'
};

/**
 * 0struct GameGrid
 * @brief 
 * */
struct GameGrid {
	enum CellContent** game_grid;
	int columns;
	int rows;
};


struct GameState {
	struct GameGrid grid;
	int playerX;
	int playerY;
	int total_targets;
	int targets_Completed;
};


void initializeGame(struct GameState* game, int rows, int columns, int totalTargets);
void updateGame(struct GameState* game);
void renderGame(struct GameState* game, SDL_Renderer* renderer);
void freeLevel(struct GameState* game)


#endif
