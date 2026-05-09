// card.cpp
// Author: Zhe Wang
// Implementation of the classes defined in card.h
#include "card.h"
#include <string>
#include <iostream>
using namespace std;

Card::Card() : suit('c'), value("a") {}
Card::Card(char s, const string &v) : suit(s), value(v) {}

int Card::suitRank() const
{
    switch (suit)
    {
    case 'c':
        return 0;
    case 'd':
        return 1;
    case 's':
        return 2;
    default:
        return 3;
    }
}

int Card::valueRank() const
{
    if (value == "a")
        return 0;
    if (value == "2")
        return 1;
    if (value == "3")
        return 2;
    if (value == "4")
        return 3;
    if (value == "5")
        return 4;
    if (value == "6")
        return 5;
    if (value == "7")
        return 6;
    if (value == "8")
        return 7;
    if (value == "9")
        return 8;
    if (value == "10")
        return 9;
    if (value == "j")
        return 10;
    if (value == "q")
        return 11;
    return 12;
}

bool Card::operator<(const Card &other) const
{
    if (suitRank() != other.suitRank())
        return suitRank() < other.suitRank();
    return valueRank() < other.valueRank();
}

bool Card::operator>(const Card &other) const
{
    return other < *this;
}

bool Card::operator==(const Card &other) const
{
    return suit == other.suit && value == other.value;
}

bool Card::operator!=(const Card &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Card &c)
{
    os << c.suit << " " << c.value;
    return os;
}

istream &operator>>(istream &is, Card &c)
{
    is >> c.suit >> c.value;
    return is;
}