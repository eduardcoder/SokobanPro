#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"  
#include "input.h"

typedef struct Player {
	Location position;
}Player;

extern Player player;

void initializePlayer();
char getCellContent(Location location);
void updateMap(Location currentPosition, Location nextPosition);
int moveBox(Location current, Location next);
void handleNewPosition(Location nextCell, Location cellAfterNew);
void movePlayer(enum Direction direction);

#endif

