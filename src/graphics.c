#include "../include/graphics.h"
#include <stdio.h>

GraphicsContext graphicsContext;
static float frameTime = 0;
static Uint32 startTime = 0;
static Uint32 currentTime = 0;
double yAnimation;
double xAnimation;


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

void initializeTexts(){
    graphicsContext.texts->victory = makeVictoryText("VICTORY");
    graphicsContext.texts->quit = makeText("Quit: Q", TEXTURE_WIDTH/4);
    graphicsContext.texts->restart = makeText("Restart: R", strlen("Quit: Q ")*(TEXTURE_WIDTH/4));
    graphicsContext.texts->fullscreen = makeText("Full: F", strlen("Quit: Q Restart: R")*(TEXTURE_WIDTH/4));
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

void SDL_ErrorExit(const char *section, const char *error){
    SDL_Log("ERROR: %s %s\n",section, error);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void initializeSDL() {
	int isInitialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (isInitialized != 0) {
	    SDL_ErrorExit("SDL_Init", SDL_GetError());	
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_ErrorExit("IMG_Init", IMG_GetError());
    }
    if (TTF_Init() == -1) {
        SDL_ErrorExit("TTF_Init", TTF_GetError());    
    }

	SDL_Window *window = SDL_CreateWindow(
        "Sokoban",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DEFAULT_SCREEN_WIDTH,
        DEFAULT_SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
	if (window == NULL) {
        SDL_ErrorExit("SDL_Window", SDL_GetError()); 
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_ErrorExit("SDL_Renderer", SDL_GetError()); 
    }
    
    SDL_Texture *gameTexture = loadTexture(renderer, "assets/sokoban_tilesheet@2.png");

    TTF_Font *openedFont = TTF_OpenFont("assets/terminal-dosis-extrabold.ttf", 60);
    if (openedFont == NULL) {
        TTF_CloseFont(openedFont);
        SDL_Quit();
        SDL_DestroyWindow(window);    
        SDL_ErrorExit("SDL_Renderer", SDL_GetError()); 
    }
    Texts *textAllocation;
    CHECK_NULL(textAllocation = (Texts*)calloc(1, sizeof(Texts)));

    graphicsContext = (GraphicsContext){
        .window = window,
        .renderer = renderer,
        .width = DEFAULT_SCREEN_WIDTH,
        .height = DEFAULT_SCREEN_HEIGHT,
        .gameTexture = gameTexture,
        .font = openedFont,
        .texts = textAllocation
    }; 
    initializeSprites();
    initializeTexts();
}

void destroysTextsTextures(Texts *texts){
    SDL_DestroyTexture(texts->name.texture);
    SDL_DestroyTexture(texts->quit.texture);
    SDL_DestroyTexture(texts->victory.texture);
    SDL_DestroyTexture(texts->restart.texture);
    SDL_DestroyTexture(texts->fullscreen.texture);
}

void finalizeSDL() {
    destroysTextsTextures(graphicsContext.texts);
    free(graphicsContext.texts);
    SDL_DestroyTexture(graphicsContext.gameTexture);
    SDL_DestroyRenderer(graphicsContext.renderer);
    SDL_DestroyWindow(graphicsContext.window);
    TTF_CloseFont(graphicsContext.font);    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Text makeText(const char *text, int x){
    Text editedText;
    SDL_Color white = {255, 255, 255, 255};
    int textWidth, textHeight, y;
    float scale = 0.5;

    SDL_Surface *surface = TTF_RenderText_Blended(graphicsContext.font, text, white);
    editedText.texture = SDL_CreateTextureFromSurface(graphicsContext.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(editedText.texture, NULL, NULL, &textWidth, &textHeight);
    textWidth *= scale;
    textHeight *= scale;
    if (x>=0) {
        x -= textWidth/2;
        if ((x+textWidth)>graphicsContext.width) {
            x -= textWidth;        
        }else if (x<0) {
            x += textWidth;        
        }
    }
    y = textHeight / 4;
    editedText.destination = (SDL_Rect){x, y, textWidth, textHeight};
    
    return editedText;
}

Text makeVictoryText(const char *text){
    Text victory;
    SDL_Color white = {255, 255, 255, 255};
    int textWidth, textHeight, x, y;
    float scale = 2.5;
    
    SDL_Surface *surface = TTF_RenderText_Blended(graphicsContext.font, text, white);
    victory.texture = SDL_CreateTextureFromSurface(graphicsContext.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(victory.texture, NULL, NULL, &textWidth, &textHeight);
    textWidth *= scale;
    textHeight *= scale;
    x = (DEFAULT_SCREEN_WIDTH - textWidth) / 2;
    y = (DEFAULT_SCREEN_HEIGHT - textHeight) / 2;
    victory.destination = (SDL_Rect){x, y, textWidth, textHeight };

    return victory;
}

void updateRenderTexts(struct GameState *game){
    SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->quit.texture, NULL, &graphicsContext.texts->quit.destination);
    SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->restart.texture, NULL, &graphicsContext.texts->restart.destination);
    SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->fullscreen.texture, NULL, &graphicsContext.texts->fullscreen.destination);
    char targets[TARGETS_CHAR_SIZE];
    
    if (!graphicsContext.texts->name.texture) {
        graphicsContext.texts->name = makeText(game->mapPath, graphicsContext.width);
    }
    graphicsContext.texts->name.destination.x = graphicsContext.width - (graphicsContext.texts->name.destination.w * 1.3);
    SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->name.texture, NULL, &graphicsContext.texts->name.destination);

    snprintf(targets, TARGETS_CHAR_SIZE, "Targets: %2d/%2d", game->completedTargets, game->totalTargets);
    graphicsContext.texts->targets = makeText(
        targets, graphicsContext.width / 2
    );
    SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->targets.texture, NULL, &graphicsContext.texts->targets.destination);
    SDL_DestroyTexture(graphicsContext.texts->targets.texture);
    if (game->completedTargets == game->totalTargets) {
        graphicsContext.texts->victory.destination.x = (graphicsContext.width - graphicsContext.texts->victory.destination.w) / 2;        
        graphicsContext.texts->victory.destination.y = (graphicsContext.height - graphicsContext.texts->victory.destination.h) / 2;        
        SDL_RenderCopy(graphicsContext.renderer, graphicsContext.texts->victory.texture, NULL, &graphicsContext.texts->victory.destination);
    }
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

int verifierWall(struct GameState *game){
    int nextY = game->playerPosition.y;
    int nextX = game->playerPosition.x;
    int afterNextY = game->playerPosition.y;
    int afterNextX = game->playerPosition.x;
    switch (graphicsContext.player.direction) {
        case UP:
            nextY -= 1;
            afterNextY -= 2;
            break;
        case DOWN:
            nextY += 1;
            afterNextY += 2;
            break;
        case LEFT:
            nextX -= 1;
            afterNextX -= 2;
            break;
        case RIGHT:
            nextX += 1;
            afterNextX += 2;
            break;
    }

    int currentCell = game->levelGrid[nextY][nextX];
    int nextCell;

    switch (currentCell) {
        case WALL:
            return 1;
        case BOX_ON_TARGET:
        case BOX:
            nextCell = game->levelGrid[afterNextY][afterNextX];
            return (nextCell == BOX || nextCell == BOX_ON_TARGET || nextCell == WALL);
        default:
            return 0;
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

void playerAnimation(struct GameState *game, float movement){
    int yPosition = game->playerPosition.y + 1;
    int xPosition = game->playerPosition.x;
    int clipIndex = graphicsContext.player.frameClip;
    Location sourcePosition = {.x = 0, .y = 0};

    if (graphicsContext.player.isMoving && !verifierWall(game)) {
        switch (graphicsContext.player.direction) {
            case UP:
                yAnimation -= movement;
                sourcePosition = graphicsContext.player.spriteUpClips[clipIndex];
                break;
            case DOWN:
                yAnimation += movement;
                sourcePosition = graphicsContext.player.spriteDownClips[clipIndex];
                break;
            case RIGHT:
                xAnimation += movement;
                sourcePosition = graphicsContext.player.spriteRightClips[clipIndex];
                break;
            case LEFT:
                xAnimation -= movement;
                sourcePosition = graphicsContext.player.spriteLeftClips[clipIndex];
                break;
            default:
                break;
        }    
        graphicsContext.player.sourceSprite = (SDL_Rect){sourcePosition.x * TEXTURE_WIDTH, sourcePosition.y * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        graphicsContext.player.destinationRender = (SDL_Rect){xAnimation, yAnimation, TEXTURE_WIDTH, TEXTURE_HEIGHT};
    }else {
        yAnimation = yPosition * TEXTURE_HEIGHT;
        xAnimation = xPosition * TEXTURE_WIDTH;
        graphicsContext.player.sourceSprite = (SDL_Rect){0 * TEXTURE_WIDTH, 5 * TEXTURE_HEIGHT, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        graphicsContext.player.destinationRender = (SDL_Rect){xAnimation, yAnimation, TEXTURE_WIDTH, TEXTURE_HEIGHT};
        
    }
}

void displaySDL(struct GameState *game){    
    int offSetX = 0;
    int offSetY = 0;
    int offSetW = DEFAULT_SCREEN_WIDTH;
    int offSetH = DEFAULT_SCREEN_HEIGHT;
    if (game->fullscreen) {
        SDL_SetWindowFullscreen(graphicsContext.window, SDL_WINDOW_FULLSCREEN);
        SDL_GetWindowSize(graphicsContext.window, &graphicsContext.width, &graphicsContext.height);
        offSetW = graphicsContext.width;
        offSetH = graphicsContext.height;
        SDL_RenderSetLogicalSize(graphicsContext.renderer, graphicsContext.width, graphicsContext.height);
    }else {
        SDL_SetWindowFullscreen(graphicsContext.window, 0);
        offSetW = DEFAULT_SCREEN_WIDTH;
        offSetH = DEFAULT_SCREEN_HEIGHT;
        graphicsContext.width = DEFAULT_SCREEN_WIDTH;
        graphicsContext.height = DEFAULT_SCREEN_HEIGHT;
    }

    if (game->columns < MIN_BLOCKS_WIDTH ) {
        offSetX = ((MIN_BLOCKS_WIDTH - game->columns)/2)*(offSetW/MIN_BLOCKS_WIDTH);
        offSetW -= (offSetX * 2);
    }
    if (game->rows < MIN_BLOCKS_HEIGHT) {
        offSetY = ((MIN_BLOCKS_HEIGHT - game->rows) / 2)*(offSetH/MIN_BLOCKS_HEIGHT);
        offSetH -= (offSetY * 2);
    }
    SDL_Rect viewport = {offSetX, offSetY, offSetW, offSetH};

    double scaleX = (double)offSetW/((game->columns) * TEXTURE_WIDTH);
    double scaleY = (double)offSetH/((game->rows + 1) * TEXTURE_HEIGHT);
    float movement = 0;
    float deltaTime;

    currentTime = SDL_GetTicks();

    graphicsContext.player.frameClip = (currentTime/90 % 4);

    frameTime = currentTime - startTime;
    if (frameTime < 1000.0 / FPS) {
        SDL_Delay((1000.0 / FPS) - frameTime);
    }

    if (frameTime >= 1000.0 / FPS) {
        deltaTime = frameTime / 1000.0;
        movement = SPEED * deltaTime;

        playerAnimation(game, movement);
        SDL_RenderSetViewport(graphicsContext.renderer, &viewport);
        SDL_RenderClear(graphicsContext.renderer);
        SDL_SetRenderDrawColor(graphicsContext.renderer, 0, 0, 0, 255);
        SDL_RenderSetScale(graphicsContext.renderer, scaleX, scaleY);
        renderMap(game);
        renderEntities(game);
        SDL_RenderSetScale(graphicsContext.renderer, 1.0, 1.0);
        SDL_RenderSetViewport(graphicsContext.renderer, NULL);
        updateRenderTexts(game);
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


