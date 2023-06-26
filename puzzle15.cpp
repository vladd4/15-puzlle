#include "puzzle15.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


namespace puzzle15 {
    unsigned short int normal_state[4][4] =
    {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,0}
    };
    // функція пошуку позиції вказаної плитки
    position search_in(short unsigned int state[4][4], const int number)
    {
        position Pos;
        int i = 0, j = 0;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (state[i][j] == number)
                {
                    Pos.x = i;
                    Pos.y = j;

                    return Pos;
                }
            }
        }
    }
}
// функція запису даних у вихідний файл
void write_in_file(unsigned int count, std::string operation) {
    std::fstream file;
    file.open("output.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout << 'ops';
    }
    else {
        file << "You pressed " << operation << "." << " K-ct operations: " << count << std::endl;
    }
    file.close();
} 

void transposeMatrix(unsigned short int matrix[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}

int getInvCount(unsigned short int array[]) {
    int int_count = 0;
    for (int i = 0; i < 4 * 4 - 1; i++) {
        for (int j = i + 1; j < 4 * 4; j++) {
            if (array[j] && array[i] && array[i > array[j]])
                int_count++;
        }
    }
    return int_count;
}

int findXPosition(unsigned short int puzzle[4][4]) {
    for (int i = 4-1; i >= 0; i--) {
        for (int j = 4-1; j >= 0; j--) {
            if (puzzle[i][j] == 0)
                return 4 - i;
        }
    }
}

bool isSolvable(unsigned short int puzzle[4][4]) {
    int int_count = getInvCount((unsigned short int*)puzzle);

    if (4 & 1) // непарна
        return !(int_count & 1); // парна
    else {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(int_count & 1);
        else
            return int_count & 1;
    }
}