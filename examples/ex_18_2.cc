#include <iostream>
#include <assert.h>
#include <deque>
#include <stdlib.h>

using namespace std;

//all kind of card figures
enum KCARD {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, 
            QUEEN, KING, CARD_NOT_VALID};

//all kind of seeds
enum KSEED {HEARTS, DIAMONDS, FLOWERS, SPADES, SEED_NOT_VALID};

KCARD operator++ (KCARD &c) {
  assert(c >= ACE && c <= CARD_NOT_VALID);
  c = static_cast<KCARD>(c+1);
  return c;
}

KSEED operator++ (KSEED &s) {
  assert(s >= HEARTS && s <= SEED_NOT_VALID);
  s = static_cast<KSEED>(s+1);
  return s;
}

//card representation
class Card {
 public:
  Card (): figure_(ACE), seed_(HEARTS) {}
  Card (KCARD figure, KSEED seed) : figure_(figure), seed_(seed) { }
  //return the card figure
  KCARD figure () { return figure_; }
  //return the card seed
  KSEED seed () { return seed_; }

 private:
  //card figure
  KCARD figure_;
  //card seed
  KSEED seed_;
};

//the idea consists of picking a card randomly from the original deque and
//moving it in a new deque
//time complexity O(N^2) where N is the number of cards
//space complexity O(N)
void shuffleDeque (deque<Card> &cards) {
  deque<Card> new_deque;

  while (cards.size() > 0) {
    int index = rand() % cards.size();
    new_deque.push_back(cards[index]);
    cards.erase(cards.begin()+index);
  }
  cards = new_deque;
}

//the idea consists of picking a card randomly and swaping it with another one
//on its left
//time complexity O(N) where N is the number of cards
//space complexity O(1)
void recursiveShuffleDeque (deque<Card> &cards, int i = 52) {
  if (i == 0) return;

  recursiveShuffleDeque(cards, i-1);

  int id = rand() % i;

  Card tmp = cards[i];
  cards[i] = cards[id];
  cards[id] = cards[i];
}

int main () {
  srand(time(0));

  deque<Card> cards, original_deque;
  for (KSEED i = HEARTS; i <= SPADES; ++i)
    for (KCARD j = ACE; j <= KING; ++j)
      cards.push_back(Card(j, i));
  original_deque = cards;

  //shuffleDeque(cards);
  recursiveShuffleDeque(cards);

  assert(cards.size() == 52);

  int count_equal = 0;
  for (int i = 0; i < cards.size(); i++)
    if (cards[i].seed() == original_deque[i].seed() &&
        cards[i].figure() == original_deque[i].figure())
      count_equal++;

  assert(count_equal <= 5);

  return 0;
}

