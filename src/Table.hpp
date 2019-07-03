#ifndef TABLE_H
#define TABLE_H

#include "Card.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "Pile.hpp"
#include "../util/Iterator.hpp"
#include <vector>

class Table;

class Table {
private:
    std::vector<Pile*> piles;
    Deck deck;
    size_t completed_count;
    size_t stock_count;
public:
    Table();
    ~Table();
    void build();
    void stock();
    bool move(int , int);
    Pile* get(int);
    Collection* get(int, int);
    Card* get(int, int, int);
    int get_stock_count();
    int get_completed_count();
    void completed();

    Iterator<Pile> begin();
    Iterator<Pile> end();
};

Table::Table() : deck(2, 8){
    completed_count = 0;
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
    for (int i = 0; i < 54; i++){
        Collection * collection = new Collection();
        if (i >= 44) collection->make_visible();
        collection->push(deck.deal());
        get(i%10)->push(collection);
    }
}
void Table::stock(){
    if (stock_count > 0){
        for (auto pile : piles){
            Collection * collection = new Collection();
            collection->make_visible();
            collection->push(deck.deal());
            if (!pile->empty() && (pile->top()->can_merge(collection))){
                pile->top()->merge(collection);
            }
            else {
                pile->push(collection);
            }
        }
        stock_count--;
    }
}
bool Table::move(int p1, int p2){
    Pile* pile1 = get(p1);
    Pile* pile2 = get(p2);
    if (pile1 != pile2){
        if (pile2->empty()) 
            pile2->push(new Collection(true));
        Collection* collection1 = pile1->top();
        Collection* collection2 = pile2->top();
        if (!(collection2->can_merge(collection1) || collection2->can_rest(collection1)))
            return false;
        else if (collection2->can_merge(collection1))
            collection2->merge(collection1);
        else if (collection2->can_rest(collection1))
            pile2->push(collection1);
        pile1->pop();
        if (!pile1->empty())
            pile1->top()->make_visible();    
        return true; 
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
int Table::get_stock_count(){
    return stock_count;
}
int Table::get_completed_count(){
    return completed_count;
}
void Table::completed(){
    completed_count++;
}

Iterator<Pile> Table::begin() {
	return Iterator<Pile>(piles, 0); 
}
Iterator<Pile> Table::end() {
	return Iterator<Pile>(piles, piles.size()); 
}

#endif