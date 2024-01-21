#include "../include/player.h"

Player player;

void initializePlayer() {
	player.position.x = gameState.initialPlayerPosition.x;
	player.position.y = gameState.initialPlayerPosition.y;
}

char getCellContent(Location location) {
	char CellContent = gameState.levelGrid[location.y][location.x];
	return CellContent;
}

void updateMap(Location currentPosition, Location nextPosition) {
	char currentCellContent = getCellContent(currentPosition);
	char nextCellContent = getCellContent(nextPosition);

	//update nextCell
	if (nextCellContent == TARGET) {
		if (currentCellContent == BOX || currentCellContent == BOX_ON_TARGET) {
			gameState.levelGrid[nextPosition.y][nextPosition.x] = BOX_ON_TARGET;
		}else {
			gameState.levelGrid[nextPosition.y][nextPosition.x] = PLAYER_ON_TARGET;
		}
	}else if (currentCellContent == BOX || currentCellContent == BOX_ON_TARGET) {
		gameState.levelGrid[nextPosition.y][nextPosition.x] = BOX;
	}else {
		gameState.levelGrid[nextPosition.y][nextPosition.x] = PLAYER;
	}

	//update currentCell
	if (currentCellContent == BOX_ON_TARGET || currentCellContent == PLAYER_ON_TARGET) {
		gameState.levelGrid[currentPosition.y][currentPosition.x] = TARGET;
	}else {
		gameState.levelGrid[currentPosition.y][currentPosition.x] = EMPTY;
	}
}

int moveBox(Location current, Location next) {
	switch (getCellContent(next)) {
		case EMPTY: {
			if (getCellContent(current) == BOX_ON_TARGET) {
				gameState.completedTargets -= 1;
			}
			updateMap(current, next);
			return 1;
		}
		case TARGET: {
			if (getCellContent(current) != BOX_ON_TARGET) {
				gameState.completedTargets += 1;
			}
			updateMap(current, next);
			return 1;
		}
		default:
			return 0;
	}
}

void handleNewPosition(Location newCell, Location cellAfterNew) {
	char newPositionCell = getCellContent(newCell);
	switch (newPositionCell) {
		case EMPTY:
		case TARGET: {
			updateMap(player.position, newCell);
			player.position = newCell;
			break;
		}
		case BOX:
		case BOX_ON_TARGET: {
			if(moveBox(newCell, cellAfterNew)) {
				updateMap(player.position, newCell);
				player.position = newCell;
			}
			break;
		}
		default:
			break;
	}
}

void movePlayer(enum Direction direction) {
	Location newPosition = player.position;
	Location positionAfterNew = player.position;

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

	handleNewPosition(newPosition, positionAfterNew);
}


