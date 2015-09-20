#include <iostream>
#include <assert.h>

using namespace std;

#define MAX_SIZE	4

enum KCOLOR {KBLACK, KWHITE};

bool checkBorder(KCOLOR matrix[MAX_SIZE][MAX_SIZE],
                int x, int y, int max_x, int max_y) {
  for (; x < max_x; x++)
    for (; y < max_y; y++)
      if (matrix[x][y] == KWHITE)
        return false;
  return true;
}

bool checkSquare(KCOLOR matrix[MAX_SIZE][MAX_SIZE], int x, int y, int size) {
  return checkBorder(matrix, x, y, x+size, y+1) &&           //upper side
         checkBorder(matrix, x, y+size-1, x+size, y+size) && //lower side
         checkBorder(matrix, x, y, x+1, y+size) &&           //left side
         checkBorder(matrix, x+size-1, y, x+size, y+size);   //right side
}

int searchMaxSquare (KCOLOR matrix[MAX_SIZE][MAX_SIZE], int length_border,
                     int x, int y) {

  int max = 0;

  if (length_border == 0)
   return (matrix[x][y] == KBLACK) ? 1 : 0;

  if (matrix[x][y] == KBLACK)
    for (int l = length_border; l > 0; l--)
      if (checkSquare(matrix, x, y, l) == true)
        return l;

  return 0;
}

int searchSquare (KCOLOR matrix[MAX_SIZE][MAX_SIZE], int length_border) {
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
  KCOLOR matrix[MAX_SIZE][MAX_SIZE] = {{KWHITE, KWHITE, KBLACK, KWHITE},
                                       {KBLACK, KBLACK, KBLACK, KBLACK},
                                       {KWHITE, KBLACK, KBLACK, KBLACK},
                                       {KWHITE, KBLACK, KBLACK, KBLACK},
                                      };

  assert(searchSquare(matrix, MAX_SIZE) == 3);

  matrix[3][2] = KWHITE;
  assert(searchSquare(matrix, MAX_SIZE) == 2);

  matrix[2][2] = KWHITE;
  assert(searchSquare(matrix, MAX_SIZE) == 1);

  return 0;
}

