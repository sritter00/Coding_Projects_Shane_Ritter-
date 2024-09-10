#include "Game.h"
#include <iostream>
using namespace std; 
int main() {
    cout << "How many players? (1/2): ";
    int numPlayers;
    cin >> numPlayers;
    Game game;
    game.run(numPlayers);

    return 0;
}
