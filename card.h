// card.h
// Author: Zhe Wang
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>

class Card
{
public:
    char suit;
    std::string value;

    Card();
    Card(char s, const std::string &v);

    // Return a number 0~3 for suit, 0~12 for value
    int suitRank() const;
    int valueRank() const;

    bool operator<(const Card &other) const;
    bool operator>(const Card &other) const;
    bool operator==(const Card &other) const;
    bool operator!=(const Card &other) const;
};

std::ostream &operator<<(std::ostream &os, const Card &c);
std::istream &operator>>(std::istream &is, Card &c);

#endif
