#include <iostream>
#include "BlackjackGame.h"

int main() {
    BlackjackGame game;
    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        game.startGame();
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;
    }
    return 0;
}
