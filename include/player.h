#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"  
#include "input.h"

typedef struct {
	int x;
	int y;
} Location;

typedef struct Player {
	Location position;
}Player;

Player initializePlayer(struct GameState* game);
char getCellContent(struct GameState* game, Location location);
void updateMap(struct GameState* game, Location current_l, Location future_l);
int moveBox(struct GameState* game, Location current_l, Location next);
void handleNewPosition(Player* player, struct GameState* game, Location new_cell, Location after_new);
void movePlayer(struct GameState* game, Player* player, enum Direction direction);

#endif

