#include <iostream>
#include <assert.h>
#include <string.h>
#include <set>

using namespace std;

bool validCharacter(char c) {
  switch(c) {
    case ' ':
    case ',':
    case '.':
    case ';':
    case ':':
    case '?':
    case '!':
      return false;
  }
  return true;
}

void parse (multiset<string> &counter, const char* text) {
  int i = 0;
  int start = 0;
  int size = strlen(text);
  bool finding_end = false;

  while (i < size) {
    if(validCharacter(text[i])) {
      if (!finding_end) {
        start = i;
        finding_end = true;
      }
    } else {
      if (finding_end) {
        counter.insert(string(&text[start], i-start));
        finding_end = false;
      }
    }
    i++;
  }
}


int main () {
  const char *text = "this is a simple text to show how the algoritms works" \
                     "with respect to the parsing and counting problems. "\
                     "have fun!! the word is bird";
  multiset<string> counter;
  parse(counter, text);
  assert(counter.count("the") == 3);
  assert(counter.count("to") == 2);
  assert(counter.count("fun") == 1);

  return 0;
}

