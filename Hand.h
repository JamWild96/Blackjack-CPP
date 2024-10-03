#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
#include <mutex>

class Hand {
private:
    std::vector<Card> hand;
    mutable std::mutex handMutex;
public:
    void addCard(const Card& card) {
        std::lock_guard<std::mutex> lock(handMutex);
        hand.push_back(card);
    }

    int getTotal() const {
        std::lock_guard<std::mutex> lock(handMutex);
        int total = 0;
        int aceCount = 0;
        for (const Card& card : hand) {
            total += card.getValue();
            if (card.getValue() == ACE) {
                aceCount++;
            }
        }
        while (total > 21 && aceCount > 0) {
            total -= 10;
            aceCount--;
        }
        return total;
    }

    bool isBust() const {
        return getTotal() > 21;
    }

    bool isBlackjack() const {
        return hand.size() == 2 && getTotal() == 21;
    }

    void displayHand() const {
        std::lock_guard<std::mutex> lock(handMutex);
        for (const Card& card : hand) {
            card.displayCard();
        }
    }
    void reset() {
        std::lock_guard<std::mutex> lock(handMutex);
        hand.clear();

    }
};

#endif
