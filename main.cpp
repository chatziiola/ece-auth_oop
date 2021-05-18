#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"

using namespace std;

void printGridsSideBySide(Player** players, int playerTurn) {
    cout << "     " << players[0]->getName() << setw(29) << players[1]->getName() << endl;
    stringstream ss(players[0]->gridToString(playerTurn != 0)), ss2(players[1]->gridToString(playerTurn == 0));
    string to, to2;
    while(getline(ss, to, '\n') && getline(ss2, to2, '\n'))
        cout << to << to2 << endl;
    cout << endl;
}

int main() {
    srand(time(NULL));

    Player** players = new Player*[2];
    players[0] = new Player("Player 1");
    players[1] = new Player("Player 2");

    // Set up the ships on the grid
    players[0]->placeShips();
    players[1]->placeShips();

    int playerTurn = 0;
    do {
        cout << "Turn of " << players[playerTurn]->getName() << endl << endl;
        printGridsSideBySide(players, playerTurn);

        if (players[playerTurn]->canMoveSubmarine() && players[playerTurn]->moveSubmarine()) {
            cout << players[playerTurn]->getName() << " moved the submarine!" << endl << endl;
            printGridsSideBySide(players, playerTurn);
        }

        // Guess position
        Square* p = players[playerTurn]->guessSquare();
        cout << players[playerTurn]->getName() << " shoots at " << p->toString();
        if (players[1 - playerTurn]->acceptHit(p->getX(), p->getY()))
            cout << ". It's a Hit!" << endl << endl;
        else
            cout << ". It's a Miss!" << endl << endl;
        delete p;

        printGridsSideBySide(players, playerTurn);

        if ((!players[playerTurn]->canDoubleHit()) || (!players[playerTurn]->doubleHit()))
            playerTurn = 1 - playerTurn;
    } while (!(players[0]->numberOfShipsThatAreSunk() == 10 || players[1]->numberOfShipsThatAreSunk() == 10));

    if (players[0]->numberOfShipsThatAreSunk() == 10)
        cout << players[1]->getName() << " has won! (Score: " << players[0]->calculatePoints() << "-" << players[1]->calculatePoints() << ")" << endl;
    else
        cout << players[0]->getName() << " has won! (Score: " << players[0]->calculatePoints() << "-" << players[1]->calculatePoints() << ")" << endl;

    return 0;
}
