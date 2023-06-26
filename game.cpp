#include "game.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "puzzle15.h"
#include "solution.h"


// конструктор класу, який визначає кількість позицій як 0 та розміщує плитки в правильному порядку
Game::Game()
{   
    this->count = 0;
}

// функція розв'язку гри (повернення позиції плит у розв'язане положення)
void Game::solve(bool &flag)
{   
    transposeMatrix(this->state_of_tiles);
    Solver solver(this->state_of_tiles, flag);

    solver.printCurrentPosition();
    solver.run();
    solver.printCurrentPosition();
    this->count = 0;

     
    
}
// функція генерації позиції плит рандомізованим чином
void Game::scramble()
{   
    std::srand(unsigned(std::time(0)));
    int a = rand() % (6 + 1);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a == 1) {
                state_of_tiles[i][j] = state1[i][j];
            }
            else if (a == 2) {
                state_of_tiles[i][j] = state2[i][j];
            }
            else if (a == 3) {
                state_of_tiles[i][j] = state3[i][j];
            }
            else if (a == 4) {
                state_of_tiles[i][j] = state4[i][j];
            }
            else if (a == 5) {
                state_of_tiles[i][j] = state5[i][j];
            }
            else if (a == 6) {
                state_of_tiles[i][j] = state6[i][j];
            }
        }
    }
    this->count = 0;
}

// функція переміщення плитки залежно від напрямку
void Game::move_tile(int direction)
{
    puzzle15::position Positi0n;
    Positi0n = puzzle15::search_in(state_of_tiles, 0);

    if (direction == up)
    {
        if ((Positi0n.y) != 3)
        {
            std::swap(state_of_tiles[Positi0n.x][Positi0n.y], state_of_tiles[Positi0n.x][Positi0n.y + 1]);
            this->count++;
        }
    }

    if (direction == down)
    {
        if ((Positi0n.y) != 0)
        {
            std::swap(state_of_tiles[Positi0n.x][Positi0n.y], state_of_tiles[Positi0n.x][Positi0n.y - 1]);
            this->count++;
        }
    }

    if (direction == left)
    {
        if ((Positi0n.x) != 3)
        {
            std::swap(state_of_tiles[Positi0n.x][Positi0n.y], state_of_tiles[Positi0n.x + 1][Positi0n.y]);
            this->count++;
        }
    }

    if (direction == right)
    {
        if ((Positi0n.x) != 0)
        {
            std::swap(state_of_tiles[Positi0n.x][Positi0n.y], state_of_tiles[Positi0n.x - 1][Positi0n.y]);
            this->count++;
        }
    }
}
