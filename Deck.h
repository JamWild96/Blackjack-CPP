#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <random>
#include <algorithm>

class Deck {
private:
    std::vector<Card> deck;
    mutable std::mutex deckMutex;
public:
    Deck() {
        reset();
        shuffle();
    }

    void shuffle() {
        std::lock_guard<std::mutex> lock(deckMutex);
        std::srand(static_cast<unsigned int>(time(NULL)));
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    }

    Card dealCard() {
        std::lock_guard<std::mutex> lock(deckMutex);
        Card dealtCard = deck.back();
        deck.pop_back();void shuffle();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

        return dealtCard;
    }

    void reset() {
        std::lock_guard<std::mutex> lock(deckMutex);
        deck.clear();
        for (int s = HEARTS; s <= SPADES; ++s) {
            for (int r = ACE; r <= KING; ++r) {
                deck.push_back(Card(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }
};

#endif
