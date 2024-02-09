#include "../include/player.h"
/*
void initializePlayer(Location playerPosition) {
	player.position.x = gameState->initialPlayerPosition.x;
	player.position.y = gameState->initialPlayerPosition.y;
}*/

char getCellContent(enum CellContent** levelGrid, Location location) {
	char CellContent = levelGrid[location.y][location.x];
	return CellContent;
}

void updateMap(enum CellContent** levelGrid, Location currentPosition, Location nextPosition) {
	char currentCellContent = getCellContent(levelGrid, currentPosition);
	char nextCellContent = getCellContent(levelGrid, nextPosition);

	//update nextCell
	if (nextCellContent == TARGET) {
		if (currentCellContent == BOX || currentCellContent == BOX_ON_TARGET) {
			levelGrid[nextPosition.y][nextPosition.x] = BOX_ON_TARGET;
		}else {
			levelGrid[nextPosition.y][nextPosition.x] = PLAYER_ON_TARGET;
		}
	}else if (currentCellContent == BOX || currentCellContent == BOX_ON_TARGET) {
		levelGrid[nextPosition.y][nextPosition.x] = BOX;
	}else {
		levelGrid[nextPosition.y][nextPosition.x] = PLAYER;
	}

	//update currentCell
	if (currentCellContent == BOX_ON_TARGET || currentCellContent == PLAYER_ON_TARGET) {
		levelGrid[currentPosition.y][currentPosition.x] = TARGET;
	}else {
		levelGrid[currentPosition.y][currentPosition.x] = EMPTY;
	}
}

int moveBox(struct GameState* gameState, Location current, Location next) {
	switch (getCellContent(gameState->levelGrid, next)) {
		case EMPTY: {
			if (getCellContent(gameState->levelGrid, current) == BOX_ON_TARGET) {
				gameState->completedTargets -= 1;
			}
			updateMap(gameState->levelGrid, current, next);
			return 1;
		}
		case TARGET: {
			if (getCellContent(gameState->levelGrid, current) != BOX_ON_TARGET) {
				gameState->completedTargets += 1;
			}
			updateMap(gameState->levelGrid, current, next);
			return 1;
		}
		default:
			return 0;
	}
}

int handleNewPosition(struct GameState* game, Location newCell, Location cellAfterNew) {
	char newPositionCell = getCellContent(game->levelGrid, newCell);
	switch (newPositionCell) {
		case EMPTY:
		case TARGET: {
			updateMap(game->levelGrid, game->playerPosition, newCell);
			game->playerPosition = newCell;
            return 1;
		}
		case BOX:
		case BOX_ON_TARGET: {
			if(moveBox(game, newCell, cellAfterNew)) {
				updateMap(game->levelGrid, game->playerPosition, newCell);
				game->playerPosition = newCell;
                return 1;
			}
            return 0;
		}
		default:
            return 0;
	}
}

int movePlayer(struct GameState* game, enum Direction direction) {
	Location newPosition = game->playerPosition;
	Location positionAfterNew = game->playerPosition;

	switch (direction) {
		case UP:
			newPosition.y -= 1;
			positionAfterNew.y -=2;
			break;
		case DOWN:
			newPosition.y += 1;
			positionAfterNew.y += 2;
			break;
		case LEFT:
			newPosition.x -= 1;
			positionAfterNew.x -= 2;
			break;
		case RIGHT:
			newPosition.x += 1;
			positionAfterNew.x += 2;
			break;
		default:
			break;
	}

    if (handleNewPosition(game, newPosition, positionAfterNew)) {
        return 1;
    }else {
        return 0;
    }
}


