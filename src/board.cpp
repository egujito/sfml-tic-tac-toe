#include "board.hpp"
#include <iostream>
#include<cmath>

void Board::drawBoard(sf::RenderWindow& win)
{
    sf::Vector2u size = win.getSize();
    int i_sum = 1;
    for (int i = 0; i < 5 ; i+=2) // 0 -> 2 -> 4
    {   
        sf::Vertex vertices[2] =
        {
            sf::Vertex(sf::Vector2f(0, int(size.y/3) * (i+i_sum))),
            sf::Vertex(sf::Vector2f(size.x, int(size.y/3) * (i+i_sum))),
        };
        win.draw(vertices, 2, sf::Lines);
        i_sum = 0;
    }
    i_sum = 1;
    for (int i = 0; i < 5 ; i+=2) // 0 -> 2 -> 4
    {   
        
        sf::Vertex vertices[2] =
        {
            sf::Vertex(sf::Vector2f(214 * (i+i_sum), 0)),
            sf::Vertex(sf::Vector2f(214 * (i+i_sum), size.y))
        };
        win.draw(vertices, 2, sf::Lines);
        i_sum = 0;
    }
}

void Board::toggleTurn()
{
    turn = !turn;
}


void Board::parseInput(int mx, int my, sf::RenderWindow& window)
{   
    sf::Vector2u size = window.getSize();

    int cell_x = mx/(size.x/3);
    int cell_y = my/(size.y/3);

    if (isempty(cell_x, cell_y))
    {
        cells[cell_x][cell_y] = turn;
        std::cout << turn << " to " << cell_x << " " << cell_y << std::endl;
        
        if (wincons()) is_game_finished = true;
        else toggleTurn();
        
    } else std::cout << "Cell is not empty" << std::endl;
}

int Board::getIndex(int i, int j)
{
    return cells[i][j];
}

bool Board::isempty(int i, int j)
{
    bool val = (cells[i][j] != O && cells[i][j] != X) ? true : false;
    return val; 
}

void Board::draw_circle(sf::RenderWindow& win, int row, int column)
{
    sf::Vector2u size = win.getSize();

    sf::CircleShape circle((size.x/3)/2);

    circle.setPosition((size.x/3)*row, (size.y/3)*column);
    circle.setFillColor(sf::Color(0, 0, 0));

    circle.setOutlineThickness(-15);
    circle.setOutlineColor(sf::Color(BLUE));

    win.draw(circle);
}

void Board::draw_cross(sf::RenderWindow& win, int row, int column)
{
    sf::Vector2u size = win.getSize();

    sf::Vertex T_line_pos[] =
    {
        sf::Vertex(sf::Vector2f((size.x/3)*row, (size.y/3)*column), sf::Color(RED)),
        sf::Vertex(sf::Vector2f((size.x/3)*row + size.x/3, (size.y/3)*column + size.y/3), sf::Color(RED))
    };

    win.draw(T_line_pos, 2, sf::Lines);

    sf::Vertex T_line_neg[] =
    {
        sf::Vertex(sf::Vector2f((size.x/3)*row + size.x/3, (size.y/3)*column), sf::Color(RED)),
        sf::Vertex(sf::Vector2f((size.x/3)*row, (size.y/3)*column + size.y/3), sf::Color(RED))
    };

    win.draw(T_line_neg, 3, sf::Lines);
}

void Board::drawMoves(sf::RenderWindow& win)
{
     
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isempty(i, j))
            {   
                if (cells[i][j] == X)
                {
                    draw_cross(win, i, j);
                }
                else if (cells[i][j] == O)
                {
                    draw_circle(win, i, j);
                }
            }
        }
    }
}

bool Board::wincons()
{
    bool sequence=false;

	//verify lines
	for(int i=0; i<3; i++) {
		if(cells[i][0] == turn) {
			sequence = true;

			for(int j=0; j<3; j++) {
				if(cells[i][j] != turn) {
					sequence = false;
				}
			}
		}

		if(sequence) {
			return(true);
		}
	}

	sequence = false;

	//verify coluns
	for(int i=0; i<3; i++) {
		if(cells[0][i] == turn) {
			sequence = true;

			for(int j=0; j<3; j++) {
				if(cells[j][i] != turn) {
					sequence = false;
				}
			}
		}

		if(sequence) {
			return(true);
		}
	}

	//verify diagnoles 1
	if(cells[0][0] == turn) {
		sequence = true;

		for(int i=0; i<3; i++) {
			if(cells[i][i] != turn) {
				sequence = false;
			}
		}

		if(sequence) {
			return(true);
		}
	}

	//verify diagnoles 2
	if(cells[0][3-1] == turn) {
		sequence = true;

		for(int i=0; i<3; i++) {
			if(cells[i][3-1-i] != turn) {
				sequence = false;
			}
		}

		if(sequence) {
			return(true);
		}
	}

	return(false);

}