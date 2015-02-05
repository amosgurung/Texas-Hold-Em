// Author: Amos Gurung
// File: card.cpp
// Implementation of card class

#include "card.h"

std::ostream& operator << (std::ostream& out, const card& d)
{
    if(d.number>=0 && d.number<=8)
    {
        if(d.suit==0)
            std::cout << "(" <<d.number+2 << " S)";
        else if(d.suit==1)
            std::cout << "(" <<d.number+2 << " C)";
        else if(d.suit==2)
            std::cout << "(" <<d.number+2 << " H)";
        else
            std::cout << "(" <<d.number+2 << " D)";
    }
    else if(d.number==9)
    {
        if(d.suit==0)
            std::cout << "(J S)";
        else if(d.suit==1)
            std::cout << "(J C)";
        else if(d.suit==2)
            std::cout << "(J H)";
        else
            std::cout << "(J D)";
    }
    else if(d.number==10)
    {
        if(d.suit==0)
            std::cout << "(Q S)";
        else if(d.suit==1)
            std::cout << "(Q C)";
        else if(d.suit==2)
            std::cout << "(Q H)";
        else
            std::cout << "(Q D)";
    }
    else if(d.number==11)
    {
        if(d.suit==0)
            std::cout << "(J S)";
        else if(d.suit==1)
            std::cout << "(J C)";
        else if(d.suit==2)
            std::cout << "(J H)";
        else
            std::cout << "(J D)";
    }
    else
    {
        if(d.suit==0)
            std::cout << "(J S)";
        else if(d.suit==1)
            std::cout << "(J C)";
        else if(d.suit==2)
            std::cout << "(J H)";
        else
            std::cout << "(J D)";
    }
}
