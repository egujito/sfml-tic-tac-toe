#include "board.hpp"
#include <iostream>


int Board::getTurn()
{
    return turn;// returns current turn/state of game. Used in "main.cpp"
                // to determine who is the winner or if the game is tied
}

bool Board::is_Game_finished()
{
    return is_game_finished; // shall return private boolean that says if game is finished.
}

void Board::setCells() // Reset all cells. Called to setup the board.
{
    for (int i = 0; i < Y_MAX_CELLS; i++)
    {
        for (int j = 0; j < X_MAX_CELLS; j++)
        {
            cells[i][j] = 2;
        }
    }
}

void Board::drawBoard(sf::RenderWindow& win) // Draw the grid (sf::Lines)
{
    sf::Vector2u size = win.getSize();
    int i_sum = 1;
    for (int i = 0; i < 5 ; i+=2) // 0 -> 2 -> 4
    {   
        sf::Vertex vertices[2] =
        {
            sf::Vertex(sf::Vector2f(0, int(size.y/X_MAX_CELLS) * (i+i_sum))),
            sf::Vertex(sf::Vector2f(size.x, int(size.y/Y_MAX_CELLS) * (i+i_sum))),
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

void Board::toggleTurn() // Changes the turn
{
    turn = !turn;
}


void Board::parseInput(int mx, int my, sf::RenderWindow& window)
// acccepts 3 parameters:
// param1: X coordinates of mouse
// param2: Y coordinates of mouse 
// param3: Renderer/Window in order to draw shapes on the grid.
{   
    sf::Vector2u size = window.getSize();

    int cell_x = mx/(size.x/X_MAX_CELLS);
    int cell_y = my/(size.y/Y_MAX_CELLS);

    if (isempty(cell_x, cell_y))
    {
        cells[cell_x][cell_y] = turn;
        std::cout << turn << " to " << cell_x << " " << cell_y << std::endl;
        
        if (wincons()) is_game_finished = true;
        else toggleTurn();

    } 
    else std::cout << "Cell is not empty" << std::endl;
    checkTie();
}

bool Board::checkTie()
// Checks is board is full.
// Returns: bool tied.
// tied = true: if board is full and win condition function returns false;
// tied = false: if board is not full.

{
    bool tied = false;
    for(int i=0; i<X_MAX_CELLS; i++) 
    {
		for(int j=0; j<Y_MAX_CELLS; j++) 
        {
			if(cells[i][j] == 2) 
            {
				return tied;
			}
		}
	}
    tied = true;
    if (tied == true && (!wincons()))
    {
        is_game_finished = true;
        turn = TIE;
    }

    return 0;
}

bool Board::isempty(int x, int y)
// checks if given cell is empty or not.
{
    return (cells[x][y] != O && cells[x][y] != X) ? true : false; 
}

void Board::draw_circle(sf::RenderWindow& win, int row, int column)
// draws sf::CircleShape
// In this function renderer X and Y coordinates are calculated
// in order to draw the shape in the correct position
// param1: Sf::RenderWindow, to draw the shape
// param2, param3: row, column, to calculate the correct coordinates 
{
    sf::Vector2u size = win.getSize();

    sf::CircleShape circle((size.x/X_MAX_CELLS)/2);

    circle.setPosition((size.x/X_MAX_CELLS)*row, (size.x/Y_MAX_CELLS)*column);
    circle.setFillColor(sf::Color(BLACK));

    circle.setOutlineThickness(-5);
    circle.setOutlineColor(sf::Color(BLUE));

    win.draw(circle);
}

void Board::draw_cross(sf::RenderWindow& win, int row, int column)
// draws 2 sf::Vertex
// In this function renderer X and Y coordinates are calculated
// in order to draw the shape in the correct position
// param1: Sf::RenderWindow, to draw the shape
// param2, param3: row, column, to calculate the correct coordinates 
{
    sf::Vector2u size = win.getSize();

    sf::Vertex T_line_pos[] =
    {
        sf::Vertex(sf::Vector2f((size.x/X_MAX_CELLS)*row, (size.y/Y_MAX_CELLS)*column), sf::Color(RED)),
        sf::Vertex(sf::Vector2f((size.x/X_MAX_CELLS)*row + size.x/X_MAX_CELLS, (size.y/Y_MAX_CELLS)*column + size.y/Y_MAX_CELLS), sf::Color(RED))
    };

    win.draw(T_line_pos, 2, sf::Lines);

    sf::Vertex T_line_neg[] 
    {
        sf::Vertex(sf::Vector2f((size.x/X_MAX_CELLS)*row + size.x/X_MAX_CELLS, (size.y/Y_MAX_CELLS)*column), sf::Color(RED)),
        sf::Vertex(sf::Vector2f((size.x/X_MAX_CELLS)*row, (size.y/Y_MAX_CELLS)*column + size.y/Y_MAX_CELLS), sf::Color(RED))
    };

    win.draw(T_line_neg, 2, sf::Lines);
}

void Board::drawMoves(sf::RenderWindow& win)
// Render which the shapes of the cells that are not empty
{
    for (int i = 0; i < X_MAX_CELLS; i++)
    {
        for (int j = 0; j < Y_MAX_CELLS; j++)
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

// credits: l0py2

bool Board::wincons()
//checks all winning possibilties
{
    bool sequence=false;

	for(int i=0; i<X_MAX_CELLS; i++) {
		if(cells[i][0] == turn) {
			sequence = true;

			for(int j=0; j<Y_MAX_CELLS; j++) {
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

	for(int i=0; i<X_MAX_CELLS; i++) {
		if(cells[0][i] == turn) {
			sequence = true;

			for(int j=0; j<Y_MAX_CELLS; j++) {
				if(cells[j][i] != turn) {
					sequence = false;
				}
			}
		}

		if(sequence) {
			return(true);
		}
	}

	if(cells[0][0] == turn) {
		sequence = true;

		for(int i=0; i<X_MAX_CELLS; i++) {
			if(cells[i][i] != turn) {
				sequence = false;
			}
		}

		if(sequence) {
			return(true);
		}
	}

	if(cells[0][Y_MAX_CELLS-1] == turn) {
		sequence = true;

		for(int i=0; i<X_MAX_CELLS; i++) {
			if(cells[i][Y_MAX_CELLS-1-i] != turn) {
				sequence = false;
			}
		}

		if(sequence) {
			return(true);
		}
	}

	return(false);
}