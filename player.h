#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"

/**
 * Class that implements a player of the game.
 */
class Player
{
private:
    string name;
    Ship** ships; // the ships of the player
    Grid* grid; // the grid of the player
    Grid* opponentGrid; // the grid of the opponent, used to keep track of the hits of the player

public:
    /**
     * Initializes a player setting the name. The two grids (one for the player and one for keeping
     * track of the opponent's grid) and the ships are also initialized.
     *
     * @param name the name of the player.
     */
    Player(string name);

    /**
     * Deletes this player, by deleting also the grids and the ships.
     */
    ~Player();

    /**
     * Returns the name of the player.
     *
     * @return the name of the player.
     */
    string getName();

    /**
     * Returns the grid of the player.
     *
     * @return the grid of the player.
     */
    Grid* getGrid();

    /**
     * Returns the number of ships of the player that are sunk.
     *
     * @return the number of ships of the player that are sunk.
     */
    int numberOfShipsThatAreSunk();

    /**
     * Accepts a hit at the location provided. This method calls the acceptHit method of the Grid object.
     *
     * @param x the horizontal coordinate of the hit.
     * @param y the vertical coordinate of the hit.
     * @return true if there is a ship in the square, or false otherwise.
     */
    bool acceptHit(int x, int y);

    /**
     * Guesses a square for the player randomly. This method continuously guesses a square
     * until it finds a non-hit square at the opponentGrid. When a valid guess is found,
     * the hitSquare method is called for the square of the opponentGrid. Finally, the method
     * returns the square that is guessed.
     *
     * @return the square that is guessed by the player.
     */
    Square* guessSquare();

    /**
     * Checks if the submarine of the player can move, by calling the canMove method of Submarine.
     *
     * @return true if the submarine can move, or false otherwise.
     */
    bool canMoveSubmarine();

    /**
     * Moves the submarine to a new location in the grid.
     *
     * @return true if the submarine is moved, or false otherwise.
     */
    bool moveSubmarine();

    /**
     * Checks if the carrier can perform a double hit, by calling the canDoubleHit method of Carrier.
     *
     * @return true if the carrier can perform a double hit, or false otherwise.
     */
    bool canDoubleHit();

    /**
     * Performs a double hit using the carrier of the player.
     *
     * @return true if the double hit is performed, or false otherwise.
     */
    bool doubleHit();

    /**
     * Creates the ships of the player by calling the different constructors.
     */
    void createShips();

    /**
     * Places the ships of the player in different positions in the player's grid.
     * Calls the placeShip method for each ship placement, giving as input the coordinates (x, y),
     * the direction (r for right or d for down) and the size of the ship.
     */
    void placeShips();

    /**
     * Returns a string representation of the player's grid.
     *
     * @param hide boolean indicating whether the ships should be shown (false) or remain hidden (true).
     * @return the grid of the player as string.
     */
    string gridToString(bool hide);

    /**
     * Calculates and returns the points of the player at the end of the game. If the player has lost, then
     * he/she earns 0 points. If the player has won, then he/she earns 50 points for the victory, as well as
     * 10 points for every square of a Carrier ship that is not hit, 5 points for every square of a Battleship
     * ship that is not hit, and 1 point for every square of any other ship that is not hit.
     *
     * @return the points of the player.
     */
    int calculatePoints();
};

#endif // PLAYER_H
