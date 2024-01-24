#include "../include/eventHandler.h"

static Uint32 startTime = 0;
static Uint32 currentTime; 
static Uint32 moveInterval;

void handleEventsSDL2(struct GameState *gameState) {
    currentTime = SDL_GetTicks();
    moveInterval = 500;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {  
        if (event.type == SDL_QUIT) {
			gameState->playing = 0;
        }else if (event.type == SDL_KEYDOWN) {
            if (!graphicsContext.player.isMoving) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        graphicsContext.player.isMoving = 1;
                        graphicsContext.player.direction = UP;
                        graphicsContext.player.frameClip = 0;
                        break;
                    case SDLK_DOWN:
                        graphicsContext.player.isMoving = 1;
                        graphicsContext.player.direction = DOWN;
                        graphicsContext.player.frameClip = 0;
                        break;
                    case SDLK_LEFT:
                        graphicsContext.player.isMoving = 1;
                        graphicsContext.player.direction = LEFT;
                        graphicsContext.player.frameClip = 0;
                        break;
                    case SDLK_RIGHT:
                        graphicsContext.player.isMoving = 1;
                        graphicsContext.player.direction = RIGHT;
                        graphicsContext.player.frameClip = 0;
                        break;
                }
            }
        }
    }
    if (graphicsContext.player.isMoving == 1 && ((currentTime - startTime) >= moveInterval)) {
        movePlayer(gameState, graphicsContext.player.direction);
        startTime = currentTime;
        graphicsContext.player.isMoving = 0;
    }
    if (gameState->completedTargets == gameState->totalTargets) {
        gameState->playing = 0;
        printf("VICTORY!\n");
    }
}


void handleEventsConsole(struct GameState *gameState) {
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	int key = getch();

	if (gameState->completedTargets == gameState->totalTargets || gameState->options) {
		switch (key) {
			case 27: {
				gameState->options = 0;
				break;
			}
			case 'R':
			case 'r': {
				restartGame(gameState);
				gameState->options = 0;
				break;
			}
			case 'Q':
			case 'q': {
				gameState->playing = 0;
				break;
			}
			default:
				break;
		}	
	}else {
		switch (key) {
			case 27:{
				gameState->options = 1;
				break;
			}
			case KEY_UP:{
                movePlayer(gameState, UP);
				break; 
			}
			case KEY_DOWN:{
				movePlayer(gameState, DOWN);
				break; 
			}
			case KEY_LEFT:{
				movePlayer(gameState, LEFT);
				break; 
			}
			case KEY_RIGHT:{
				movePlayer(gameState, RIGHT);
				break; 
			}
			default:
				break;
		}
	}
}


