#include "../include/event_handler.h"


void handleEvents(struct GameState *game, Player *player){
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int key = getch();

	if (game->targets_Completed == game->total_targets || game->verify_option) {
		switch (key) {
			case 'R':
			case 'r': {
				restartGame(game);
				*player = initializePlayer(game);
				game->verify_option = 0;
				break;
			}
			case 'Q':
			case 'q': {
				game->playing = 0;
				break;
			}
			case 27: {
				if (game->verify_option) {
					game->verify_option = 0;
				}
				break;

			}
			default:
				break;
		}	
	}else {
		switch (key) {
			case KEY_UP:{
				movePlayer(game, player, UP);
				break; 
			}
			case KEY_DOWN:{
				movePlayer(game, player, DOWN);
				break; 
			}
			case KEY_LEFT:{
				movePlayer(game, player, LEFT);
				break; 
			}
			case KEY_RIGHT:{
				movePlayer(game, player, RIGHT);
				break; 
			}
			case 27:{
				game->verify_option = 1;
				break;
			}
			default:
				break;
		}
	}
}


