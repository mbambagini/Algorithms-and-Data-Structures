#include <iostream>
#include <assert.h>
#include <set>
#include <string>

using namespace std;


bool find (const set<string> &dictionary, string start, string finish,
           set<string> &visited) {
  if (start.compare(finish) == 0)
    return true;

  visited.insert(start);

  for (int i = 0; i < start.size(); i++) {
    for (char c = 'a'; c <= 'z'; c++) {
      string possible_new_string = start;
      possible_new_string[i] = c;
      if (dictionary.count(possible_new_string) == 0 ||
          visited.count(possible_new_string) == 1)
        continue;
      if (possible_new_string.compare(finish) == 0)
        return true;
      if (find(dictionary, possible_new_string, finish, visited))
        return true;
    }
  }

  return false;
}


bool find (const set<string> &dictionary, string start, string finish) {
  set<string> visited;
  return find(dictionary, start, finish, visited);
}


int main () {
  set<string> dictionary;
  dictionary.insert("text");
  dictionary.insert("test");
  dictionary.insert("fest");
  dictionary.insert("fast");
  dictionary.insert("cast");
  dictionary.insert("cart");
  dictionary.insert("rest");
  dictionary.insert("rast");
  dictionary.insert("rasp");
  dictionary.insert("ramp");
  dictionary.insert("pppp");

  assert(find(dictionary, "text", "pppp")==0);
  assert(find(dictionary, "rasp", "cart")==1);
  assert(find(dictionary, "text", "ramp")==1);

  return 0;
}

