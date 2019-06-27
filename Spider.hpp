#ifndef SPIDER_H
#define SPIDER_H

#include "Deck.hpp"
#include "Table.hpp"
#include <vector>
#include <stack>

class Spider {
private:
    Deck deck;
    Table table;
    size_t completed;
public:
    Spider();
    ~Spider();
};

Spider::Spider() {
    completed = 0;
}

Spider::~Spider(){
}

#endif