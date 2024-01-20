#include "../include/game.h"

void initializeGame(struct GameState *game, char* file_path){
	int columns, rows;
	FILE* file = fopen(file_path, "r");
	if (!file) {
		fprintf(stderr, "Error %s not found\n", file_path);
		exit(-1);	
	}
	char line[MAX_LINE_LENGTH] = {0};
	
	fgets(line, MAX_LINE_LENGTH, file);
	sscanf(line, "%d %d %d", &columns, &rows, &game->total_targets);
	game->targets_Completed = 0;
	game->rows = rows;
	game->columns = columns;
	game->map_path = file_path;
	game->verify_option = 0;

	CHECK_NULL(game->game_grid = calloc(rows, sizeof(enum CellContent*)));
	for (int i = 0; i < rows; i++) {
		CHECK_NULL(game->game_grid[i] = calloc(columns, sizeof(enum CellContent)));	
	}

	int current_row = 0;
	while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
		char* buffer = line;
		int current_column = 0;
		while (*buffer && (*buffer != '\n')) {
			game->game_grid[current_row][current_column] = *buffer;
			if (*buffer == PLAYER || *buffer == PLAYER_ON_TARGET) {
				game->playerX = current_column;
				game->playerY = current_row;
			}
			if(*buffer == BOX_ON_TARGET){
				game->targets_Completed++;
			}
			current_column++;
			buffer++;
		}
		current_row++;
	}
	fclose(file);	
}

void restartGame(struct GameState* game) {
	int columns, rows;
	FILE* file = fopen(game->map_path, "r");
	if (!file) {
		fprintf(stderr, "Error %s not found\n", game->map_path);
		exit(-1);	
	}
	char line[MAX_LINE_LENGTH] = {0};
	
	fgets(line, MAX_LINE_LENGTH, file);
	sscanf(line, "%d %d %d", &columns, &rows, &game->total_targets);
	game->targets_Completed = 0;

	int current_row = 0;
	while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
		char* buffer = line;
		int current_column = 0;
		while (*buffer && (*buffer != '\n')) {
			game->game_grid[current_row][current_column] = *buffer;
			if (*buffer == PLAYER || *buffer == PLAYER_ON_TARGET) {
				game->playerX = current_column;
				game->playerY = current_row;
			}
			if(*buffer == BOX_ON_TARGET){
				game->targets_Completed++;
			}
			current_column++;
			buffer++;
		}
		current_row++;
	}
	fclose(file);	
}

int verifyTargets(struct GameState* game) {
	if (game->total_targets == game->targets_Completed){
		return 1;
	}else {
		return 0;
	}
}

void freeLevel(struct GameState* game){
	for(int index = 0; index < game->rows; index++){
		free(game->game_grid[index]);
	}
	free(game->game_grid);
}


