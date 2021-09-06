#pragma once
#include <SFML/Graphics.hpp>

#define BR_LEN 9

class Board 
{

public:

    void setup(sf::RenderWindow& win);

private:
    char tab[BR_LEN];
};  