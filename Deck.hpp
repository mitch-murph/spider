#ifndef DECK_H
#define DECK_H

#include "Card.hpp"
#include <vector>
#include <iostream>

class Deck {
private:
    std::vector<Card *> deck_of_cards;
public:
    Deck(){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 13; j++) {
                Card *temp = new Card;
                temp->suit = i;
                temp->rank = j;
                deck_of_cards.push_back(temp);
            }
    }

    void print_deck(){
        for (int i = 0; i < deck_of_cards.size(); i++){
            std::cout << deck_of_cards[i]->rank << ", " <<  deck_of_cards[i]->suit  << std::endl;
        }
    }
};

#endif