﻿#pragma once
#ifndef GAME_H
#define GAME_H

// головний клас програми, який визначає гру
class Game
{
public:
    Game(); // конструктор класу
    unsigned int count; // кількість переміщень у грі
    unsigned short int state_of_tiles[4][4];  // масив для збереження розмірності та позиції плит
    unsigned short int hard[4][4] =
    {
        {15,12,8,4},
        {14,11,7,3},
        {0,10,6,2},
        {13,9,5,1}
    };
    unsigned short int easy[4][4] =
    {
        {1,5,9,13},
        {2,6,10,0},
        {3,7,15,11},
        {4,8,12,14}
    };
    unsigned short int state1[4][4] =
    {
        {1,5,9,15},
        {2,6,10,14},
        {3,7,11,12},
        {4,8,13,0}
    };
    unsigned short int state2[4][4] =
    {
        {1,5,9,15},
        {7,14,6,0},
        {2,3,10,11},
        {4,8,12,13}
    };
    unsigned short int state3[4][4] =
    {
        {15,8,14,1},
        {5,12,9,0},
        {11,10,4,6},
        {2,7,13,3}
    };
    unsigned short int state4[4][4] =
    {
        {1,10,7,0},
        {6,2,8,9},
        {5,12,3,14},
        {13,11,15,4}
    };
    unsigned short int state5[4][4] =
    {
        {11,15,14,10},
        {4,9,12,2},
        {7,8,5,3},
        {1,0,13,6}
    };
    unsigned short int state6[4][4] =
    {
        {7,2,3,13},
        {0,9,8,6},
        {15,14,11,10},
        {5,1,12,4}
    };
    void solve(bool &flag);   // функція розв'язку гри (повернення позиції плит у розв'язане положення)
    void scramble();    // функція генерації позиції плит рандомізованим чином
    enum  // перелік позицій переміщення
    {
        up = 1,
        down = 2,
        left = 3,
        right = 4
    };

    void move_tile(int direction);  // функція переміщення плитки залежно від напрямку
};

#endif // GAME_H