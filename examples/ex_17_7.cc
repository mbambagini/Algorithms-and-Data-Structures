#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

string upper_postfix[] = {"", "thousand", "million", "billion"};
string decade_prefix[] = {"twenty", "thirty", "forty", "fifty", "sixty",
                          "seventy", "eighty", "ninety"};

//convert from a digit to a string
string convertDigitToString (int digit) {
  switch (digit){
    case 0: return "zero";
	case 1: return "one";
	case 2: return "two";
	case 3: return "three";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
  };
  return "---";
}

string convertLessThanThousand(int num) {
  if (num >= 0 && num <10)
    return convertDigitToString(num);
  if (num >= 10 && num <= 20) {
    switch (num) {
	  case 10: return "ten";
	  case 11: return "eleven";
	  case 12: return "twelve";
	  case 13: return "thirteen";
	  case 15: return "fifteen";
      default: return convertDigitToString(num%10)+"teen";
	}
  }
  if (num > 20 && num < 100) {
    string s = decade_prefix[num/10 - 2];
    if (num % 10)
      s += " " + convertDigitToString(num % 10);
    return s;
  }
  //num >= 100 && num < 1000
  return convertDigitToString(num/100) + " hundred " + 
         convertLessThanThousand(num % 100);
}

//the main idea consists of dividing the number of blocks of one thousand (3 
//digits) and treating them independently (followed by a specific postfix)
string convertIntegerToString (int num) {
  string s;
  int upper_level = 0;

  do {
    if (upper_postfix[upper_level].compare("") == 0)
	  s = convertLessThanThousand(num % 1000) + s;
	else
	  s = convertLessThanThousand(num % 1000) + " " +
          upper_postfix[upper_level] + " " + s;
    num /= 1000;
	upper_level++;
  } while (num != 0);

  return s;
}

int main () {
  assert(convertIntegerToString(         2).compare("two")==0);
  assert(convertIntegerToString(        12).compare("twelve")==0);
  assert(convertIntegerToString(       312).compare("three hundred twelve")==0);
  assert(convertIntegerToString(      1312).compare("one thousand three hundred twelve")==0);
  assert(convertIntegerToString(     54312).compare("fifty four thousand three hundred twelve")==0);
  assert(convertIntegerToString(    754312).compare("seven hundred fifty four thousand three hundred twelve")==0);
  assert(convertIntegerToString(   9754312).compare("nine million seven hundred fifty four thousand three hundred twelve")==0);
  assert(convertIntegerToString(  19754312).compare("nineteen million seven hundred fifty four thousand three hundred twelve")==0);
  assert(convertIntegerToString( 619754312).compare("six hundred nineteen million seven hundred fifty four thousand three hundred twelve")==0);
  assert(convertIntegerToString(2019754312).compare("two billion nineteen million seven hundred fifty four thousand three hundred twelve")==0);

  return 0;
}
