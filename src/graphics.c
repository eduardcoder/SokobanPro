#include "../include/graphics.h"
#include <stdio.h>

GraphicsContext graphicsContext;
static float frameTime = 0;
static Uint32 startTime = 0;
static Uint32 currentTime = 0;
static int times = 0;


void SDL_ErrorExit(const char *section, const char *error){
    SDL_Log("ERROR: %s %s\n",section, error);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void initializeSprites(){
    graphicsContext.player.spriteUpClips[0] = (Location){4,4};
    graphicsContext.player.spriteUpClips[1] = (Location){3,4};
    graphicsContext.player.spriteUpClips[2] = (Location){5,4};
    graphicsContext.player.spriteUpClips[3] = (Location){3,4};
    graphicsContext.player.spriteLeftClips[0] = (Location){4,6};
    graphicsContext.player.spriteLeftClips[1] = (Location){3,6};
    graphicsContext.player.spriteLeftClips[2] = (Location){5,6};
    graphicsContext.player.spriteLeftClips[3] = (Location){3,6};
    graphicsContext.player.spriteDownClips[0] = (Location){1,4};
    graphicsContext.player.spriteDownClips[1] = (Location){0,4};
    graphicsContext.player.spriteDownClips[2] = (Location){2,4};
    graphicsContext.player.spriteDownClips[3] = (Location){0,4};
    graphicsContext.player.spriteRightClips[0] = (Location){1,6};
    graphicsContext.player.spriteRightClips[1] = (Location){0,6};
    graphicsContext.player.spriteRightClips[2] = (Location){2,6};
    graphicsContext.player.spriteRightClips[3] = (Location){0,6};
}

SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *filePath) {
    SDL_Surface *surface = IMG_Load(filePath);
    if (!surface) {
        fprintf(stderr, "ERROR: loading %s: %s\n", filePath, IMG_GetError());
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void initializeSDL() {
	int isInitialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (isInitialized != 0) {
	    SDL_ErrorExit("SDL_Init", SDL_GetError());	
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_ErrorExit("IMG_Init", IMG_GetError());
    }

	SDL_Window *window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN);
	if (window == NULL) {
        SDL_ErrorExit("SDL_Window", SDL_GetError()); 
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_ErrorExit("SDL_Renderer", SDL_GetError()); 
    }
    
    SDL_Texture *gameTexture = loadTexture(renderer, "../assets/sokoban_tilesheet@2.png");
    initializeSprites();

    graphicsContext = (GraphicsContext){
        .window = window, .renderer = renderer, .width = DEFAULT_SCREEN_WIDTH, .height = DEFAULT_SCREEN_HEIGHT, .gameTexture = gameTexture
        }; 
}


void finalizeSDL() {
    SDL_DestroyTexture(graphicsContext.gameTexture);
    SDL_DestroyRenderer(graphicsContext.renderer);
    SDL_DestroyWindow(graphicsContext.window);
    IMG_Quit();
    SDL_Quit();
}

void renderMap(struct GameState *game) {
    SDL_Rect sourceRect;  
    SDL_Rect destinationRect;
    int rowIndex, columnIndex;

	for(rowIndex = 1; rowIndex <= game->rows; rowIndex++){
		for(columnIndex = 0; columnIndex < game->columns; columnIndex++){
            sourceRect = (SDL_Rect){12 * TEXTURE_WIDTH, 6 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
            destinationRect.x = columnIndex * TEXTURE_WIDTH;
            destinationRect.y = rowIndex * TEXTURE_HEIGHT;
            destinationRect.w = TEXTURE_WIDTH;
            destinationRect.h = TEXTURE_HEIGHT;
            SDL_RenderCopy(graphicsContext.renderer, graphicsContext.gameTexture, &sourceRect, &destinationRect);

            char tileType = game->levelGrid[rowIndex-1][columnIndex];
            switch (tileType) {
                case WALL:
                    sourceRect = (SDL_Rect){6 * TEXTURE_WIDTH, 7 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
                    break;
                case PLAYER_ON_TARGET:
                case BOX_ON_TARGET:
                case TARGET:
                    sourceRect = (SDL_Rect){11 * TEXTURE_WIDTH, 4 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
                    break;
                default: 
                    continue;
            }
            destinationRect.x = columnIndex * TEXTURE_WIDTH;
            destinationRect.y = rowIndex * TEXTURE_HEIGHT;
            destinationRect.w = TEXTURE_WIDTH;
            destinationRect.h = TEXTURE_HEIGHT;
            SDL_RenderCopy(graphicsContext.renderer, graphicsContext.gameTexture, &sourceRect, &destinationRect);
        }
    }
}

void renderEntities(struct GameState *game) {
    SDL_Rect sourceRect;  
    SDL_Rect destinationRect;
    int rowIndex, columnIndex;

	for(rowIndex = 1; rowIndex <= game->rows; rowIndex++){
		for(columnIndex = 0; columnIndex < game->columns; columnIndex++){
            char tileType = game->levelGrid[rowIndex-1][columnIndex];
            switch (tileType) {
                case PLAYER_ON_TARGET:
                case PLAYER:
                    sourceRect = graphicsContext.player.sourceSprite;
                    destinationRect = graphicsContext.player.destinationRender;
                    break;
                case BOX_ON_TARGET:
                    sourceRect = (SDL_Rect){8 * TEXTURE_WIDTH, 4 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
                    destinationRect.x = columnIndex * TEXTURE_WIDTH;
                    destinationRect.y = rowIndex * TEXTURE_HEIGHT;
                    destinationRect.w = TEXTURE_WIDTH;
                    destinationRect.h = TEXTURE_HEIGHT;
                    break;
                case BOX:
                    sourceRect = (SDL_Rect){8 * TEXTURE_WIDTH, 0 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
                    destinationRect.x = columnIndex * TEXTURE_WIDTH;
                    destinationRect.y = rowIndex * TEXTURE_HEIGHT;
                    destinationRect.w = TEXTURE_WIDTH;
                    destinationRect.h = TEXTURE_HEIGHT;
                    break;
                default: 
                    continue;
            }
            SDL_RenderCopy(graphicsContext.renderer, graphicsContext.gameTexture, &sourceRect, &destinationRect);
        }
    }
}

void playerAnimation(Location playerPosition, float movement){
    double yPosition = (double)playerPosition.y + 1;
    double xPosition = (double)playerPosition.x;
    int clipIndex = graphicsContext.player.frameClip;
    Location sourcePosition;

    if (graphicsContext.player.isMoving) {
        switch (graphicsContext.player.direction) {
            case UP:
                yPosition = (yPosition * TEXTURE_HEIGHT) + movement;
                xPosition = xPosition * TEXTURE_WIDTH;
                sourcePosition = graphicsContext.player.spriteUpClips[clipIndex];
                break;
            case DOWN:
                yPosition = (yPosition * TEXTURE_HEIGHT) - movement;
                xPosition = xPosition * TEXTURE_WIDTH;
                sourcePosition = graphicsContext.player.spriteDownClips[clipIndex];
                break;
            case RIGHT:
                xPosition = (xPosition * TEXTURE_WIDTH) + movement;
                yPosition = yPosition * TEXTURE_HEIGHT;
                sourcePosition = graphicsContext.player.spriteRightClips[clipIndex];
                break;
            case LEFT:
                xPosition = (xPosition * TEXTURE_WIDTH) - movement;
                yPosition = yPosition * TEXTURE_HEIGHT;
                sourcePosition = graphicsContext.player.spriteLeftClips[clipIndex];
                break;
            default:
                break;
        }    
        printf("(%f,%f) \n",yPosition, xPosition );
        graphicsContext.player.sourceSprite = (SDL_Rect){sourcePosition.x * TEXTURE_WIDTH, sourcePosition.y * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        graphicsContext.player.destinationRender = (SDL_Rect){xPosition, yPosition, TEXTURE_WIDTH, TEXTURE_HEIGHT};
    }else {
        /*
        //printf("y:%f ",yPosition);
        yPosition = (yPosition) - (double)MOVE_SPEED;
        //printf("y:%f ",yPosition);
        graphicsContext.player.destinationRender = (SDL_Rect){xPosition * TEXTURE_WIDTH, yPosition * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        graphicsContext.player.sourceSprite = (SDL_Rect){sourcePosition.x * TEXTURE_WIDTH, sourcePosition.y * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        /*/
        graphicsContext.player.sourceSprite = (SDL_Rect){0 * TEXTURE_WIDTH, 5 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        graphicsContext.player.destinationRender = (SDL_Rect){xPosition * TEXTURE_WIDTH, yPosition * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        
    }
}

void displaySDL(struct GameState *game){
    double scaleX = (double)graphicsContext.width/(game->columns * TEXTURE_WIDTH);
    double scaleY = (double)graphicsContext.height/((game->rows +1) * TEXTURE_HEIGHT);
    float movement;
    float deltaTime;

    currentTime = SDL_GetTicks();

    frameTime = currentTime - startTime;
    if (frameTime < 1000.0 / FPS) {
        SDL_Delay((1000.0 / FPS) - frameTime);
    }

    if (frameTime >= 1000.0 / FPS) {
        deltaTime = frameTime / 1000.0;
        movement = SPEED * deltaTime;
        
        times += 15; 
        if(times == FPS){
            times = 0;
            graphicsContext.player.frameClip = (graphicsContext.player.frameClip + 1) % 4;
        }
        playerAnimation(game->playerPosition, movement);
        SDL_RenderClear(graphicsContext.renderer);
        SDL_SetRenderDrawColor(graphicsContext.renderer, 0, 0, 0, 255);
        SDL_RenderSetScale(graphicsContext.renderer, scaleX, scaleY);
        renderMap(game);
        renderEntities(game);
        SDL_RenderSetScale(graphicsContext.renderer, 1.0, 1.0);
        SDL_RenderPresent(graphicsContext.renderer); 
        startTime = SDL_GetTicks();
    }

}

void initializeNCurses() {
	initscr();
	//start_color();
}

void displayConsole(struct GameState *game){
	clear();
	int rowIndex, columnIndex;
	for(rowIndex = 0; rowIndex < game->rows; rowIndex++){
		for(columnIndex = 0; columnIndex < game->columns; columnIndex++){
			printw("%c",game->levelGrid[rowIndex][columnIndex]);
		}
		printw("\n");
	}
	if (game->completedTargets == game->totalTargets) {
		printw("%d/%d VICTORY!\n", game->completedTargets, game->totalTargets);
		printw("Restart: R\t Exit: Q\n");
	}else if (game->options) {
		printw("Targets: %d/%d ...PAUSE...\n", game->completedTargets, game->totalTargets);
		printw("Continue: ESC\nRestart: R\t Exit: Q\n");	
	}else {
		printw("Targets: %d/%d\nOptions: ESC\n", game->completedTargets, game->totalTargets);
	}
	refresh();
}


