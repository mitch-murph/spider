#ifndef COLLECTION_H
#define COLLECTION_H

#include "Card.hpp"
#include <vector>
#include <iostream>

class Collection
{
private:
    bool visible;
    std::vector<Card* > cards;
public:
    Collection(bool);
    ~Collection();
    void push(Card * card);
    bool can_merge(Collection * other);
    void merge(Collection * other);
    std::vector<Card* > * get_cards();
    void print_collection();
};

Collection::Collection(bool visible) : visible(visible) {
}

Collection::~Collection(){
}

void Collection::push(Card * card){
    cards.push_back(card);
}

bool Collection::can_merge(Collection * other){
    return (this->cards[this->cards.size()-1]->rank - 1 == other->cards[other->cards.size()-1]->rank);
}

void Collection::merge(Collection * other){
    for (auto card : other->cards){
        this->cards.push_back(card);
    }
}

std::vector<Card *> * Collection::get_cards(){
    return & cards;
}

void Collection::print_collection(){
    for (auto card : cards){
        if (visible)
            std::cout << card->suit << ", " << card->rank << "\t";
        else
            std::cout << "*" << ", " << "**" << "\t";

    }
}

#endif