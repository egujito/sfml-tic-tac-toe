#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include<cmath>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define BR_LEN 9
#define X 0
#define O 1
#define RED 255,0,0
#define BLUE 0,0,255


class Board 
{

public:

    void drawBoard(sf::RenderWindow& win);
    void parseInput(int mx, int my, sf::RenderWindow& window);
    void drawMoves(sf::RenderWindow& win);
    int getIndex(int i, int j);
    int getTurn()
    {
        return turn;
    }
    bool is_Game_finished()
    {
        return is_game_finished;
    }
    void setCells()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cells[i][j] = 2;
            }
        }
    }
private:
    bool wincons();
    bool isempty(int i, int j);
    void toggleTurn();
    void draw_cross(sf::RenderWindow& win, int row, int column);
    void draw_circle(sf::RenderWindow& win, int row, int column);
    void endgame();
    int cells[BR_LEN/3][BR_LEN/3]; // 0 -> X || 1 -> O
    int turn;
    bool is_game_finished;

};