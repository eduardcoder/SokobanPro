#include "../include/eventHandler.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

static const Uint8 *keyState;
static Uint32 startTime = 0;
static Uint32 currentTime; 

void handleEventsSDL2(struct GameState *gameState) {
    
    SDL_Event event;
    keyState = SDL_GetKeyboardState(NULL);

    if (gameState->completedTargets == gameState->totalTargets) {
        while (SDL_PollEvent(&event)) {  
            if (event.type == SDL_QUIT) {
                gameState->playing = 0;
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        gameState->playing = 0;
                        break;
                    case SDLK_r:
                        restartGame(gameState);
                        break;
                    case SDLK_f:
                        gameState->fullscreen = (gameState->fullscreen)? 0 : 1;
                        break;                        
                    default:
                        break;
                }
            }
        }
    }else {
        while (SDL_PollEvent(&event)) {  
            if (event.type == SDL_QUIT) {
                gameState->playing = 0;
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        gameState->playing = 0;
                        break;
                    case SDLK_r:
                        restartGame(gameState);
                        break;
                    case SDLK_f:
                        gameState->fullscreen = (gameState->fullscreen)? 0 : 1;
                        break;  
                    default:
                        break;
                }
            }
        }

        if (!graphicsContext.player.isMoving) {
            if (keyState[SDL_SCANCODE_UP]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = UP;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_DOWN]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = DOWN;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_LEFT]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = LEFT;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_RIGHT]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = RIGHT;
                graphicsContext.player.frameClip = 0;
            }
        }

        if (graphicsContext.player.isMoving && ((SDL_GetTicks() - startTime) >= MOVE_INTERVAL)) {
            movePlayer(gameState, graphicsContext.player.direction);
            startTime = currentTime;
            if (keyState[SDL_SCANCODE_UP]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = UP;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_DOWN]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = DOWN;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_LEFT]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = LEFT;
                graphicsContext.player.frameClip = 0;
            }else if (keyState[SDL_SCANCODE_RIGHT]) {
                graphicsContext.player.isMoving = 1;
                startTime = SDL_GetTicks();
                graphicsContext.player.direction = RIGHT;
                graphicsContext.player.frameClip = 0;
            }else {
                graphicsContext.player.isMoving = 0;
            }
        }
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


