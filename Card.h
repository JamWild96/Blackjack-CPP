#ifndef CARD_H
#define CARD_H

#include <iostream>

enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10 };

class Card {
private:
    Suit suit;
    Rank rank;
public:
    Card(Suit s, Rank r) : suit(s), rank(r) {}
    [[nodiscard]] int getValue() const {
        return rank;
    }
    void displayCard() const {
        std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        std::string ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
        std::cout << ranks[rank - 1] << " of " << suits[suit] << std::endl;
    }
};

#endif
