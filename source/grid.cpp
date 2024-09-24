#include <iostream>
#include "grid.h"

Grid::Grid() {
    squares = new Square**[10];
    for (int i = 0; i < 10; i++){
        squares[i] = new Square*[10];
        for (int j = 0; j < 10; j++)
            squares[i][j] = new Square(i, j);
    }
}

Grid::~Grid() {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            delete squares[i][j];
        delete[] squares[i];
    }
    delete[] squares;
}

bool Grid::acceptHit(int x, int y){
    squares[x][y]->hitSquare();
    return squares[x][y]->hasShip();
}

bool Grid::isHit(int x, int y){
    return squares[x][y]->isHit();
}

bool Grid::hasShip(int x, int y){
    return squares[x][y]->hasShip();
}

void Grid::placeShip(int x, int y, char shipDirection, Ship* ship){
    Square** shipSquares = new Square*[ship->getSize()];
    if (shipDirection == 'r'){
        for(int i = 0; i < ship->getSize(); i++){
            shipSquares[i] = squares[x][y+i];
            squares[x][y+i]->addShip();
        }
    }
    else if (shipDirection == 'd'){
        for(int i = 0; i < ship->getSize(); i++){
            shipSquares[i] = squares[x+i][y];
            squares[x+i][y]->addShip();
        }
    }
    ship->setSquares(shipSquares);
    delete[] shipSquares;
}

void Grid::removeShip(Ship* ship){
    for(int i = 0; i < ship->getSize(); i++)
        ship->getSquare(i)->removeShip();
}

