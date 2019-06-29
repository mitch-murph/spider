#ifndef CARD_H
#define CARD_H

#include <utility>

class Card{
private:
    int suit;
    int rank;
public:
    Card();
    Card(int, int);
    Card(std::pair<int, int>);
    ~Card();
    void set_rank(int);
    void set_suit(int);
    int get_rank();
    int get_suit();
    std::pair<int, int> get_card();
};

Card::Card(){}
Card::Card(int r, int s){
    rank = r;
    suit = s;
}
Card::Card(std::pair<int, int> c){
    rank = c.first;
    suit = c.second;
}
Card::~Card(){}
void Card::set_rank(int r){
    rank = r;
}
void Card::set_suit(int s){
    suit = s;
}
int Card::get_rank(){
    return rank;
}
int Card::get_suit(){
    return suit;
}
std::pair<int, int> Card::get_card(){
    return {rank, suit};
}

#endif