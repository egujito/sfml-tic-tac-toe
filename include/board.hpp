#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define WIDTH 640
#define HEIGHT 640
#define X_MAX_CELLS 3
#define Y_MAX_CELLS 3
#define X 0
#define O 1
#define TIE 10
#define RED 255,0,0
#define BLUE 0,0,255
#define BLACK 0, 0, 0


class Board 
{

public:

    void drawBoard(sf::RenderWindow& win);
    void parseInput(int mx, int my, sf::RenderWindow& window);
    void drawMoves(sf::RenderWindow& win);
    int getTurn();
    bool is_Game_finished();
    void setCells();

private:

    bool checkTie();
    bool wincons();
    bool isempty(int i, int j);
    void toggleTurn();
    void draw_cross(sf::RenderWindow& win, int row, int column);
    void draw_circle(sf::RenderWindow& win, int row, int column);
    int cells[X_MAX_CELLS][Y_MAX_CELLS];
    int turn;
    bool is_game_finished;

};
