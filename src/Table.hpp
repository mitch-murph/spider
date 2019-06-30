#ifndef TABLE_H
#define TABLE_H

#include "Card.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "Pile.hpp"
#include "../util/Iterator.hpp"
#include <vector>
#include <stack>
#include <iostream>

class Table;

class Table {
private:
    std::vector<Pile*> piles;
    Deck deck;
    size_t completed;
    size_t stock_count;
public:
    Table();
    ~Table();
    void build();
    void stock();
    bool move(int , int);
    void check();
    Pile* get(int);
    Collection* get(int, int);
    Card* get(int, int, int);

    Iterator<Pile> begin();
    Iterator<Pile> end();
};

Table::Table() : deck(1, 4){
    completed = 0;
    stock_count = 5;
    build();
}
Table::~Table(){
    for (auto pile : piles){
        delete pile;
    }
}
void Table::build(){
    for (int i = 0; i < 10; i++){
        piles.push_back(new Pile());
    }
    for (int i = 0; i < 44; i++){
        Collection * collection = new Collection();
        if (i >= 34) collection->make_visible();
        collection->push(deck.deal());
        get(i%10)->push(collection);
    }
}
void Table::stock(){
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
        if (get(pile2)->empty()){
            Collection* temp = new Collection();
            temp->make_visible();
            get(pile2)->push(temp);
        }
        auto collection1 = get(pile1)->top();
        auto collection2 = get(pile2)->top();
        if (collection2->can_merge(collection1)){
            collection2->merge(collection1);
            get(pile1)->pop();
            if (!get(pile1)->empty())
                get(pile1)->top()->make_visible();
            return true;
        }
    }
    return false;
}
void Table::check(){
    for (auto pile : *this){
        if (pile->size() > 0){
            if (pile->top()->front()->get_rank() == 12 && pile->top()->top()->get_rank() == 0){
                pile->pop();
                if (pile->size() > 0) pile->top()->make_visible(); 
            }
        }
    }
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