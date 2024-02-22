#include "../include/game.h"

enum GameMode getMode(int argc, char *argv[]) {
    enum GameMode mode;
	
    if (argc > 2) {
        fprintf(stderr, "usage: ./sokoban --terminal/graphics <optional>\n");
	    exit(EXIT_FAILURE);
    }else if ((argc > 1) && (strcmp(argv[1], "--console") == 0)) {
	    mode = CONSOLE_MODE;
    }else if ((argc > 1) && (strcmp(argv[1], "--graphics") != 0)) {
        fprintf(stderr, "usage: ./sokoban --terminal/graphics <optional>\n");
	    exit(EXIT_FAILURE);
    }else {
	    mode = GRAPHICS_MODE;
    }
    return mode;
}

void initializeGame(struct GameState *gameState, char *file_path){
	FILE* file = fopen(file_path, "r");
	if (!file) {
		fprintf(stderr, "Error %s not found\n", file_path);
		exit(-1);	
	}
	char line[MAX_LINE_LENGTH] = {0};
	
	fgets(line, MAX_LINE_LENGTH, file);
	sscanf(line, "%d %d %d", &gameState->columns, &gameState->rows, &gameState->totalTargets);
	gameState->completedTargets = 0;
	gameState->mapPath = file_path;
	gameState->options = 0;
	gameState->playing = 1;
    gameState->fullscreen = 0;

	CHECK_NULL(gameState->levelGrid = calloc(gameState->rows, sizeof(enum CellContent*)));
	for (int i = 0; i < gameState->rows; i++) {
		CHECK_NULL(gameState->levelGrid[i] = calloc(gameState->columns, sizeof(enum CellContent)));	
	}

	int currentRow = 0;
	while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
		char* buffer = line;
		int currentColumn = 0;
		while (*buffer && (*buffer != '\n')) {
			gameState->levelGrid[currentRow][currentColumn] = *buffer;
			if (*buffer == PLAYER || *buffer == PLAYER_ON_TARGET) {
				gameState->playerPosition.x = currentColumn;
				gameState->playerPosition.y = currentRow;
			}
			if(*buffer == BOX_ON_TARGET){
				gameState->completedTargets++;
			}
			currentColumn++;
			buffer++;
		}
		currentRow++;
	}
	fclose(file);	
}

void restartGame(struct GameState *gameState) {
	FILE* file = fopen(gameState->mapPath, "r");
	if (!file) {
		fprintf(stderr, "Error %s not found\n", gameState->mapPath);
		exit(-1);	
	}
	char line[MAX_LINE_LENGTH] = {0};
	
	fgets(line, MAX_LINE_LENGTH, file);
	sscanf(line, "%d %d %d", &gameState->columns, &gameState->rows, &gameState->totalTargets);
	gameState->completedTargets = 0;

	int currentRow = 0;
	while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
		char* buffer = line;
		int currentColumn = 0;
		while (*buffer && (*buffer != '\n')) {
			gameState->levelGrid[currentRow][currentColumn] = *buffer;
			if (*buffer == PLAYER || *buffer == PLAYER_ON_TARGET) {
				gameState->playerPosition.x = currentColumn;
				gameState->playerPosition.y = currentRow;
			}
			if(*buffer == BOX_ON_TARGET){
				gameState->completedTargets++;
			}
			currentColumn++;
			buffer++;
		}
		currentRow++;
	}
	fclose(file);	
}

int verifyTargets(struct GameState *gameState) {
	if (gameState->totalTargets == gameState->completedTargets){
		return 1;
	}else {
		return 0;
	}
}

void freeLevel(struct GameState *gameState){
	for(int index = 0; index < gameState->rows; index++){
		free(gameState->levelGrid[index]);
	}
	free(gameState->levelGrid);
}


