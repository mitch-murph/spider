#ifndef DECK_H
#define DECK_H

#include "Card.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class Deck {
private:
    size_t suit_count;
    size_t set_count;
    std::vector<Card *> deck_of_cards;
public:
    Deck(size_t suit_count, size_t set_count);
    ~Deck();
    void build_deck();
    void shuffle_deck();
    Card * deal();
    std::vector<Card *> deal(int n);
    void print_deck();
};

Deck::Deck(size_t suit_count, size_t set_count) : suit_count(suit_count), set_count(set_count) {
    build_deck();
    shuffle_deck();
}

Deck::~Deck(){
    for (int i = 0; i < deck_of_cards.size(); i++){
        delete deck_of_cards[i];
    }
}

void Deck::build_deck(){
    for (size_t i = 0; i < suit_count; i++){
        for (size_t k = 0; k < set_count/suit_count; k++) {
            for (size_t j = 0; j < 13; j++) {
                Card *temp = new Card;
                temp->suit = i;
                temp->rank = j;
                deck_of_cards.push_back(temp);
            }
        }
    }
}

void Deck::shuffle_deck(){
    srand(time(NULL));
    
    for (int i = 0; i < deck_of_cards.size(); i++){
        int random_index = rand() % deck_of_cards.size();
        Card * temp = deck_of_cards[i];
        deck_of_cards[i] = deck_of_cards[random_index];
        deck_of_cards[random_index] = temp;
    }
}

Card * Deck::deal(){
    Card * card = deck_of_cards.back();
    deck_of_cards.pop_back();
    return card;
}

std::vector<Card *> Deck::deal(int n){
    std::vector<Card *> cards;
    for (int i = 0 ; i < n; i++){
        Card * card = deck_of_cards.back();
        deck_of_cards.pop_back();
        cards.push_back(card);
    }
    return cards;
}

void Deck::print_deck(){
    for (int i = 0; i < deck_of_cards.size(); i++){
        std::cout << deck_of_cards[i]->rank << ", " <<  deck_of_cards[i]->suit  << std::endl;
    }
}

#endif