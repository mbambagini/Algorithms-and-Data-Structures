#include <iostream>
#include <assert.h>

using namespace std;

#define MAX_SIZE	4

int computeBorder(int matrix[MAX_SIZE][MAX_SIZE], int x, int y, int offset) {
  int sum = matrix[x+offset][y+offset];
  for (int i = 0; i < offset; i++) {
    sum += matrix[x+i][y+offset];
    sum += matrix[x+offset][y+i];
  }
  return sum;
}

int searchMaxSquare (int matrix[MAX_SIZE][MAX_SIZE], int length_border,
                     int x, int y) {

  int max = matrix[x][y];
  int actual = max;

  for (int l = 1; l < length_border; l++) {
    actual += computeBorder(matrix, x, y, l);
    if (actual > max)
      max = actual;
  }

  return max;
}

int searchSquare (int matrix[MAX_SIZE][MAX_SIZE], int length_border) {
  int max = 0;

  for (int x = 0; x < length_border; x++)
    for (int y = 0; y < length_border; y++) {
      int tmp = searchMaxSquare(matrix, length_border-((x>y)?x:y), x, y);
      if (tmp > max)
        max = tmp;
    }

  return max;
}

int main () {
  int matrix[MAX_SIZE][MAX_SIZE] = {{ 4,  2,  4,  0},
                                    {-1, -5,  2,  1},
                                    {-2,  9,  3,  3},
                                    { 5, -9,  1,  0},
                                   };

  assert(searchSquare(matrix, MAX_SIZE) == 19); //(0, 1), size = 3
  matrix[0][4] = 20;
  assert(searchSquare(matrix, MAX_SIZE) == 38); //(0, 0), size = 4

  return 0;
}

