#include "../include/graphics.h"
#include <SDL2/SDL_system.h>
#include <ncurses.h>
/*
void getWindow() {
	int width = 1280;
	int height = 720;
	// Création de la fenêtre
	SDL_Window *window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
    return;
	}
	SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


void initializeSDL() {
	int isInitialized = SDL_Init(SDL_INIT_VIDEO);
	if (isInitialized) {
		fprintf(stderr, "Error %s not found\n", gameState.mapPath);
		exit(-1);	
	}
}
*/
void displayConsole(){
	clear();
	int row_index, column_index;
	for(row_index = 0; row_index < gameState.rows; row_index++){
		for(column_index = 0; column_index < gameState.columns; column_index++){
			printw("%c",gameState.levelGrid[row_index][column_index]);
		}
		printw("\n");
	}
	if (gameState.completedTargets == gameState.totalTargets) {
		printw("%d/%d VICTORY!\n", gameState.completedTargets, gameState.totalTargets);
		printw("Restart: R\t Exit: Q\n");
	}else if (gameState.verifyOption) {
		printw("Targets: %d/%d ...PAUSE...\n", gameState.completedTargets, gameState.totalTargets);
		printw("Continue: ESC\nRestart: R\t Exit: Q\n");	
	}else {
		printw("Targets: %d/%d\nOptions: ESC\n", gameState.completedTargets, gameState.totalTargets);
	}
	refresh();
}


