#include <iostream>
#include <chrono>
#include "timer.h"

int main()
{
    constexpr int ROW_SIZE = 10000;
    constexpr int COLUMN_SIZE = 10000;
    int **matrix = new int*[ROW_SIZE];
    for (int i = 0; i < ROW_SIZE; ++i) {
        matrix[i] = new int[COLUMN_SIZE];
        for (int j = 0; j < COLUMN_SIZE; ++j) {
            matrix[i][j] = i + j;
        }
    }
    {
        Timer time_col;
        volatile uint64_t col_sum = 0;
        for (int j = 0; j < COLUMN_SIZE; ++j) {
            for (int i = 0; i < ROW_SIZE; ++i) {
                col_sum += matrix[i][j];
            }
        }
        std::cout << "Sum by col: " << col_sum << std::endl;
    }
    for (int i = 0; i < ROW_SIZE; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0; 
}