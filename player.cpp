#include <cstdlib>
#include "player.h"

Player::Player(string name) {
    this->name = name;
    grid = new Grid();
    opponentGrid = new Grid();
    ships = new Ship*[10];
    createShips();
}

Player::~Player(){
    delete grid;
    delete opponentGrid;
    for (int i = 0; i < 10; i++)
        delete ships[i];
    delete[] ships;
}

string Player::getName() {
    return name;
}

Grid* Player::getGrid(){
    return grid;
}

int Player::numberOfShipsThatAreSunk() {
    int sunkShips = 0;
    for (int i = 0; i < 10; i++) {
        if (ships[i]->isSunk())
            sunkShips++;
    }
    return sunkShips;
}

bool Player::canMoveSubmarine() {
    if (((Submarine*)ships[5])->canMove()){
        // Check if there is at least one location (consecutive squares) where the submarine can be moved
        char directions[] = {'r', 'd'};
        for (int k = 0; k < 2; k++){
            char direction = directions[k];
            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 10; j++){
                    if (grid->shipCanBePlaced(i, j, direction, ships[5]))
                        return true;
                }
            }
        }
    }
    return false;
}

bool Player::moveSubmarine() {
    if (rand() % 2 == 0){ // used to decide randomly whether to move or not
        grid->removeShip(ships[5]);
        // figure out a random placement
        int x, y;
        char z;
        do {
            x = rand() % 10;
            y = rand() % 10;
            z = (rand() % 2 == 0) ? 'r' : 'd';
        } while(!grid->shipCanBePlaced(x, y, z, ships[5]));
        grid->placeShip(x, y, z, ships[5]);
        ((Submarine*)ships[5])->makeMove();
        return true;
    }
    return false;
}

bool Player::canDoubleHit() {
    return ((Carrier*)ships[0])->canDoubleHit();
}

bool Player::doubleHit() {
    if (rand() % 2 == 0){ // used to decide randomly whether to double hit or not
        ((Carrier*)ships[0])->doubleHit();
        return true;
    }
    return false;
}

bool Player::acceptHit(int x, int y) {
    return grid->acceptHit(x, y);
}

Square* Player::guessSquare() {
    int x, y;
    // find a random square that is not already hit
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while(opponentGrid->isHit(x, y));
    opponentGrid->acceptHit(x, y);
    return new Square(x, y);
}

void Player::createShips() {
    ships[0] = new Carrier();
    ships[1] = new Battleship();
    ships[2] = new Battleship();
    ships[3] = new Cruiser();
    ships[4] = new Cruiser();
    ships[5] = new Submarine(2);
    ships[6] = new Destroyer();
    ships[7] = new Destroyer();
    ships[8] = new Destroyer();
    ships[9] = new Destroyer();
};

void Player::placeShips() {
    for (int i = 0; i < 10; i++){
        // for each ship figure out a random placement
        int x, y;
        char z;
        do {
            x = rand() % 10;
            y = rand() % 10;
            z = (rand() % 2 == 0) ? 'r' : 'd';
        } while(!grid->shipCanBePlaced(x, y, z, ships[i]));
        grid->placeShip(x, y, z, ships[i]);
    }
};

string Player::gridToString(bool hide) {
    stringstream sstm;
    sstm << "     _______________________ \n"
         << "    |                       |\n"
         << "    |   0 1 2 3 4 5 6 7 8 9 |\n"
         << "    |                       |\n";
    for(int i = 0; i < 10; i++) {
        sstm << "    | " << ((char)('A' + i)) << " ";
        for(int j = 0; j < 10; j++) {
            if(grid->hasShip(i, j) && grid->isHit(i, j)) sstm << "# ";
            else if(!grid->hasShip(i, j) && grid->isHit(i, j)) sstm << "+ ";
            else if(grid->hasShip(i, j) && !hide) sstm << "# ";
            else sstm << "- ";
        }
        sstm << "|\n";
    }
    sstm << "    |_______________________|";
    string result = sstm.str();
    return result;
};
