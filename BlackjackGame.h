#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Dealer.h"
#include <thread>
#include <mutex>

class BlackjackGame {
private:
    Deck deck;
    Player player;
    Dealer dealer;
    std::mutex gameMutex;

    void playerTurn() {
        bool playerTurn = true;
        while (playerTurn) {
            std::cout << "\nYour hand: \n";
            player.displayHand();
            std::cout << "Total: " << player.getTotal() << std::endl;

            if (player.isBlackjack()) {
                std::cout << "You have Blackjack!" << std::endl;
                return;
            }
            if (player.isBust()) {
                std::cout << "You are bust!" << std::endl;
                return;
            }
            playerTurn = player.hitOrStand();
            if (playerTurn) {
                player.addCard(deck.dealCard());
            }
        }
    }

    void dealerTurn() {
        dealer.play(deck);
    }

public:
    void startGame() {
        std::cout << "Welcome to Blackjack!" << std::endl;
        deck.reset();
        player.reset();
        dealer.reset();
        std::cout << "Shuffling deck..." << std::endl;
        deck.shuffle();
        std::cout << "Dealing cards..." << std::endl;

        player.addCard(deck.dealCard());
        player.addCard(deck.dealCard());
        dealer.addCard(deck.dealCard());
        dealer.addCard(deck.dealCard());

        std::cout << "Dealer's visible card:  " << std::endl;
        dealer.displayHand();

        // Create threads for the player and dealer turns
        std::thread playerThread(&BlackjackGame::playerTurn, this);
        std::thread dealerThread(&BlackjackGame::dealerTurn, this);

        // Wait for both threads to finish
        playerThread.join();
        dealerThread.join();

        determineOutcome();
    }

    void determineOutcome() {
        std::lock_guard<std::mutex> lock(gameMutex);
        if (player.isBust()) {
            std::cout << "You lose!" << std::endl;
            return;
        }

        std::cout << "\nDealer's hand: \n";
        dealer.displayHand();
        std::cout << "Total: " << dealer.getTotal() << std::endl;

        if (dealer.isBust()) {
            std::cout << "Dealer is bust! You win!" << std::endl;
            return;
        }

        if (dealer.getTotal() > player.getTotal()) {
            std::cout << "Dealer wins!" << std::endl;
        } else if (dealer.getTotal() < player.getTotal()) {
            std::cout << "You win!" << std::endl;
        } else {
            std::cout << "It's a tie!" << std::endl;
        }
    }
};

#endif
