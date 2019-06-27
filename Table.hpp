#ifndef TABLE_H
#define TABLE_H

#include "Card.hpp"
#include "Collection.hpp"
#include "Deck.hpp"
#include "Pile.hpp"
#include <vector>
#include <stack>
#include <iostream>

class Table;
class Pile_iterator;

class Table {
private:
    std::vector<Pile*> table;
    Deck deck;
    size_t completed;
public:
    Table();
    void build_table();
    void stock_table();
    void make_move(int , int);
    void print_table();
    std::vector<Pile*>* get_piles();

    Pile_iterator begin();
    Pile_iterator end();
};

class Pile_iterator {
private:
    const std::vector<Pile*> *pile_ptr;
    size_t position;
public:
    Pile_iterator(const Pile_iterator&);
    Pile_iterator(std::vector<Pile*>&, size_t);
    ~Pile_iterator();
    Pile_iterator operator=(const Pile_iterator&);
    bool operator==(const Pile_iterator&) const;
    bool operator!=(const Pile_iterator&) const;
    Pile_iterator operator++();
    Pile_iterator operator++(int);
    Pile* operator*() const;
    Pile* operator->() const;
};

Table::Table() : deck(2, 8){
    completed = 0;
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
        std::cout << i << "----->\t";
        table[i]->print_pile();
        std::cout << std::endl;
    }
}
std::vector<Pile*>* Table::get_piles(){
    return &table;
}
Pile_iterator Table::begin() {
	return Pile_iterator(*get_piles(), 0); 
}
Pile_iterator Table::end() {
	return Pile_iterator(*get_piles(), table.size()); 
}

Pile_iterator::Pile_iterator(const Pile_iterator& other){
    pile_ptr = other.pile_ptr;
    position = other.position;
}
Pile_iterator::Pile_iterator(std::vector<Pile*>& pile, size_t position){
    this->pile_ptr = &pile;
    this->position = position;
}
Pile_iterator::~Pile_iterator(){}
Pile_iterator Pile_iterator::operator=(const Pile_iterator& other){
    return Pile_iterator(*this);
}
bool Pile_iterator::operator==(const Pile_iterator& other) const {
    return (pile_ptr == other.pile_ptr && position == other.position);
}
bool Pile_iterator::operator!=(const Pile_iterator& other) const {
    return !(*this == other);
}
Pile_iterator Pile_iterator::operator++(){
    position++;
    return *this;
} 
Pile_iterator Pile_iterator::operator++(int){
    Pile_iterator temp = *this;
    ++position;
    return temp;
}
Pile* Pile_iterator::operator*() const {
    return (*pile_ptr)[position];
} 
Pile* Pile_iterator::operator->() const {
    return (*pile_ptr)[position];
}

#endif