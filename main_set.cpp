// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char **argc)
{
  if (argv < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> alice, bob;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    Card c;
    c.suit = line[0];         // first char is the suit
    c.value = line.substr(2); // everything after the space
    alice.insert(c);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0))
  {
    Card c;
    c.suit = line[0];
    c.value = line.substr(2);
    bob.insert(c);
  }
  cardFile2.close();
  // Alternate turns: Alice goes forward, Bob goes backward
  // Stop as soon as the current player finds no match
  bool foundMatch = true;
  bool aliceTurn = true;

  while (foundMatch)
  {
    foundMatch = false;

    if (aliceTurn)
    {
      // Alice: smallest → largest
      for (auto it = alice.begin(); it != alice.end(); ++it)
      {
        if (bob.count(*it))
        {
          cout << "Alice picked matching card " << *it << endl;
          Card match = *it; // save before erasing
          alice.erase(it);
          bob.erase(match);
          foundMatch = true;
          break;
        }
      }
    }
    else
    {
      // Bob: largest → smallest
      for (auto it = bob.rbegin(); it != bob.rend(); ++it)
      {
        if (alice.count(*it))
        {
          cout << "Bob picked matching card " << *it << endl;
          Card match = *it;
          bob.erase(match);
          alice.erase(match);
          foundMatch = true;
          break;
        }
      }
    }
    aliceTurn = !aliceTurn; // flip whose turn it is
  }

  cout << "\nAlice's cards:" << endl;
  for (const auto &c : alice)
    cout << c << endl;

  cout << "\nBob's cards:" << endl;
  for (const auto &c : bob)
    cout << c << endl;

  return 0;
}
