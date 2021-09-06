#include "board.hpp"

void Board::setup(sf::RenderWindow& win)
{
    for (int i = 0; i < BR_LEN; ++i)
    {
        tab[i] = ' ';
    }

    int lc = 1;
    int sub_iter = 1;

    while (lc < 5 && sub_iter < 3)
    {
        sf::RectangleShape rectangle;

        rectangle.setSize(sf::Vector2f(640, 5));

        if (lc < 3) // MEANS WE ARE STILL DRWAING THE HORIZONTAL STROKES FOR THE BOARD
        {
            rectangle.setPosition(0, ((640/4) * lc) - 5);
            win.draw(rectangle);
        }
        ++lc;
    } 
}