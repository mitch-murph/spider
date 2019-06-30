#ifndef SPIDER_H
#define SPIDER_H

#include "Deck.hpp"
#include "Table.hpp"
#include <string>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

class Spider {
private:
    sf::RenderWindow *window_ptr;
    int width, height;
    int card_width, card_height;
    bool is_running;
    Table table;


    bool picked_up;
    int current[3];
    int m[2];
public:
    Spider(int, int);
    ~Spider();
    void run();
    void init();
    void close();
    void exit();
    void loop();
    void poll();
    void update();
    void render();    

    void mousePress(sf::Event event);
    void mouseRelease(sf::Event event);
    void render_cards();
    void render_spaces();
    void render_picked(Collection *);
};

Spider::Spider(int w, int h) {
    height = h;
    width = w;
    card_width = 100;
    card_height = 150;
    is_running = false;

    picked_up = false;
}
Spider::~Spider(){

}
void Spider::init(){
    window_ptr = new sf::RenderWindow(sf::VideoMode(width, height), "Spider");
    is_running = true;
}
void Spider::loop(){
    while (window_ptr->isOpen()){
        poll();
        update();
        if (is_running){
            window_ptr->clear(sf::Color::White);
            render();
            window_ptr->display();
        }
    }
}
void convert_click(int mouse_x, int mouse_y, Table &table, int card_width, int card_height, int (&card_pos)[3]){
    for (int i = 0; i < 3; i++)
        card_pos[i] = -1;
    size_t c_table = 0, c_pile = 0, c_collection = 0, overall = 0;
    for (auto pile : table){
        int cx = (card_width + 10)*c_table +(card_width/5);
        if (pile->empty()){
            int cy = (card_height/5);
            if (cx < mouse_x && cx + 100 > mouse_x &&
                    cy < mouse_y && cy + 150 > mouse_y){
                card_pos[0] = c_table;
                card_pos[1] = c_pile;
                card_pos[2] = c_collection;
            }
        }
        for (auto collection : *pile){
            for (auto card : *collection){
                int cy = (card_height/3)*(overall) +(card_height/5);
                if (cx < mouse_x && cx + 100 > mouse_x &&
                     cy < mouse_y && cy + 150 > mouse_y){
                    card_pos[0] = c_table;
                    card_pos[1] = c_pile;
                    card_pos[2] = c_collection;
                }
                c_collection++;
                overall++;
            }
            c_collection = 0;
            c_pile++;
        }
        overall = 0;
        c_pile = 0;
        c_table++;
    }
}
void Spider::poll(){
    sf::Event event;
    while (window_ptr->pollEvent(event)){
        if (event.type == sf::Event::Closed) close();
        if (event.type == sf::Event::MouseButtonPressed) mousePress(event);
        if (event.type == sf::Event::MouseButtonReleased) mouseRelease(event);



        if (event.type == sf::Event::KeyPressed) {
            table.stock();
        }
        if (event.type == sf::Event::MouseMoved){
            m[0] = event.mouseMove.x;
            m[1] = event.mouseMove.y;
        }
    }
}
void Spider::mousePress(sf::Event event){
    convert_click(event.mouseButton.x, event.mouseButton.y, table, card_width, card_height, current);
    if (current[0] != -1 && current[1] != -1 && current[2] != -1){
        picked_up = true;
        if (table.get(current[0])->split(current[1], current[2])){
            std::cout << "Split" << std::endl;
            current[1]++;
        }
    }
}
void Spider::mouseRelease(sf::Event event){
    if (picked_up){
        int c_table = current[0];
        convert_click(event.mouseButton.x, event.mouseButton.y, table, card_width, card_height, current);
        if (current[0] != -1 && current[1] != -1 && current[2] != -1){
            table.move(c_table, current[0]);
        }
        table.get(c_table)->unsplit();
        picked_up = false;
    }
}
void Spider::close(){
    is_running = false;
    window_ptr->close();
}
void Spider::exit(){
    delete window_ptr;
    window_ptr = NULL;
}
void Spider::run(){
    init();
    loop();
    exit();
}
void Spider::update(){
    if (picked_up){
        if (!table.get(0)->empty())
            if (!(table.get(current[0])->size() - 1 == current[1])) picked_up = false;
    }
    table.check();
}
void render_card(sf::RenderWindow *window_ptr, int x, int y, bool visible = false, int rank = -1, int suit = -1){
    sf::RectangleShape shape(sf::Vector2f(100,150));
    shape.setFillColor(sf::Color::Green);
    if (rank == -1 && suit == -1) shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    window_ptr->draw(shape);

        // sf::Text text;
        // sf::Font font;
        // font.loadFromFile("arial.ttf");
        // text.setFont(font);
        // text.setString(std::to_string(suit) + "\t" + std::to_string(rank));
        // text.setPosition(x, y);
        // text.setCharacterSize(24);
        // text.setFillColor(sf::Color::Blue);
        // window_ptr->draw(text);

    if (visible){
        sf::Text text;
        sf::Font font;
        font.loadFromFile("util/arial.ttf");
        text.setFont(font);
        text.setString(std::to_string(suit) + "\t" + std::to_string(rank));
        text.setPosition(x, y);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        window_ptr->draw(text);
    }
}
void Spider::render_cards(){
    size_t c_table = 0, c_pile = 0, c_collection = 0, overall = 0;
    for (auto pile : table){
        for (auto collection : *pile){
            for (auto card : *collection){
                if (!((current[0] == c_table) && (current[1] == c_pile) && picked_up)){
                    render_card(window_ptr, 
                                (card_width + 10)*c_table +(card_width/5),
                                (card_height/3)*(overall) +(card_height/5), 
                                collection->is_visible(),
                                card->get_rank(), card->get_suit());
                }
                c_collection++;
                overall++;
            }
            c_collection = 0;
            c_pile++;
        }
        overall = 0;
        c_collection = 0;
        c_pile = 0;
        c_table++;
    }
}
void Spider::render_spaces(){
    int i = 0;
    for (auto pile : table){
        render_card(window_ptr,
                        (card_width + 10)*i +(card_width/5),
                        (card_height/5));
        i++;
    }
}
void Spider::render_picked(Collection * collection){
    int i = 0;
    for (auto card : *collection){
        int x = m[0]-card_width/2;
        int y = (i*card_height/3) + m[1]-card_height/2;
        render_card(window_ptr, x, y, true, card->get_rank(), card->get_suit());
        i++;
    }
}
void Spider::render(){
    render_spaces();
    render_cards();
    if (picked_up) {
        render_picked(table.get(current[0], current[1]));
    }
}


#endif