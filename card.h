// Author: Amos Gurung
// File: card.cpp
// Card class used to fill deck

#ifndef __CARD
#define __CARD
#include <iostream>
struct card
{
    //varialbes for cards
    int suit;
    int number;

    //overloaded operators
    bool operator==(const card& s){return s.suit==this->suit&&s.number==this->number;}
    bool operator>(const card& s){return this->number>s.number;}
    card& operator=(const card& s) {suit=s.suit; number=s.number; return *this;}
    friend std::ostream& operator << (std::ostream&, const card&);
};

#endif
