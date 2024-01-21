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
	const char *modeByDefault = "--graphics";
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
		mode = modeByDefault;
	}

	printf("Mode: %s\n", mode);
	char levelPath[] = "../maps/level1.txt";

	initializeGame(levelPath);
	initializePlayer();

	//initialize window ncurses
	initscr();

	while(gameState.playing){
		displayConsole();
		handleEvents();
	}
	clear();
	endwin();

	freeLevel();
	

	return EXIT_SUCCESS;
}
