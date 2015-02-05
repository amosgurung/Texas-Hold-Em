// Author: Amos Gurung
// File: deck.cpp
// Implementation of deck class
#include "deck.h"
#include <vector>
#include <iostream>
#include <algorithm>

void deck::filldeck()
{
    //suits are from 0-3
    //nums are from 0-12 ace=12
    for(int suits = 0; suits < 4; suits++)
    {
        for(int nums=0;nums < 13; nums++)
        {
            card mycard;
            mycard.number=nums;
            mycard.suit=suits;
            mydeck.push_back(mycard);
        }
    }
}

void deck::displaydeck()
{
    for(unsigned int i=0;i < mydeck.size();i++)
    {
        if(i%13 ==0)
            std::cout<<std::endl;
        std::cout <<'('<<mydeck[i].number;
        std::cout << mydeck[i].suit<<')';
    }
}

void deck::shuffle()
{
    std::random_shuffle(mydeck.begin(),mydeck.end());
}

card deck::getcard()
{
    card temp = mydeck.back();
    mydeck.pop_back();
    return temp;
}

card deck::getscard(int loc)
{
    card temp = mydeck[loc];
    mydeck.erase(mydeck.begin()+loc);
    return temp;
}
