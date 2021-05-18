#include "ship.h"

// TODO: Implement here the methods of Ship and all derived classes
Ship::Ship() {
    shipSize = 0;
    squares = NULL;
    shipType = CARRIER;
}

Ship::Ship(int shipSize, ShipType shipType) {
    this->shipSize = shipSize;
    this->shipType = shipType;
    squares = new Square*[shipSize];
}

Ship::~Ship() {
    delete[] squares;
}

void Ship::setSize(int shipSize) {
    this->shipSize = shipSize;
}

void Ship::setType(ShipType shipType) {
    this->shipType = shipType;
}

int Ship::getSize() {
    return shipSize;
}

ShipType Ship::getType() {
    return shipType;
}

void Ship::setSquares(Square** squares) {
	this->squares = new Square*[shipSize];

    for(int i = 0; i < shipSize; i++)
    {
        this->squares[i] = squares[i];
    }
}

Square* Ship::getSquare(int index) {
    return *(squares+index);
}

bool Ship::hasSquare(Square* square) {

    for(int i=0; i<shipSize; i++) {
        if(squares[i]->equals(square))
            return 1;
    }

    return 0;
}

int Ship::getNumberOfHits() {
    int num = 0;

    for(int i=0; i<shipSize; i++) {
        if(squares[i]->isHit())
            num++;
    }

    return num;
}

bool Ship::isSunk() {
    if(getNumberOfHits() == this->shipSize)
        return true;
    return false;
}

Carrier::Carrier() {
    shipSize = 6;
    shipType = CARRIER;
    doubleHits = 1;
}

bool Carrier::canDoubleHit() {
    return doubleHits; //WARNING!!!!!!
}

void Carrier::doubleHit() {
    doubleHits--;
}

Battleship::Battleship() {
    shipSize = 4;
    shipType = BATTLESHIP;
}

Cruiser::Cruiser() {
    shipSize = 3;
    shipType = CRUISER;
}

Submarine::Submarine(int moves) {
    shipSize = 3;
    shipType = SUBMARINE;
    this->moves = moves;
}

bool Submarine::canMove() {
    return (moves && (getNumberOfHits()==0))? 1:0 ;
}

void Submarine::makeMove() {
    moves--;
}

Destroyer::Destroyer() {
    shipSize = 2;
    shipType = DESTROYER;
}




