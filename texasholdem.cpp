// Author: Amos Gurung
// File: texasholdem.cpp
// This program mimcs a texas hold em game with probability

#include "texasholdem.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
namespace texasholdem
{
    void GurungStartGame()
    {
        //seed the rand() function which is used by random shuffle
        srand(time(NULL));
        bool done = false;
        bool preflop = false;
        greeting();
        preflop = preflopoption();
        bool fold=false;
        while(done==false)
        {
            int turn =0;
            //creates fills and shuffles the deck
            deck ourdeck;
            ourdeck.filldeck();
            ourdeck.shuffle();
            //creates both hands and the table
            hand playerhand;
            hand opphand;
            table mytable;
            if(turn==0)
            {
                playerhand.c1 = ourdeck.getcard();
                playerhand.c2 = ourdeck.getcard();
                opphand.c1 = ourdeck.getcard();
                opphand.c2 = ourdeck.getcard();

                if(preflop==true)
                    calcprob(playerhand,opphand,mytable, ourdeck,0);


                std::cout <<std::endl<<  "Opponent Hand -> " <<opphand.c1<<opphand.c2<<std::endl;
                std::cout << "Table ->         " <<std::endl;
                std::cout << "Your Hand ->     " <<playerhand.c1<<playerhand.c2<<std::endl;

                fold=foldoption();
                if(fold==true)
                    turn=0;
                else
                    turn++;
            }
            if(turn==1)
            {
                mytable.t1 = ourdeck.getcard();
                mytable.t2 = ourdeck.getcard();
                mytable.t3 = ourdeck.getcard();
                calcprob(playerhand,opphand,mytable, ourdeck,1);

                std::cout << "Opponent Hand -> " <<opphand.c1<<opphand.c2<<std::endl;
                std::cout << "Table ->         " << mytable.t1 << mytable.t2 << mytable.t3 <<std::endl;
                std::cout << "Your Hand ->     "<<playerhand.c1<<playerhand.c2<<std::endl;

                fold=foldoption();
                if(fold==true)
                    turn=0;
                else
                    turn++;
            }
            if(turn==2)
            {
                mytable.t4 = ourdeck.getcard();
                calcprob(playerhand,opphand,mytable, ourdeck,2);

                std::cout << "Opponent Hand -> " <<opphand.c1<<opphand.c2<<std::endl;
                std::cout << "Table ->         " << mytable.t1 << mytable.t2 << mytable.t3 <<mytable.t4<<std::endl;
                std::cout << "Your Hand ->     "<<playerhand.c1<<playerhand.c2<<std::endl;

                fold=foldoption();
                if(fold==true)
                    turn=0;
                else
                    ++turn;
            }
            if(turn==3)
            {
                mytable.t5= ourdeck.getcard();
                calcprob(playerhand,opphand,mytable, ourdeck,3);

                std::cout << "Opponent Hand -> " <<opphand.c1<<opphand.c2<<std::endl;
                std::cout << "Table ->         " << mytable.t1 << mytable.t2 << mytable.t3<< mytable.t4 << mytable.t5 <<std::endl;
                std::cout << "Your Hand ->     "<<playerhand.c1<<playerhand.c2<<std::endl;
                fold=foldoption();
                if(fold==true)
                    turn=0;
                else
                    ++turn;
            }
            if(turn==4)
            {
                std::cout <<std::endl;
                int winner = whowon(playerhand,opphand,mytable);
                if(winner==0)
                    std::cout << "Draw"<<std::endl;
                else if(winner==1)
                    std::cout << "You won!" << std::endl;
                else
                    std::cout << "You lost better luck next time." <<std::endl;
                std::cout <<std::endl;
            }

            done=continueoption();
            std::cout <<std::endl;
        }
        exitmessage();
    }

    void greeting()
    {
        char c;
        std::cout << "This program simulates a game of texas hold em and shows you the probaiblity" << std::endl;
        std::cout << "of winning after stage of the game. Probability is computed by taking every" << std::endl;
        std::cout << "single possible hand that can be made with the current deck given the cards" << std::endl;
        std::cout << "in each player's hand and the cards on the table. The number of times each" << std::endl;
        std::cout << "player wins is then calcuated and the probability of winning is determined" << std::endl;
        std::cout << "by diving by the total number of possible hands." <<std::endl<<std::endl;
        std::cout << "Press any key followed by enter to continue -> ";
        std::cin >> c;
        std::cout<<std::endl;
    }

    void exitmessage()
    {
        std::cout << "Thank you for playing." << std::endl;
    }

    bool continueoption()
    {
        char option = NULL;
        while((option!='Y')&&(option!='y')&&(option!='N')&&(option!='n'))
        {
            std::cout << "Would you like to keep playing? (Y/N)" << std::endl;
            std::cin >> option;
            std::cout << "Option was " <<option<< std::endl;
        }
        if(option=='Y'||option=='y')
        {
            //not done
            return false;
        }
        else
        {
            //done
            return true;
        }
    }

    bool preflopoption()
    {
        char option = NULL;
        while((option!='Y')&&(option!='y')&&(option!='N')&&(option!='n'))
        {
            std::cout << "Would you like preflop probability?" << std::endl;
            std::cout << "*This will take around 20 seconds to compute (Y/N)" << std::endl;
            std::cin >> option;
            std::cout << "Option was " <<option<< std::endl;
        }
        if(option=='Y'||option=='y')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool foldoption()
    {
        char option= NULL;
        while((option!='F')&&(option!='f')&&(option!='C')&&(option!='c'))
        {
            std::cout << "Fold(F) or Check(C)?";
            std::cin>>option;
        }
        if(option=='F'||option=='f')
        {
            //fold
            return true;
        }
        else
        {
            //check
            return false;
        }
    }

    fivecard besthand(hand h1,table mytable)
    {
        int bucket[13] = {0};
        int suit[4] = {0};
        int strength=10;
        fivecard myfivecard;
        std::list<card> poskickers;

        suit[h1.c1.suit]++;
        suit[h1.c2.suit]++;
        suit[mytable.t1.suit]++;
        suit[mytable.t2.suit]++;
        suit[mytable.t3.suit]++;
        suit[mytable.t4.suit]++;
        suit[mytable.t5.suit]++;

        bucket[h1.c1.number]++;
        bucket[h1.c2.number]++;
        bucket[mytable.t1.number]++;
        bucket[mytable.t2.number]++;
        bucket[mytable.t3.number]++;
        bucket[mytable.t4.number]++;
        bucket[mytable.t5.number]++;

        int counter = 0;
        int fullhousetemp=0;
        int fullhousetempcount=0;
        int numpairs=0;
        int temppairval=0;
        for(int i=0;i<13;i++)
        {
            if(bucket[i] >= 1)
                counter++;
            else
                counter = 0;
            //A can be either the lowest or highest cards
            if((counter >= 5)||(i==3&&counter==4&&bucket[12]>=1))
            {
                //straight
                if(strength>=6)
                {
                    strength=6;
                    myfivecard.str=6;
                    myfivecard.fc1.number=i;
                    myfivecard.fc2.number=i-1;
                    myfivecard.fc3.number=i-2;
                    myfivecard.fc4.number=i-3;
                    myfivecard.fc5.number=i-4;
                }

                 //check for royal flush and straight flush
                if(suit[0]>=5||suit[1]>=5||suit[2]>=5||suit[3]>=5)
                {
                    poskickers.clear();
                    //counter for each of the suits of the cards that make up the straight
                    int tempsuits[4]={0};
                    //A-5 straight
                    if(i==3&&counter==4&&bucket[12]>=1)
                    {
                        //check the suits of each of the cards in the straight
                        if((h1.c1.number==12)||((h1.c1.number<=i)&&(h1.c1.number>=i-3)))
                        {
                            tempsuits[h1.c1.suit]++;
                        }
                        if((h1.c2.number==12)||((h1.c2.number<=i)&&(h1.c2.number>=i-3)))
                        {
                            tempsuits[h1.c2.suit]++;
                        }
                        if((mytable.t1.number==12)||((mytable.t1.number<=i)&&(mytable.t1.number>=i-3)))
                        {
                            tempsuits[mytable.t1.suit]++;
                        }
                        if((mytable.t2.number==12)||((mytable.t2.number<=i)&&(mytable.t2.number>=i-3)))
                        {
                            tempsuits[mytable.t2.suit]++;
                        }
                        if((mytable.t3.number==12)||((mytable.t3.number<=i)&&(mytable.t3.number>=i-3)))
                        {
                            tempsuits[mytable.t3.suit]++;
                        }
                        if((mytable.t4.number==12)||((mytable.t4.number<=i)&&(mytable.t4.number>=i-3)))
                        {
                            tempsuits[mytable.t4.suit]++;
                        }
                        if((mytable.t5.number==12)||((mytable.t5.number<=i)&&(mytable.t5.number>=i-3)))
                        {
                            tempsuits[mytable.t5.suit]++;
                        }
                    }
                    else
                    {
                        //check the suits of each of the cards in the straight
                        if((h1.c1.number<=i)&&(h1.c1.number>=i-4))
                        {
                            tempsuits[h1.c1.suit]++;
                        }
                        if((h1.c2.number<=i)&&(h1.c2.number>=i-4))
                        {
                            tempsuits[h1.c2.suit]++;
                        }
                        if((mytable.t1.number<=i)&&(mytable.t1.number>=i-4))
                        {
                            tempsuits[mytable.t1.suit]++;
                        }
                        if((mytable.t2.number<=i)&&(mytable.t2.number>=i-4))
                        {
                            tempsuits[mytable.t2.suit]++;
                        }
                        if((mytable.t3.number<=i)&&(mytable.t3.number>=i-4))
                        {
                            tempsuits[mytable.t3.suit]++;
                        }
                        if((mytable.t4.number<=i)&&(mytable.t4.number>=i-4))
                        {
                            tempsuits[mytable.t4.suit]++;
                        }
                        if((mytable.t5.number<=i)&&(mytable.t5.number>=i-4))
                        {
                            tempsuits[mytable.t5.suit]++;
                        }
                    }

                    if (tempsuits[0]>=5||tempsuits[1]>=5||tempsuits[2]>=5||tempsuits[3]>=5)
                    {
                        //std::cout <<"bucket i is" <<bucket[i];
                        if(i==12)
                        {
                            //royal flush
                            strength = 1;
                            myfivecard.str=1;
                            //nothing beats royal flush
                            return myfivecard;
                        }
                        else
                        {
                            //straight flush
                            if(strength>=2)
                            {
                                strength=2;
                                myfivecard.str=2;
                                myfivecard.fc1.number=i;
                            }
                        }
                    }
                }
            }
            //check for 4 of a kind
            if(bucket[i]==4)
            {
                //four of a kind
                if(strength>=3)
                {
                    poskickers.clear();
                    strength =3;
                    myfivecard.str=3;
                    myfivecard.fc1.number=i;
                    myfivecard.fc2.number=i;
                    myfivecard.fc3.number=i;
                    myfivecard.fc4.number=i;
                    if(h1.c1.number!=i)
                    {
                        poskickers.push_back(h1.c1);
                    }
                    if(h1.c2.number!=i)
                    {
                        poskickers.push_back(h1.c2);
                    }
                    if(mytable.t1.number!=i)
                    {
                        poskickers.push_back(mytable.t1);
                    }
                    if(mytable.t2.number!=i)
                    {
                        poskickers.push_back(mytable.t2);
                    }
                    if(mytable.t3.number!=i)
                    {
                        poskickers.push_back(mytable.t3);
                    }
                    if(mytable.t4.number!=i)
                    {
                        poskickers.push_back(mytable.t4);
                    }
                    if(mytable.t5.number!=i)
                    {
                        poskickers.push_back(mytable.t5);
                    }
                    myfivecard.fc5=highcard(poskickers);
                    //if 4 of a kind exists then it is the strongest hand because you cannot have any kind of straight with a
                    //4 of a kind so neither royal flusehs nor straight flushes exist making 4 of a kind the stronget hand
                    return myfivecard;
                }
            }

            //check for full house
            if(bucket[i]>=2)
            {
                if(fullhousetempcount!=0)
                {
                    if(bucket[i]>=3)
                    {
                        //full house
                        if(strength>=4)
                        {
                            strength =4;
                            myfivecard.str=4;
                            myfivecard.fc1.number=i;
                            myfivecard.fc2.number=i;
                            myfivecard.fc3.number=i;
                            myfivecard.fc4.number=fullhousetemp;
                            myfivecard.fc5.number=fullhousetemp;
                        }
                    }
                    else if(fullhousetempcount>=3)
                    {
                        if(strength>=4)
                        {
                            strength =4;
                            myfivecard.str=4;
                            myfivecard.fc1.number=fullhousetemp;
                            myfivecard.fc2.number=fullhousetemp;
                            myfivecard.fc3.number=fullhousetemp;
                            myfivecard.fc4.number=i;
                            myfivecard.fc5.number=i;
                        }
                    }
                }
                else
                {
                    fullhousetempcount=bucket[i];
                    fullhousetemp=i;
                }
            }

            //check for 3 of a kind
            if(bucket[i]==3)
            {
                //three of a kind
                if(strength>=7)
                {
                    poskickers.clear();
                    strength=7;
                    myfivecard.str=7;
                    myfivecard.fc1.number=i;
                    myfivecard.fc2.number=i;
                    myfivecard.fc3.number=i;
                    if(h1.c1.number!=i)
                    {
                        poskickers.push_back(h1.c1);
                    }
                    if(h1.c2.number!=i)
                    {
                        poskickers.push_back(h1.c2);
                    }
                    if(mytable.t1.number!=i)
                    {
                        poskickers.push_back(mytable.t1);
                    }
                    if(mytable.t2.number!=i)
                    {
                        poskickers.push_back(mytable.t2);
                    }
                    if(mytable.t3.number!=i)
                    {
                        poskickers.push_back(mytable.t3);
                    }
                    if(mytable.t4.number!=i)
                    {
                        poskickers.push_back(mytable.t4);
                    }
                    if(mytable.t5.number!=i)
                    {
                        poskickers.push_back(mytable.t5);
                    }
                    myfivecard.fc4=highcard(poskickers);
                    poskickers.remove(myfivecard.fc4);
                    myfivecard.fc5=highcard(poskickers);
                }
            }

            //check for two pairs and pair
            if(bucket[i]>=2)
            {
                ++numpairs;
                //two pairs
                if(numpairs>=2)
                {
                    if(strength>=8)
                    {
                        poskickers.clear();
                        strength=8;
                        myfivecard.str=8;
                        myfivecard.fc1.number=i;
                        myfivecard.fc2.number=i;
                        myfivecard.fc3.number=temppairval;
                        myfivecard.fc4.number=temppairval;
                        if((h1.c1.number!=i)&&(h1.c1.number!=temppairval))
                        {
                            poskickers.push_back(h1.c1);
                        }
                        if((h1.c2.number!=i)&&(h1.c2.number!=temppairval))
                        {
                            poskickers.push_back(h1.c2);
                        }
                        if((mytable.t1.number!=i)&&(mytable.t1.number!=temppairval))
                        {
                            poskickers.push_back(mytable.t1);
                        }
                        if((mytable.t2.number!=i)&&(mytable.t2.number!=temppairval))
                        {
                            poskickers.push_back(mytable.t2);
                        }
                        if((mytable.t3.number!=i)&&(mytable.t3.number!=temppairval))
                        {
                            poskickers.push_back(mytable.t3);
                        }
                        if((mytable.t4.number!=i)&&(mytable.t4.number!=temppairval))
                        {
                            poskickers.push_back(mytable.t4);
                        }
                        if((mytable.t5.number!=i)&&(mytable.t5.number!=temppairval))
                        {
                            poskickers.push_back(mytable.t5);
                        }
                        myfivecard.fc5=highcard(poskickers);
                    }
                }
                else
                {
                    //pair
                    if(strength>=9)
                    {
                        poskickers.clear();
                        strength=9;
                        myfivecard.str=9;
                        myfivecard.fc1.number=i;
                        myfivecard.fc2.number=i;
                        if(h1.c1.number!=i)
                        {
                            poskickers.push_back(h1.c1);
                        }
                        if(h1.c2.number!=i)
                        {
                            poskickers.push_back(h1.c2);
                        }
                        if(mytable.t1.number!=i)
                        {
                            poskickers.push_back(mytable.t1);
                        }
                        if(mytable.t2.number!=i)
                        {
                            poskickers.push_back(mytable.t2);
                        }
                        if(mytable.t3.number!=i)
                        {
                            poskickers.push_back(mytable.t3);
                        }
                        if(mytable.t4.number!=i)
                        {
                            poskickers.push_back(mytable.t4);
                        }
                        if(mytable.t5.number!=i)
                        {
                            poskickers.push_back(mytable.t5);
                        }
                        myfivecard.fc3=highcard(poskickers);
                        poskickers.remove(myfivecard.fc3);
                        myfivecard.fc4=highcard(poskickers);
                        poskickers.remove(myfivecard.fc4);
                        myfivecard.fc5=highcard(poskickers);
                    }
                }
                temppairval=i;
            }
        }
        //check for flush
        if(suit[0]>=5||suit[1]>=5||suit[2]>=5||suit[3]>=5)
        {
            int flushsuit=0;
            if(suit[0]>=5)
                flushsuit=0;
            else if(suit[1]>=5)
                flushsuit=1;
            else if(suit[2]>=5)
                flushsuit=2;
            else
                flushsuit=3;

            //flush
            if(strength>=5)
            {
                poskickers.clear();
                strength=5;
                myfivecard.str=5;
                if(h1.c1.suit==flushsuit)
                {
                    poskickers.push_back(h1.c1);
                }
                if(h1.c2.suit==flushsuit)
                {
                    poskickers.push_back(h1.c2);
                }
                if(mytable.t1.suit==flushsuit)
                {
                    poskickers.push_back(mytable.t1);
                }
                if(mytable.t2.suit==flushsuit)
                {
                    poskickers.push_back(mytable.t2);
                }
                if(mytable.t3.suit==flushsuit)
                {
                    poskickers.push_back(mytable.t3);
                }
                if(mytable.t4.suit==flushsuit)
                {
                    poskickers.push_back(mytable.t4);
                }
                if(mytable.t5.suit==flushsuit)
                {
                    poskickers.push_back(mytable.t5);
                }
                myfivecard.fc1=highcard(poskickers);
                poskickers.remove(myfivecard.fc1);
                myfivecard.fc2=highcard(poskickers);
                poskickers.remove(myfivecard.fc2);
                myfivecard.fc3=highcard(poskickers);
                poskickers.remove(myfivecard.fc3);
                myfivecard.fc4=highcard(poskickers);
                poskickers.remove(myfivecard.fc4);
                myfivecard.fc5=highcard(poskickers);
            }
        }
        //if strength has not changed at this point no stronger hand exists so its a high card
        if(strength==10)
        {
            strength=10;
            myfivecard.str=10;
            poskickers.clear();
            poskickers.push_back(h1.c1);
            poskickers.push_back(h1.c2);
            poskickers.push_back(mytable.t1);
            poskickers.push_back(mytable.t2);
            poskickers.push_back(mytable.t3);
            poskickers.push_back(mytable.t4);
            poskickers.push_back(mytable.t5);
            myfivecard.fc1=highcard(poskickers);
            poskickers.remove(myfivecard.fc1);
            myfivecard.fc2=highcard(poskickers);
            poskickers.remove(myfivecard.fc2);
            myfivecard.fc3=highcard(poskickers);
            poskickers.remove(myfivecard.fc3);
            myfivecard.fc4=highcard(poskickers);
            poskickers.remove(myfivecard.fc4);
            myfivecard.fc5=highcard(poskickers);
        }
        return myfivecard;
    }

    std::string convertstr(int strength)
    {
        std::string str;
        if(strength==1)
            str="Royal flush";
        else if(strength==2)
            str="Straight flush";
        else if(strength==3)
            str="Four of a kind";
        else if(strength==4)
            str="Full house";
        else if(strength==5)
            str="Flush";
        else if(strength==6)
            str="Straight";
        else if(strength==7)
            str="Three of a kind";
        else if(strength==8)
            str="Two Pair";
        else if(strength==9)
            str="Pair";
        else
            str="High card";
        return str;
    }

    int whowon(hand h1,hand h2,table mytable)
    {
        //the lower the hand the stronger it is
        fivecard fcp1 =besthand(h1,mytable);
        fivecard fcp2 =besthand(h2,mytable);
        int p1=fcp1.str;
        int p2=fcp2.str;

        if(p1<p2)
        {
            return 1;
        }

        else if(p1>p2)
        {
            return 2;
        }
        //tie
        else
        {
            return tiebreaker(fcp1,fcp2);
        }

    }

    float calcprob(hand h1,hand h2,table mytable,deck mydeck,int turn)
    {
        float numwins=0;
        float total=0;
        float probability=0;
        float tie=0;
        float player2wins=0;

        if(turn==0)
        {
            deck deck1=mydeck;
            for(int i=0;i<mydeck.size();i++)
            {
                mytable.t1=deck1.getcard();
                deck deck2=deck1;
                for(int j=0;j<deck1.size();j++)
                {
                    mytable.t2=deck2.getcard();
                    deck deck3=deck2;
                    for(int k=0;k<deck2.size();k++)
                    {
                        mytable.t3=deck3.getcard();
                        deck deck4=deck3;
                        for(int l=0;l<deck3.size();l++)
                        {
                            mytable.t4=deck4.getcard();
                            deck deck5=deck4;
                            for(int m=0;m<deck4.size();m++)
                            {
                                mytable.t5=deck5.getcard();
                                int winner =whowon(h1,h2,mytable);
                                if(winner==1)
                                {
                                    ++numwins;
                                }
                                else if(winner==2)
                                {
                                    ++player2wins;
                                }
                                else if(winner ==0)
                                {
                                    ++tie;
                                }
                                ++total;
                            }
                        }
                    }
                }
            }
        }
        else if(turn==1)
        {
            deck tempdeck=mydeck;
            for(int i=0;i<mydeck.size();i++)
            {
                mytable.t4=tempdeck.getcard();
                deck tempdeck2=tempdeck;
                for(int j=0;j<tempdeck.size();j++)
                {
                    mytable.t5=tempdeck2.getcard();
                    int winner =whowon(h1,h2,mytable);
                    if(winner==1)
                        ++numwins;
                    else if(winner==2)
                        ++player2wins;
                    else if(winner==0)
                        ++tie;
                    ++total;
                }
            }
        }
        else if(turn==2)
        {
            deck tempdeck=mydeck;
            for(int i=0;i < mydeck.size(); i++)
            {
                mytable.t5=tempdeck.getcard();
                int winner =whowon(h1,h2,mytable);
                if(winner==1)
                    ++numwins;
                else if(winner==2)
                    ++player2wins;
                else if(winner==0)
                    ++tie;
                ++total;
            }
        }
        else if(turn==3)
        {
            int winner =whowon(h1,h2,mytable);
            if(winner==1)
                ++numwins;
            else if(winner==2)
                ++player2wins;
            else if(winner ==0)
                ++tie;
            ++total;
        }

        probability=(numwins/total)*100;
        float tieprob=(tie/total)*100;
        float player2prob=(player2wins/total)*100;

        std::cout <<std::endl;
        //std::cout << "Number of Player wins is: " <<std::fixed <<std::setprecision(0) <<numwins<<std::endl;
        //std::cout << "Total number of hands is: " <<std::fixed<<std::setprecision(0)<<total<<std::endl;
        std::cout << "Probability of Player winning is: " << std::fixed <<std::setprecision(2) <<probability<<'%'<<std::endl;
        //std::cout << "Number of ties is: " <<std::fixed << std::setprecision(0) <<tie<<std::endl;
        std::cout << "Probability of tie is: " << std::fixed<< std::setprecision(2) << tieprob<<'%'<<std::endl;
        //std::cout << "Number of Opponent wins is: " <<std::fixed<<std::setprecision(0)<< player2wins<<std::endl;
        std::cout << "Probability of Opponent winning is: " << std::fixed <<std::setprecision(2) << player2prob<<'%'<<std::endl;
        std::cout << std::endl;
        return probability;
    }

    int tiebreaker(fivecard f1, fivecard f2)
    {
        int mystr = f1.str;

        //royal flush
        if(mystr==1)
        {
            return 0;
        }
        //straight flush
        else if(mystr==2)
        {
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            else
                return 0;
        }
        //4 of a kind
        else if(mystr==3)
        {
            //compare the 4 of akind
            if (f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            //compare kicker
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
        //full house
        else if(mystr==4)
        {
            //compare the 3 cards
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            //compare the two cards
            else if(f1.fc4.number>f2.fc4.number)
                return 1;
            else if(f1.fc4.number<f2.fc4.number)
                return 2;
            else
                return 0;
        }
        //flush
        else if(mystr==5)
        {
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            else if(f1.fc2.number>f2.fc2.number)
                return 1;
            else if(f1.fc2.number<f2.fc2.number)
                return 2;
            else if(f1.fc3.number>f2.fc3.number)
                return 1;
            else if(f1.fc3.number<f2.fc3.number)
                return 2;
            else if(f1.fc4.number>f2.fc4.number)
                return 1;
            else if(f1.fc4.number<f2.fc4.number)
                return 2;
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
        //straight
        else if(mystr==6)
        {
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            else
                return 0;
        }
        //three of a kind
        else if(mystr==7)
        {
            //3 val the 3 of a kind
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            //kicker
            else if(f1.fc4.number > f2.fc4.number)
                return 1;
            else if(f1.fc4.number < f2.fc4.number)
                return 2;
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
        //two pair
        else if(mystr==8)
        {
            //compare higher pair
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            //lower pair
            else if(f1.fc3.number>f2.fc3.number)
                return 1;
            else if(f1.fc3.number<f2.fc3.number)
                return 2;
            //kicker
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
        //pair
        else if(mystr==9)
        {
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            else if(f1.fc3.number>f2.fc3.number)
                return 1;
            else if(f1.fc3.number<f2.fc3.number)
                return 2;
            else if(f1.fc4.number>f2.fc4.number)
                return 1;
            else if(f1.fc4.number<f2.fc4.number)
                return 2;
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
        //high card
        else
        {
            if(f1.fc1.number>f2.fc1.number)
                return 1;
            else if(f1.fc1.number<f2.fc1.number)
                return 2;
            else if(f1.fc2.number>f2.fc2.number)
                return 1;
            else if(f1.fc2.number<f2.fc2.number)
                return 2;
            else if(f1.fc3.number>f2.fc3.number)
                return 1;
            else if(f1.fc3.number<f2.fc3.number)
                return 2;
            else if(f1.fc4.number>f2.fc4.number)
                return 1;
            else if(f1.fc4.number<f2.fc4.number)
                return 2;
            else if(f1.fc5.number>f2.fc5.number)
                return 1;
            else if(f1.fc5.number<f2.fc5.number)
                return 2;
            else
                return 0;
        }
    }

    card highcard(std::list<card> mycards)
    {
        card high =mycards.front();

        std::list<card>::iterator it=mycards.begin();
        while(it!=mycards.end())
        {
            if( *it>high)
                high = *it;
            ++it;
        }
        return high;
    }
}

