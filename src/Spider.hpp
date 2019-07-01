#ifndef SPIDER_H
#define SPIDER_H

#include "Deck.hpp"
#include "Table.hpp"
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
    int mouse[2];
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
    void convert_click(int mouse_x, int mouse_y);
    void convert_click_column(int, int);
    void convert_click_row(int, int, int, Pile*);
    void convert_store(int, int, int);   
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
    //delete table;
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
            window_ptr->clear(sf::Color(34, 100, 34));
            render();
            window_ptr->display();
        }
    }
}
void Spider::poll(){
    sf::Event event;
    while (window_ptr->pollEvent(event)){
        if (event.type == sf::Event::Closed) close();
        if (event.type == sf::Event::MouseButtonPressed) mousePress(event);
        if (event.type == sf::Event::MouseButtonReleased) mouseRelease(event);

        if (event.type == sf::Event::MouseMoved){
            mouse[0] = event.mouseMove.x;
            mouse[1] = event.mouseMove.y;
        }
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
    for (auto pile : table){
        pile->check();
    }
}
void Spider::render(){
    render_spaces();
    render_cards();
    if (picked_up) {
        render_picked(table.get(current[0], current[1]));
    }
}
void Spider::mousePress(sf::Event event){
    convert_click(event.mouseButton.x, event.mouseButton.y);
    if (current[0] != -1){
        picked_up = true;
        if (table.get(current[0])->split(current[1], current[2])){
            current[1]++;
        }
    }
}
void Spider::mouseRelease(sf::Event event){
    if (picked_up){
        int c_table = current[0];
        convert_click(event.mouseButton.x, event.mouseButton.y);
        if (current[0] != -1){
            table.move(c_table, current[0]);
        }
        table.get(c_table)->unsplit();
        picked_up = false;
    }
}
bool is_within(int card, int mouse, int width){
    return (card < mouse && card + width > mouse);
}
void Spider::convert_click(int mouse_x, int mouse_y){
    for (int i = 0; i < 3; i++) current[i] = -1;
    convert_click_column(mouse_x, mouse_y);
}
void Spider::convert_click_column(int mouse_x, int mouse_y){
    int i = 0;
    for (auto pile : table){
        int card_x = (card_width + card_width/10)*i +(card_width/2);
        if (is_within(card_x, mouse_x, card_width)){
            convert_click_row(mouse_x, mouse_y, i, pile);
        }
        i++;
    }
}
void Spider::convert_click_row(int mouse_x, int mouse_y, int i, Pile* pile){
    int j = 0;
    int overall = 0;
    if (pile->empty()){
        int card_y = (card_height/5);
        if (is_within(card_y, mouse_y, card_height)){
            convert_store(i, j, 0);
        }
    } 
    else {
        for (auto collection : *pile){
            int k = 0;
            for (auto card : *collection){
                int card_y = (card_height/3)*(overall) +(card_height/5);
                if (is_within(card_y, mouse_y, card_height)){
                    convert_store(i, j, k);
                }
                k++;
                overall++;
            }
            j++;
        } 
    }
}
void Spider::convert_store(int i, int j, int k){
    current[0] = i;
    current[1] = j;
    current[2] = k;
}
void draw_rect(sf::RenderWindow *window_ptr, int x, int y, bool visible, int rank, int suit){
    sf::RectangleShape shape(sf::Vector2f(100,150));
    shape.setPosition(x, y);
    shape.setOutlineThickness(3);
    if (rank == -1 && suit == -1){
        shape.setOutlineColor(sf::Color::Red);
        shape.setFillColor(sf::Color::Transparent); 
    }
    else {
        shape.setOutlineColor(sf::Color::White);
        shape.setFillColor(sf::Color(0,0,139));
    }
    if (visible){
        shape.setOutlineColor(sf::Color::Red);
        if (suit == 0) shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(sf::Color::White);
    }
    window_ptr->draw(shape);
}
void draw_text(sf::RenderWindow *window_ptr, int x, int y, int rank, int suit){
    sf::Text text;
    sf::Font font;
    font.loadFromFile("util/arial.ttf");
    text.setFont(font);
    text.setString(std::to_string(rank));
    text.setPosition(x, y);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    if (suit == 0)
        text.setFillColor(sf::Color::Black);
    window_ptr->draw(text);
}
void render_card(sf::RenderWindow *window_ptr, int x, int y, bool visible = false, int rank = -1, int suit = -1){
    draw_rect(window_ptr, x, y, visible, rank, suit);
    if (visible){
        draw_text(window_ptr, x, y, rank, suit);
    }
}
void Spider::render_cards(){
    int i = 0, j = 0, k = 0, overall = 0;
    for (auto pile : table){
        for (auto collection : *pile){
            for (auto card : *collection){
                if (!((current[0] == i) && (current[1] == j) && picked_up)){
                    render_card(window_ptr, 
                                (card_width + 10)*i +(card_width/2),
                                (card_height/3)*(overall) +(card_height/5), 
                                collection->is_visible(),
                                card->get_rank(), card->get_suit());
                }
                k++;
                overall++;
            }
            k = 0;
            j++;
        }
        overall = 0;
        j = 0;
        i++;
    }
}
void Spider::render_spaces(){
    int i = 0;
    for (auto pile : table){
        render_card(window_ptr,
                        (card_width + 10)*i +(card_width/2),
                        (card_height/5));
        i++;
    }
}
void Spider::render_picked(Collection * collection){
    int i = 0;
    for (auto card : *collection){
        int x = mouse[0]-card_width/2;
        int y = (i*card_height/3) + mouse[1]-card_height/2;
        render_card(window_ptr, x, y, true, card->get_rank(), card->get_suit());
        i++;
    }
}
#endif