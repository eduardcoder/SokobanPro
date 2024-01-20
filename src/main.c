#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "../include/graphics.h"
#include "../include/event_handler.h"

void usage(char *argv0){
	fprintf(stderr, "usage: %s --terminal/graphics <optional>\n", argv0);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	const char *mode_by_default = "--graphics";
	const char *mode;

	if (argc > 2) {
	        usage(argv[0]);			
	}
	if (argc > 1) {
		if (strcmp(argv[1], "--terminal") == 0) {
			mode = "--terminal";
		} else if (strcmp(argv[1], "--graphics") == 0) {
			mode = "--graphics";
		} else {
			usage(argv[0]);
		}
	} else {
		mode = mode_by_default;
	}

	printf("Mode: %s\n", mode);
	char level_path[] = "../maps/level1.txt";

	struct GameState game_state;
	initializeGame(&game_state, level_path);
	Player player = initializePlayer(&game_state);
	game_state.playing = 1;

	//initialize window ncurses
	initscr();

	while(game_state.playing){
		displayConsole(&game_state);
		handleEvents(&game_state, &player);
	}

	endwin();

	freeLevel(&game_state);
	

	return EXIT_SUCCESS;
}
