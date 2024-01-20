#include "../include/player.h"



Player initializePlayer(struct GameState* game) {
	Player new_player;
	new_player.position.x = game->playerX;
	new_player.position.y = game->playerY;
	return new_player;
}

char getCellContent(struct GameState* game, Location location) {
	char CellContent = game->game_grid[location.y][location.x];
	return CellContent;
}

void updateMap(struct GameState *game, Location current_l, Location future_l) {
	char current_Cell = getCellContent(game, current_l);
	char future_Cell = getCellContent(game, future_l);

	if (future_Cell == TARGET) {
		if (current_Cell == BOX || current_Cell == BOX_ON_TARGET) {
			game->game_grid[future_l.y][future_l.x] = BOX_ON_TARGET;
		}else {
			game->game_grid[future_l.y][future_l.x] = PLAYER_ON_TARGET;
		}
	}else {
		if (current_Cell == BOX || current_Cell == BOX_ON_TARGET) {
			game->game_grid[future_l.y][future_l.x] = BOX;
		}else {
			game->game_grid[future_l.y][future_l.x] = PLAYER;
		}
	}
	if (current_Cell == BOX_ON_TARGET || current_Cell == PLAYER_ON_TARGET) {
		game->game_grid[current_l.y][current_l.x] = TARGET;
	}else {
		game->game_grid[current_l.y][current_l.x] = EMPTY;
	}
}

int moveBox(struct GameState *game, Location current, Location next) {
	char next_cell  = getCellContent(game, next);
	char current_cell  = getCellContent(game, current);

	switch (next_cell) {
		case EMPTY: {
			if (current_cell == BOX_ON_TARGET) {
				game->targets_Completed -= 1;
			}
			updateMap(game, current, next);
			return 1;
		}
		case TARGET: {
			if (current_cell != BOX_ON_TARGET) {
				game->targets_Completed += 1;
			}
			updateMap(game, current, next);
			return 1;
		}
		default:
			return 0;
	}
}

void handleNewPosition(Player* player, struct GameState *game, Location new_cell, Location after_new_cell) {
	char new_position_cell = game->game_grid[new_cell.y][new_cell.x];
	switch (new_position_cell) {
		case EMPTY:
		case TARGET: {
			updateMap(game, player->position, new_cell);
			player->position = new_cell;
			break;
		}
		case BOX:
		case BOX_ON_TARGET: {
			if(moveBox(game, new_cell, after_new_cell)) {
				updateMap(game, player->position, new_cell);
				player->position = new_cell;
			}
			break;
		}
		default:
			break;
	}
}

void movePlayer(struct GameState *game, Player* player, enum Direction direction) {
	Location next_cell;
	next_cell.y = player->position.y;
	next_cell.x = player->position.x;
	Location after_next_cell = next_cell;

	switch (direction) {
		case UP:
			next_cell.y -= 1;
			after_next_cell.y -=2;
			break;
		case DOWN:
			next_cell.y += 1;
			after_next_cell.y += 2;
			break;
		case LEFT:
			next_cell.x -= 1;
			after_next_cell.x -= 2;
			break;
		case RIGHT:
			next_cell.x += 1;
			after_next_cell.x += 2;
			break;
		default:
			break;
	}

	handleNewPosition(player, game, next_cell, after_next_cell);
}


