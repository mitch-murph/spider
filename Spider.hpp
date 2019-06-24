#ifndef SPIDER_H
#define SPIDER_H

#include "Deck.hpp"
#include <vector>

class Spider {
private:
    size_t size;
    Deck deck;
public:
    Spider(){
        size = 0;
    }
    size_t getSize() { return size; }

    void print_deck(){
        deck.print_deck();
    }
};

#endif