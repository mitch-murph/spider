#ifndef TABLE_H
#define TABLE_H

#include "Card.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "Pile.hpp"
#include <vector>
#include <stack>
#include <iostream>

class Table {
private:
    std::vector<Pile*> table;
    Deck deck;
public:
    Table(Deck &deck);
    void build_table();
    void stock_table();
    void make_move(int , int);
    void print_table();
};

Table::Table(Deck &deck) : deck(deck){
    build_table();
}

void Table::build_table(){
    for (int i = 0; i < 10; i++){
        Pile *pile = new Pile();
        size_t amount = 3;
        if (i < 4) amount = 4;
        for (int j = 0; j < amount; j++){
            Collection * collection = new Collection(false);
            (*collection).push(deck.deal());
            (*pile).push(collection);
        }
        Collection * collection = new Collection(true);
        (*collection).push(deck.deal());
        (*pile).push(collection);
        table.push_back(pile);
    }
}

void Table::stock_table(){
    for (auto pile : table){
        Collection * collection = new Collection(true);
        (*collection).push(deck.deal());
        if (pile->top()->can_merge(collection)){
            pile->top()->merge(collection);
        }
        else {
            (*pile).push(collection);
        }
    }
}

void Table::make_move(int pile1, int pile2){
    auto col1 = table[pile1]->top();
    auto col2 = table[pile2]->top();
    if (col2->can_merge(col1)){
        col2->merge(col1);
        table[pile1]->pop();
    }
}

void Table::print_table(){
    for (int i = 0; i < 10; i++){
        std::cout << i << "-> ";
        table[i]->print_pile();
        std::cout << std::endl;
    }
}

#endif