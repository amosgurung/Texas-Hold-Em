// Author: Amos Gurung
// File: deck.h
// Deck class used for the texas hold em game

#include <vector>
#include <string>
#include "card.h"
#ifndef __DECK
#define __DECK
class deck
{
    public:
    //constructor
    deck():mydeck(){ };

    //pre: a deck has been construced
    //post: the deck is filled with cards
    void filldeck();

    //pre:a deck with cards exists
    //post: displays the deck
    void displaydeck();

    //pre: a deck with cards exists
    //post: shuffles the deck
    void shuffle();

    //pre: a deck with cards exists
    //post: a card is returned and removed from the deck
    card getcard();

    //pre: a deck with cards exists and a valid location of a card is sent
    //post: a specific card is returned and removed from the deck
    card getscard(int);

    //pre: a deck exists
    //post: the size of the deck is returned
    int size(){return mydeck.size();};

    private:
    // a deck used to hold cards
    std::vector<card> mydeck;
};
#endif
