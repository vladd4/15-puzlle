#pragma once
#ifndef PUZZLE15_H
#define PUZZLE15_H
#include <fstream>
#include <iostream>


namespace puzzle15 { // використання простору імен puzzle15

    // клас, який представляє кординати позиції
    class position
    {
    public:
        int x, y;
    };

    position search_in(short unsigned int state[4][4], const int number);   // функція пошуку позиції вказаної плитки
}

void write_in_file(unsigned int count, std::string operation);  // функція запису даних у вихідний файл
int getInvCount(unsigned short int array[]);
int findXPosition(unsigned short int puzzle[4][4]);
bool isSolvable(unsigned short int puzzle[4][4]);
void transposeMatrix(unsigned short int matrix[4][4]);
#endif
