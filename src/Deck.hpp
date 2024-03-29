#ifndef DECK_H
#define DECK_H

#include "Card.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>

class Deck {
private:
    std::vector<Card *> deck_of_cards;
public:
    Deck();
    Deck(size_t, size_t);
    ~Deck();
    void build(size_t, size_t);
    void swap(int, int);
    void shuffle();
    Card * deal();
    std::vector<Card *> deal(int n);
};

Deck::Deck() {
    build(4, 4);
    shuffle();
}
Deck::Deck(size_t suit_count, size_t set_count) {
    build(suit_count, set_count);
    shuffle();
}
Deck::~Deck(){
    for (int i = 0; i < deck_of_cards.size(); i++){
        delete deck_of_cards[i];
    }
}
void Deck::build(size_t suit_count, size_t set_count){
    for (size_t i = 0; i < suit_count; i++){
        for (size_t k = 0; k < set_count/suit_count; k++) {
            for (size_t j = 0; j < 13; j++) {
                deck_of_cards.push_back(
                    new Card(j, i)
                );
            }
        }
    }
}
void Deck::swap(int x, int y){
    Card * temp = deck_of_cards[x];
    deck_of_cards[x] = deck_of_cards[y];
    deck_of_cards[y] = temp;
}
void Deck::shuffle(){
    srand(time(NULL));    
    for (int i = 0; i < deck_of_cards.size(); i++){
        int random_index = rand() % deck_of_cards.size();
        swap(random_index, i);
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
        cards.push_back(deck_of_cards.back());
        deck_of_cards.pop_back();
    }
    return cards;
}

#endif