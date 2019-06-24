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
    while (1){
        std::cout << "============================================================" << std::endl;
        int x, y;
        std::cin >> x >> y;
        table.make_move(x, y);
        table.print_table();
    }
}