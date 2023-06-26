#pragma once
#include <fstream>
#include <iostream>
#include "graphics.h"


const int MAX_COST = 100;
class PuzzleState {
public:
    unsigned short int puzzle[4][4];

    int zeroRow, zeroCol;
};
// Function to calculate the Manhattan distance heuristic
int calculateHeuristic(const PuzzleState& state) {
    int heuristic = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (state.puzzle[i][j] != 0) {
                int expectedRow = (state.puzzle[i][j] - 1) / 4;
                int expectedCol = (state.puzzle[i][j] - 1) % 4;
                heuristic += abs(i - expectedRow) + abs(j - expectedCol);
            }
        }
    }
    return heuristic;
}

// Function to check if the puzzle is solved
bool isPuzzleSolved(const PuzzleState& state) {
    int value = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (state.puzzle[i][j] != value && value != 4 * 4) {
                return false;
            }
            ++value;
        }
    }
    return true;
}

// Function to make a move (swap the empty space with a neighboring tile)
void makeMove(PuzzleState& state, int row, int col, int newRow, int newCol, unsigned short int (*state_of_tiles)[4][4]) {
    std::swap(state.puzzle[row][col], state.puzzle[newRow][newCol]);
    std::swap(state_of_tiles[newRow][newCol], state_of_tiles[row][col]);
    //window.clear();
    set_position_of_tiles(*state_of_tiles);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            window.draw(tile[i][j]);
        }
    }
    window.display();
    state.zeroRow = newRow;
    state.zeroCol = newCol;
}

// Function to perform IDA* search
bool IDAStar(PuzzleState& state, int g, int threshold, int& minCost, unsigned short int (*state_of_tiles)[4][4]) {
    int h = calculateHeuristic(state);
    int f = g + h;
    if (f > threshold) {
        minCost = std::min(minCost, f);
        return false;
    }
    if (isPuzzleSolved(state)) {
        return true;
    }

    int minCostNext = MAX_COST;
    const int dr[] = { 1, -1, 0, 0 };
    const int dc[] = { 0, 0, 1, -1 };
    for (int dir = 0; dir < 4; ++dir) {
        int newRow = state.zeroRow + dr[dir];
        int newCol = state.zeroCol + dc[dir];
        if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4) {
            makeMove(state, state.zeroRow, state.zeroCol, newRow, newCol, state_of_tiles);
            if (IDAStar(state, g + 1, threshold, minCostNext, state_of_tiles)) {
                return true;
            }
            makeMove(state, newRow, newCol, state.zeroRow, state.zeroCol, state_of_tiles);
        }
    }
    minCost = minCostNext;
    return false;
}

// Function to solve the 15 puzzle using IDA* algorithm
bool solvePuzzle(PuzzleState& state, unsigned short int (*state_of_tiles)[4][4]) {
    int threshold = calculateHeuristic(state);
    int minCost = threshold;
    while (true) {
        if (IDAStar(state, 0, threshold, minCost, state_of_tiles)) {
            return true;
        }
        if (minCost == MAX_COST) {
            return false;
        }
        threshold = minCost;
        minCost = MAX_COST;
    }
}