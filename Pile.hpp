#ifndef PILE_H
#define PILE_H

#include <vector>
#include "Collection.hpp"

class Pile{
private:
    std::vector<Collection *> collections;
public:
    Pile();
    ~Pile();
    void push(Collection * collection);
    std::vector<Collection *> * get_collections();
    Collection * top();
    void pop();
    void print_pile();
};

Pile::Pile(){

}

Pile::~Pile(){

}

void Pile::push(Collection * collection){
    collections.push_back(collection);
}

Collection * Pile::top(){
    return collections[collections.size()-1];
}

std::vector<Collection *> * Pile::get_collections(){
    return  &collections;
}

void Pile::pop(){
    collections.pop_back();
    top()->make_visible();
}

void Pile::print_pile(){
    for (auto collection : collections){
        collection->print_collection();
        std::cout << ";";
    }
}

#endif