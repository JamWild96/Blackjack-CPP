#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"

class Player : public Hand {
public:
    bool hitOrStand() {
        char choice;
        std::cout << "Do you want to hit (h) or stand (s)? ";
        std::cin >> choice;
        return (choice == 'h' || choice == 'H');
    }
};

#endif
