#ifndef TABLE_H
#define TABLE_H

#include "Card.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "Pile.hpp"
#include "Iterator.hpp"
#include <vector>
#include <stack>
#include <iostream>

class Table;

class Table {
private:
    std::vector<Pile*> piles;
    Deck deck;
    size_t completed;
    size_t stock;
public:
    Table();
    ~Table();
    void build_table();
    void stock_table();
    bool move(int , int);
    Pile* get(int);
    Collection* get(int, int);
    Card* get(int, int, int);

    Iterator<Pile> begin();
    Iterator<Pile> end();
};

Table::Table() : deck(1, 8){
    completed = 0;
    stock = 0;
    build_table();
}
Table::~Table(){
    for (auto pile : piles){
        delete pile;
    }
}
void Table::build_table(){
    for (int i = 0; i < 10; i++){
        piles.push_back(new Pile());
    }
    for (int i = 0; i < 54; i++){
        Collection * collection = new Collection();
        if (i >= 44) collection->make_visible();
        collection->push(deck.deal());
        get(i%10)->push(collection);
    }
}
void Table::stock_table(){
    for (auto pile : piles){
        Collection * collection = new Collection();
        collection->make_visible();
        collection->push(deck.deal());
        if (pile->top()->can_merge(collection)){
            pile->top()->merge(collection);
        }
        else {
            pile->push(collection);
        }
    }
}
bool Table::move(int pile1, int pile2){
    if (pile1 != pile2){
        auto collection1 = piles[pile1]->top();
        auto collection2 = piles[pile2]->top();
        if (collection2->can_merge(collection1)){
            collection2->merge(collection1);
            piles[pile1]->pop();
            piles[pile1]->top()->make_visible();
            return true;
        }
    }
    return false;
}
Pile* Table::get(int i){
    return piles[i];
}
Collection* Table::get(int i, int j){
    return get(i)->get(j);
}
Card* Table::get(int i, int j, int k){
    return get(i, j)->get(k);
}

Iterator<Pile> Table::begin() {
	return Iterator<Pile>(piles, 0); 
}
Iterator<Pile> Table::end() {
	return Iterator<Pile>(piles, piles.size()); 
}

#endif