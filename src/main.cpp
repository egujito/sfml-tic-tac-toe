#include "board.hpp"


int main()
{

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML TTT");
    Board board;
    board.setCells();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    board.parseInput(event.mouseButton.x, event.mouseButton.y, window);
                }
        }

        window.clear();
        board.drawBoard(window);
        board.drawMoves(window);
        window.display();

        if (board.is_Game_finished())
        {
            int winner = board.getTurn();
            switch (winner)
            {
                case X:
                    std::cout << "X wins!" << std::endl;
                    break;
                case O:
                    std::cout << "O wins!" << std::endl;
                    break;
                case TIE:
                    std::cout << "It's a tie!" << std::endl;
                    break;
            }
            sleep(5);
            exit(0);
        }
    }
    
    return 0;
}