#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Solver {
private:
    int n;// поточний індекс переміщень, крок 
    int n_checked; // кількість перевіриних станів плиток (розміщень)
    int n_zero[100]; // зберігає позицію пустої клітки для кожного кроку
    unsigned long long puzzle_16[100]; // представляє значення масиву[4][4] в шістнадцятковому форматі
    char n_moves[100];
    int n_other[100]; // використовується для визначення кількості плиток, які знаходяться в неправильній позиції на кожному кроці
    int n_rows[16]; // row 
    int n_cols[16]; // col
    std::ofstream outputFile;
    bool& flagRef;  // відстеження для додаткового вікна

public:
    Solver(const unsigned short int values[4][4], bool &flag) : flagRef(flag) {
        n = 0;
        n_checked = 0;
        std::fill_n(n_zero, 100, 0);
        std::fill_n(puzzle_16, 100, 0);
        std::fill_n(n_moves, 100, 0);
        std::fill_n(n_other, 100, 0);
        // вказують на номер рядка та колонки значенб від 0 до 15
        std::copy_n(new int[16] { 3, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3 }, 16, n_rows); // row
        std::copy_n(new int[16] { 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2 }, 16, n_cols); // col
        outputFile.open("solution.txt", std::ios::app); 

        n_zero[0] = std::distance(&values[0][0], std::find(&values[0][0], &values[0][0] + 16, 0)); 

        unsigned long long tmp = 0;
        for (int i = 0; i < 16; ++i) {
            tmp = (tmp << 4) | values[i / 4][i % 4]; // i/4 - номер рядка, i%4 - номер стопвця
        }
        puzzle_16[0] = tmp;
    }

    ~Solver() {
        outputFile.close();
        flagRef = false;
    }

    void f_down() {
        int n_ = n;
        int g = (11 - n_zero[n_]) * 4; // представляє кількість позицій, на яку треба зсунути значення пустої клітинки вниз
        unsigned long long a = puzzle_16[n_] & (static_cast<unsigned long long>(15) << g); // представляє значення плитки, яка знаходиться знизу 0
        n_zero[n_ + 1] = n_zero[n_] + 4; // оновлюємо індекс пустої клітинки додаємо + 4 бо переміщаємо на одну позицію вниз
        puzzle_16[n_ + 1] = puzzle_16[n_] - a + (a << 16); 
        n_moves[n_ + 1] = 'd'; 
        n_other[n_ + 1] = n_other[n_] + static_cast<int>(n_rows[a >> g] > n_zero[n_] / 4); // нова кількість плиток, в неправильній позиції
    }

    void f_up() {
        int n_ = n;
        int g = (19 - n_zero[n_]) * 4;
        unsigned long long a = puzzle_16[n_] & (static_cast<unsigned long long>(15) << g);
        n_zero[n_ + 1] = n_zero[n_] - 4;
        puzzle_16[n_ + 1] = puzzle_16[n_] - a + (a >> 16); 
        n_moves[n_ + 1] = 'u';
        n_other[n_ + 1] = n_other[n_] + static_cast<int>(n_rows[a >> g] < n_zero[n_] / 4); // n_rows[a >> g] - видає номер рядка плитки вище 0,  n_zero[n_] / 4 - позиція 0
    }

    void f_right() {
        int n_ = n;
        int g = (14 - n_zero[n_]) * 4;
        unsigned long long a = puzzle_16[n_] & (static_cast<unsigned long long>(15) << g);
        n_zero[n_ + 1] = n_zero[n_] + 1;
        puzzle_16[n_ + 1] = puzzle_16[n_] - a + (a << 4); 
        n_moves[n_ + 1] = 'r';
        n_other[n_ + 1] = n_other[n_] + static_cast<int>(n_cols[a >> g] > n_zero[n_] % 4);
    }

    void f_left() {
        int n_ = n;
        int g = (16 - n_zero[n_]) * 4;
        unsigned long long a = puzzle_16[n_] & (static_cast<unsigned long long>(15) << g);
        n_zero[n_ + 1] = n_zero[n_] - 1;
        puzzle_16[n_ + 1] = puzzle_16[n_] - a + (a >> 4);
        n_moves[n_ + 1] = 'l';
        n_other[n_ + 1] = n_other[n_] + static_cast<int>(n_cols[a >> g] < n_zero[n_] % 4);
    }

    bool f_ready() {
        if (puzzle_16[n] == 0x123456789ABCDEF0ULL) // чи дорівнює позиція вирішеній 
            return true;

        if (n_other[n] <= n_checked) // перевірка, чи існує можливість знайти розв'язок. 
            return fN();

        return false;
    }

    bool fN() {
        int n_ = n;

        if (n_moves[n_] != 'u' && n_zero[n_] / 4 < 3) { 
            f_down();
            n++;
            if (f_ready())
                return true;
            n--;
        }

        if (n_moves[n_] != 'd' && n_zero[n_] / 4 > 0) {
            f_up();
            n++;
            if (f_ready())
                return true;
            n--;
        }

        if (n_moves[n_] != 'l' && n_zero[n_] % 4 < 3) {
            f_right();
            n++;
            if (f_ready())
                return true;
            n--;
        }

        if (n_moves[n_] != 'r' && n_zero[n_] % 4 > 0) {
            f_left();
            n++;
            if (f_ready())
                return true;
            n--;
        }

        return false;
    }
    void run() {
        while (!f_ready())
            n_checked++; // якщо не вирішено, збільшуємо кількість перевірених станів

        outputFile << "Solution found with " << n << " moves: ";
        for (int i = 1; i<= n; ++i)
            outputFile << n_moves[i] << " ";
        outputFile << "." << std::endl;

    }

    void printCurrentPosition() {
        outputFile << "Current Position:" << std::endl;
        outputFile << "+---+---+---+----+" << std::endl;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int value = (puzzle_16[n] >> ((15 - (4 * i + j)) * 4)) & 0xF; // (15 - (4 * i + j)) * 4) визначає кількість позицій на яку треьа змістити вправо & 0xF - вилучає нижні 4 біти(наше число)
                if (value == 0)
                    outputFile << "|   ";
                else
                    outputFile << "|" << std::setw(2) << value << " ";
            }
            outputFile << "|" << std::endl;
            outputFile << "+---+---+---+----+" << std::endl;
        }
        
    }
};