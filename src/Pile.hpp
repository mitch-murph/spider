#ifndef PILE_H
#define PILE_H

#include <vector>
#include "Collection.hpp"
#include "../util/Stack.hpp"
#include "../util/Iterator.hpp"

class Pile : public Stack<Collection> {
private:
    std::vector<Collection *>& collections;
public:
    Pile();
    ~Pile();

    Collection * second();
    bool can_merge(Collection*);
    bool split(int, int);
    void unsplit();

    Iterator<Collection> begin();
    Iterator<Collection> end();
};

Pile::Pile() : collections(v) {

}
Pile::~Pile(){
    for (auto collection : collections){
        delete collection;
    }
}
Collection * Pile::second(){
    return collections[size()-2];
}
bool Pile::can_merge(Collection * other){
    if (size() > 0)
        return top()->can_merge(other);
    return true;
}
bool Pile::split(int j, int k){
    if (top() == get(j)){
        Collection* temp = get(j)->split(k);
        if (!temp->empty()){
            push(temp);
            return true;
        }
    }
    return false;
}
void Pile::unsplit(){
    if (size() > 1){
        if (second()->is_visible() && second()->can_merge(top())){
            Collection * temp = top();
            temp->make_visible();
            pop();
            top()->merge(temp);
        }
    }
}

Iterator<Collection> Pile::begin() {
	return Iterator<Collection>(collections, 0); 
}
Iterator<Collection> Pile::end() {
	return Iterator<Collection>(collections, size()); 
}

#endif