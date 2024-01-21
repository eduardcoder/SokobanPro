#include "../include/event_handler.h"


void handleEvents(){
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int key = getch();

	if (gameState.completedTargets == gameState.totalTargets || gameState.verifyOption) {
		switch (key) {
			case 27: {
				if (gameState.verifyOption) {
					gameState.verifyOption = 0;
				}
				break;
			}
			case 'R':
			case 'r': {
				restartGame();
				initializePlayer();
				gameState.verifyOption = 0;
				break;
			}
			case 'Q':
			case 'q': {
				gameState.playing = 0;
				break;
			}
			default:
				break;
		}	
	}else {
		switch (key) {
			case 27:{
				gameState.verifyOption = 1;
				break;
			}
			case KEY_UP:{
				movePlayer(UP);
				break; 
			}
			case KEY_DOWN:{
				movePlayer(DOWN);
				break; 
			}
			case KEY_LEFT:{
				movePlayer(LEFT);
				break; 
			}
			case KEY_RIGHT:{
				movePlayer(RIGHT);
				break; 
			}
			default:
				break;
		}
	}
}


