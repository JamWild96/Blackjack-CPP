#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"
#include "Deck.h"

class Dealer : public Hand {
public:
    void play(Deck& deck) {
        while (getTotal() < 17) {
            addCard(deck.dealCard());
        }
    }
};

#endif
