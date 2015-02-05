// Author: Amos Gurung
// File: texasholdem.h
// Functions for the texas holdem game as well as some necessary structs
#include <list>
#include "deck.h"

namespace texasholdem
{
    //some structs to store data
    struct hand
    {
        card c1;
        card c2;
    };

    struct table
    {
        card t1;
        card t2;
        card t3;
        card t4;
        card t5;
    };

    struct fivecard
    {
        int str;
        card fc1;
        card fc2;
        card fc3;
        card fc4;
        card fc5;
    };
    //pre: none
    //post: starts the game of texas hold em
    void GurungStartGame();

    //pre:none
    //post:a greeting is displayed to the user
    void greeting();

    //pre: the user has chosen to quit playing
    //post: an exit message is displayed to the user
    void exitmessage();

    //pre:hand has 2 cards and the table is full with 5 cards
    //post: the best 5 card hand is returned
    fivecard besthand(hand,table);

    //pre: a hand strength represented as an integeret is sent
    //post: a hand strength represented as an actual string is returned
    std::string convertstr(int);

    //pre: two hand with cards and a full table with 5 cards is sent
    //post: the winner is returned as an integer: 0 for a draw 1 for player 1 win and 2 for player 2 win
    int whowon(hand,hand,table);

    //pre: two hands with cards and a table which can have 0 3 4 or 5 cards is sent as well as turn information
    //post: the probability of winning repsented as a float is returned
    float calcprob(hand,hand,table, deck, int);

    //pre: two five card hands with equal strength are sent
    //post: the stronger of the two hands as determiend by the kicker is returned in the same format as whowon
    int tiebreaker(fivecard,fivecard);

    //pre: a list of cards is sent
    //post: the highest card as determined by the number of each card is returned
    card highcard(std::list<card>);

    //pre: it is the users turn
    //post: the option to fold or check is given
    bool foldoption();

    //pre: the game is starting for the first time
    //post: an option to compute preflop probability is given
    bool preflopoption();

    //pre: the game is played once
    //post: an option to continue playing is given
    bool continueoption();
}

