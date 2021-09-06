#include <SFML/Graphics.hpp>
#include "board.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML TTT");
    Board board;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        board.setup(window);
        window.display();
    }

    return 0;
}