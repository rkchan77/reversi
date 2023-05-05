//
// Author: Ryan Chan
//

#include "reversi.h"

#include <stdio.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int i, int j);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);

void movesAvailable(char board[][26], int n, char colour);
bool validInput(char board[][26], int n, char colour, char row, char col);
void swapColours(char board[][26], int n, int row, int col, char colour);

int main(void) {
  int n;
  printf("Enter the board dimension: ");
  scanf("%d", &n);

  // Declare static 2D array of size nxn
  char board[n][26];

  // Initialize board
  int half_1 = n / 2 - 1;
  int half_2 = n / 2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i == half_1 && j == half_1) || (i == half_2 && j == half_2)) {
        board[i][j] = 'W';
      } else if ((i == half_1 && j == half_2) || (i == half_2 && j == half_1)) {
        board[i][j] = 'B';
      } else {
        board[i][j] = 'U';
      }
    }
  }

  printBoard(board, n);

  // Get intermediate board configuration
  char colour, row, column;
  printf("Enter board configuration:\n");

  while (colour != '!' || row != '!' || column != '!') {
    scanf(" %c%c%c", &colour, &row, &column);
    board[row - 'a'][column - 'a'] = colour;
  }

  printBoard(board, n);

  // Get available moves for black
  movesAvailable(board, n, 'W');

  // Get available moves for white
  movesAvailable(board, n, 'B');

  // Get user input
  printf("Enter a move:\n");
  scanf(" %c%c%c", &colour, &row, &column);

  // Check validity of user input
  if (validInput(board, n, colour, row, column)) {
    printf("Valid move.\n");
    swapColours(board, n, row - 'a', column - 'a', colour);
    board[row - 'a'][column - 'a'] = colour;
  } else {
    printf("Invalid move.\n");
  }
  // Swap colours

  printBoard(board, n);
  return 0;
}

void printBoard(char board[][26], int n) {
  printf("  ");
  for (int k = 0; k < n; k++) {
    int header = k + 97;
    printf("%c", (char)header);
  }

  printf("\n");

  for (int i = 0; i < n; i++) {
    int header = i + 97;
    printf("%c ", (char)header);
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int i, int j) {
  if (i < 0 || j < 0 || i >= n || j >= n) {
    return false;
  } else {
    return true;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  char opp;
  if (colour == 'B') {
    opp = 'W';
  } else if (colour == 'W') {
    opp = 'B';
  }

  // If selected space is not empty OR if space directly touching selected space
  // is the same colour OR if selected space is not within the bounds
  if (board[row][col] != 'U' || !positionInBounds(n, row, col)) {
    return false;
  }

  // Make space counter for different radii
  int step = 1;

  while ((positionInBounds(n, row + deltaRow * step, col + deltaCol * step)) &&
         board[row + deltaRow * step][col + deltaCol * step] == opp) {
    step++;
    if (!positionInBounds(n, row + deltaRow * step, col + deltaCol * step) ||
        board[row + deltaRow * step][col + deltaCol * step] == 'U') {
      return false;
    }
    if (positionInBounds(n, row + deltaRow * step, col + deltaCol * step) &&
        board[row + deltaRow * step][col + deltaCol * step] == colour) {
      return true;
    }
  }
  return false;
}

void movesAvailable(char board[][26], int n, char colour) {
  printf("Available moves for %c:\n", colour);

  // Go through each column in every row
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Check all positions touching empty space

      if (validInput(board, n, colour, (char)(i + 97), (char)(j + 97))) {
        printf("%c%c\n", (char)(i + 97), (char)(j + 97));
      }
      // for (int k = -1; k <= 1; k++) {
      //   for (int l = -1; l <= 1; l++) {
      //     if (k == 0 && l == 0) {
      //       continue;
      //     }
      //     if (checkLegalInDirection(board, n, i, j, colour, k, l)) {
      //       printf("%c%c\n", (char)(i + 97), (char)(j + 97));
      //       break;
      //     }
      //   }
      // }
    }
  }
}

bool validInput(char board[][26], int n, char colour, char row, char col) {
  if (positionInBounds(n, row - 'a', col - 'a') == false ||
      board[row - 'a'][col - 'a'] != 'U') {
    return false;
  }
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(board, n, row - 'a', col - 'a', colour, k, l)) {
        return true;
      }
    }
  }
  return false;
}

void swapColours(char board[][26], int n, int row, int col, char colour) {
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      if (k == 0 && l == 0) {
        continue;
      }
      if (checkLegalInDirection(board, n, row, col, colour, k, l)) {
        int tempk = k;
        int templ = l;
        while (positionInBounds(n, row + tempk, col + templ) &&
               board[row + tempk][col + templ] != 'U' &&
               board[row + tempk][col + templ] != colour) {
          board[row + tempk][col + templ] = colour;
          tempk += 1 * k;
          templ += 1 * l;
        }
      }
    }
  }
}
