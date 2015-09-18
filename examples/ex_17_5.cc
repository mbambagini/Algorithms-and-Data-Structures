#include <iostream>
#include <assert.h>

using namespace std;

#define SIZE	4

enum Values {EMPTY, RED, GREEN, BLUE, YELLOW};

struct GuessResults {
  int num_guess;
  int num_pseudo_guess;
  GuessResults () {
    num_guess = num_pseudo_guess = 0;
  }
};

GuessResults checkGuess (Values solution[SIZE], Values guess[SIZE]) {
  GuessResults res;

  //find guesses
  for (int i = 0; i < SIZE; i++)
    if (solution[i] == guess[i]) {
	  solution[i] = guess[i] = EMPTY;
	  res.num_guess++;
	}

  //find pseudo_guess
  for (int i = 0; i < SIZE; i++) {
    if (guess[i] != EMPTY) {
      for (int j = 0; j < SIZE; j++)
        if (solution[j] != EMPTY && solution[j] == guess[i]) {
	      solution[j] = guess[i] = EMPTY;
		  res.num_pseudo_guess++;
        }
    }
  }

  return res;
}

int main () {
  Values solution_generic[] = {RED, GREEN, BLUE, YELLOW};
  Values guess_generic[] = {GREEN, GREEN, RED, RED};
  GuessResults results = checkGuess(solution_generic, guess_generic);
  assert(results.num_guess == 1 && results.num_pseudo_guess == 1);

  Values solution_equal[] = {GREEN, GREEN, GREEN, GREEN};
  Values guess_equal[] = {GREEN, GREEN, GREEN, GREEN};
  results = checkGuess(solution_equal, guess_equal);
  assert(results.num_guess == 4 && results.num_pseudo_guess == 0);

  return 0;
}
