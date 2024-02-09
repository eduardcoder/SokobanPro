#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"  

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


void initializePlayer();
char getCellContent(enum CellContent **levelGrid, Location location);
void updateMap(enum CellContent **levelGrid, Location currentPosition, Location nextPosition);
int moveBox(struct GameState *gameState, Location current, Location next);
int handleNewPosition(struct GameState *game, Location nextCell, Location cellAfterNew);
int movePlayer(struct GameState *game, enum Direction direction);

#endif

