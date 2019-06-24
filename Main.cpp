#include <iostream>
#include <vector>
#include "Spider.hpp"
#include "Deck.hpp"
#include "Card.hpp"

int main (){
    Deck deck(1, 8);
    //deck.print_deck();
    Table table(deck);
    table.print_table();
    table.stock_table();
    std::cout << "============================================================" << std::endl;
    table.print_table();
}