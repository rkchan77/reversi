
/**
 * @brief This is a header file for your Lab 8 solutions, which includes all
 * the required function prototypes.
 * Please note: this file should not be modified.
 * Date: 2023-03-14
 */
#ifndef REVERSI_H
#define REVERSI_H
#include <stdbool.h>
// Function prototypes for Lab 7
void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
// Function prototypes for Lab 8 Part2
int makeMove(char board[26][26], int n, char turn, int *row, int *col);
#endif
