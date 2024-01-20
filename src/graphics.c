#include "../include/graphics.h"
#include <ncurses.h>

SDLContext context;

/*
void initializeSDL(){
	int const width = 1280;
	int const height = 720;
	context = (SDLContext){NULL, NULL, .width = 0, .height = 0};
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return;	
	}
}
*/

void displayConsole(struct GameState *game){
	clear();
	int row_index, column_index;
	for(row_index = 0; row_index < game->rows; row_index++){
		for(column_index = 0; column_index < game->columns; column_index++){
			printw("%c",game->game_grid[row_index][column_index]);
		}
		printw("\n");
	}
	if (game->targets_Completed == game->total_targets) {
		printw("%d/%d VICTORY!\n", game->targets_Completed, game->total_targets);
		printw("Restart: R\t Exit: Q\n");
	}else if (game->verify_option) {
		printw("Targets: %d/%d ...PAUSE...\n", game->targets_Completed, game->total_targets);
		printw("Continue: ESC\nRestart: R\t Exit: Q\n");	
	}else {
		printw("Targets: %d/%d\nOptions: ESC\n", game->targets_Completed, game->total_targets);
	}
	refresh();
}


