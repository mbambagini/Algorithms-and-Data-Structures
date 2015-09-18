#include <iostream>
#include <assert.h>

using namespace std;

#define SIZE	3

enum CELL {EMPTY, FIRST_PLAYER, SECOND_PLAYER};

/*
bool check (CELL matrix[SIZE][SIZE]) {
  //first row
  if (matrix[0][0] == matrix[0][1] &&
      matrix[0][1] == matrix[0][2] &&
	  matrix[0][0] != EMPTY)
    return true;
  //second row
  if (matrix[1][0] == matrix[1][1] &&
      matrix[1][1] == matrix[1][2] &&
	  matrix[1][0] != EMPTY)
    return true;
  //third row
  if (matrix[2][0] == matrix[2][1] &&
      matrix[2][1] == matrix[2][2] &&
	  matrix[2][0] != EMPTY)
    return true;
  //first column
  if (matrix[0][0] == matrix[1][0] &&
      matrix[1][0] == matrix[2][0] &&
	  matrix[0][0] != EMPTY)
    return true;
  //second column
  if (matrix[0][1] == matrix[1][1] &&
      matrix[1][1] == matrix[2][1] &&
	  matrix[0][1] != EMPTY)
    return true;
  //third column
  if (matrix[0][2] == matrix[1][2] &&
      matrix[1][2] == matrix[2][2] &&
	  matrix[0][2] != EMPTY)
    return true;
  //first diagonal
  if (matrix[0][0] == matrix[1][1] &&
      matrix[1][1] == matrix[2][2] &&
	  matrix[0][0] != EMPTY)
    return true;
  //second diagonal
  if (matrix[2][0] == matrix[1][1] &&
      matrix[1][1] == matrix[0][2] &&
	  matrix[0][2] != EMPTY)
    return true;

  return false;  
}
*/

bool condition_check (CELL matrix[SIZE][SIZE],
                      int x_start, int x_step, int y_start, int y_step) {
  int x = x_start + x_step;
  int y = y_start + y_step;

  CELL cell = matrix[x_start][y_start];
  if (cell == EMPTY)
    return false;

  for (int i = 0; i < (SIZE - 1); i++, x+=x_step, y+=y_step)
    if (cell != matrix[x][y])
	  return false;
  return true;
}											   
											   
bool check (CELL matrix[SIZE][SIZE]) {
  
  if (condition_check(matrix, 0, 0, 0, 1) || //first row
      condition_check(matrix, 1, 0, 0, 1) || //second row
      condition_check(matrix, 2, 0, 0, 1) || //third row
      condition_check(matrix, 0, 1, 0, 0) || //first column
      condition_check(matrix, 0, 1, 1, 0) || //second column
      condition_check(matrix, 0, 1, 2, 0) || //third column
      condition_check(matrix, 0, 1, 0, 1) || //first diagonal
      condition_check(matrix, 0, 1, 2, -1))  //second diagonal
    return true;
  return false;
}

int main () {
  CELL no_winner[SIZE][SIZE] = {FIRST_PLAYER,  FIRST_PLAYER,  SECOND_PLAYER,
                                SECOND_PLAYER, SECOND_PLAYER, FIRST_PLAYER,
								FIRST_PLAYER,  FIRST_PLAYER,  SECOND_PLAYER};
  CELL winner_col[SIZE][SIZE] = {FIRST_PLAYER,  FIRST_PLAYER,  SECOND_PLAYER,
                                 FIRST_PLAYER,  SECOND_PLAYER, FIRST_PLAYER,
								 FIRST_PLAYER,  FIRST_PLAYER,  SECOND_PLAYER};
  CELL winner_diag[SIZE][SIZE] = {FIRST_PLAYER,  FIRST_PLAYER,  SECOND_PLAYER,
                                  FIRST_PLAYER,  SECOND_PLAYER, FIRST_PLAYER,
                                  SECOND_PLAYER, FIRST_PLAYER,  SECOND_PLAYER};
  CELL winner_diag2[SIZE][SIZE] = {FIRST_PLAYER,  SECOND_PLAYER, SECOND_PLAYER,
                                   SECOND_PLAYER, FIRST_PLAYER,  SECOND_PLAYER,
                                   SECOND_PLAYER, FIRST_PLAYER,  FIRST_PLAYER};
  CELL winner_row[SIZE][SIZE] = {FIRST_PLAYER,  FIRST_PLAYER,  FIRST_PLAYER,
                                 SECOND_PLAYER, SECOND_PLAYER, FIRST_PLAYER,
								 FIRST_PLAYER,  SECOND_PLAYER, SECOND_PLAYER};

  assert(check(no_winner) == false);
  assert(check(winner_col) == true);
  assert(check(winner_diag) == true);
  assert(check(winner_diag2) == true);
  assert(check(winner_row) == true);
  
  return 0;
}
