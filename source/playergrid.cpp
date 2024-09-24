#include "player.h"

// TODO: Implement here the method shipCanBePlaced of Grid and the method calculatePoints of Player
// Do not implement any other methods of these two classes (as they are already implemented in files grid.cpp and player.cpp)

bool Grid::shipCanBePlaced(int x, int y, char shipDirection, Ship* ship){

	int shipSize = ship->getSize(); // Get the current ship's size

	if (9 - x < shipSize || 9 - y < shipSize) { // Check if the ship fits the grid
		return false;
	}
	else if (shipDirection == 'r') { // Check if the ship can be plased top to bottom
		for (int i = 0; i < shipSize; i++) {
			if (hasShip(x, y + i)) {
				return false;
			}
		}
		for (int i = 0; i < shipSize; i++) {
			if (isHit(x, y + i)) {
				return false;
			}
		}
	}
	else if (shipDirection == 'd') { // Check if the ship can be placed left to right
		for (int i = 0; i < shipSize; i++) {
			if (hasShip(x + i, y)) {
				return false;
			}
		}
		for (int i = 0; i < shipSize; i++) {
			if (isHit(x + i, y)) {
				return false;
			}
		}
	}

    return true;
}

int Player::calculatePoints() {
	// In the case that all the player's ships are sunk he has lost
	if ( numberOfShipsThatAreSunk() == 10 )
		return 0;
	// Otherwise, he is the winnder
	unsigned int points = 50;
	// We now want to give the points based on the given criteria
	// For every unhit square of carrier +50
	// For every unhit square of battleship +5
	// For every other unhit square +1
	for ( int l = 0; l < 10; l++ )
		if ( ! ships[l]->isSunk() )
		{
			if ( ships[l]->getType() == CARRIER )
				points += 50*(ships[l]->getSize() - ships[l]->getNumberOfHits());
			else if ( ships[l]->getType() == BATTLESHIP )
				points += 5*(ships[l]->getSize() - ships[l]->getNumberOfHits());
			else
				points += ships[l]->getSize() - ships[l]->getNumberOfHits();
		}
	return points;
}
