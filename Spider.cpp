//g++ -c spider.cpp -o main.o && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(120,50));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
	
	        if (event.type == sf::Event::MouseButtonReleased){
		        std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl; 
	        }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}