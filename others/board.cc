//A board is composed of N rows and M columns whose cells contain either O or X.
//At each turn, the player can toggle all values of a row.
//Return the maximum square of all Os the user can reach after a sequence of row
//toggling
//
//This is a classical problem and the problem space is 2^N: all possible
//combinations of row flips.

#include <vector>
#include <string>
#include <math.h>
#include <assert.h>

using namespace std;

class BoardGame {
 public:
  int findMaxArea (vector <string> board);
 private:
  int analize(vector <string> board, int command);
  int computeArea (const vector<string>& board);
  bool checkAllWhite (const vector<string>& board, int x, int y, int side);
  void flip(string& row);
};

int BoardGame::findMaxArea(vector <string> board) {
  int num_combinations = pow(2, board.size());
  int max_area = 0;
  for (int i = 0; i < num_combinations; i++) {
    int actual_area = analize(board, i);
    if (actual_area > max_area)
      max_area = actual_area;
  }
  return max_area;
}

void BoardGame::flip(string& row) {
  for (int i = 0; i < row.size(); i++)
    row[i] = ( row[i] == 'X') ? row[i] = 'O' : row[i] = 'X';
}

bool BoardGame::checkAllWhite (const vector<string>& board,
                               int x, int y, int side) {
  for (int i = 0; i <= side; i++)
    for (int j = 0; j <= side; j++)
      if (board[x+i][y+j] == 'X')
        return false;
  return true;
}

int BoardGame::computeArea (const vector<string>& board) {
  int max_area = 0;
  for (int x = 0; x < board.size(); x++)
    for (int y = 0; y < board[x].size(); y++)
      for (int size = 0;
           board[x][y] == 'O' && (x+size) < board.size() &&
           (y + size) < board[x].size();
           size++)
        if (checkAllWhite(board, x, y, size) && ((size+1)*(size+1))>max_area)
          max_area = (size+1)*(size+1);
  return max_area;
}

int BoardGame::analize(vector <string> board, int command) {
  int id = 0;

  while (command != 0 && id < board.size()) {
    if (command & 0x01)
      flip(board[id++]);
    command = command / 2;
  }

  return computeArea(board);
}

int main () {
  BoardGame g;

  vector<string> board1(1);
  board1[0] = "X";
  assert(g.findMaxArea(board1) == 1);
  board1[0] = "O";
  assert(g.findMaxArea(board1) == 1);

  vector<string> board2(2);
  board2[0] = "XX"; board2[1] = "OO";
  assert(g.findMaxArea(board2) == 4);

  vector<string> board(5);
  board[0] = "XOOOXOX"; board[1] = "OXXXOOO"; board[2] = "OXXXXXX";
  board[3] = "OXOOOOO"; board[4] = "XOOOOXX";
  assert(g.findMaxArea(board) == 9);

  return 0;
}

