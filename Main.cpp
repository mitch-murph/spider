#include <iostream>
#include <vector>
#include <utility>

#include "Table.hpp"
// #include "Deck.hpp"
#include "Card.hpp"

int main (){
    Table table;
    for (auto a : table){
        a->print_pile();
        std::cout<< std::endl;
    }
}