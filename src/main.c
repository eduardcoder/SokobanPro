#include "../include/graphics.h"
#include "../include/eventHandler.h"
#include <stdio.h>

void usage(char *argv0){
	fprintf(stderr, "usage: %s --terminal/graphics <optional>\n", argv0);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	if (argc > 2) {
	    usage(argv[0]);			
	}
    DisplayFunction handleDisplay;
    EventHandlingFunction handleEvent;
	enum GameMode mode = getMode(argc, argv);
    struct GameState game;
	char levelPath[] = "maps/level1.txt";

	initializeGame(&game, levelPath);
	//initializePlayer();

	if (mode == CONSOLE_MODE) {
        handleEvent = handleEventsConsole;
        handleDisplay = displayConsole;
		initializeNCurses();
	}else {
        handleEvent = handleEventsSDL2;
        handleDisplay = displaySDL;
	    initializeSDL();
	}
	//initialize window ncurses

	while(game.playing){
		handleDisplay(&game);
		handleEvent(&game);
	}

	if (mode == CONSOLE_MODE) {
		clear();
		endwin();
	}else {
	    finalizeSDL();
	}

	freeLevel(&game);

	return EXIT_SUCCESS;
}
