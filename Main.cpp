#include <iostream>
#include <vector>
#include <utility>

#include "Table.hpp"
// #include "Deck.hpp"
#include "Card.hpp"

int main (){
    Table table;
    for (auto a : table){
        for (auto b : *a){
            for (auto c : *b){
                std::cout << c->get_rank() << std::endl;
            }
        }
    }
}