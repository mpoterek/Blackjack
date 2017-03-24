//Marya Poterek
//CardDeck.h
//Interface for CardDeck class
//CSE 20312

/* Interface for functions that are implemented in blackjack play. Dynamic memory allocation as well as a default value are used to construct an object of class CardDeck
 */


#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include <vector>


class CardDeck {

   public:
     
     CardDeck(int = 52); //Non-default constructor, assigned to n in .cpp unless other value passed
     ~CardDeck(); //Destructor
     int getSize(); //Returns size of deck
     void shuffle(); //Shuffles deck
     bool play(); //Returns win//loss to main, calls functions that facilitate gameplay
     int getCard(int); //Returns card at given index
     void showHand(std::vector<int>); //Displays dealer/player's vector
     void drawCard(std::vector<int>&, int&); //Adds another card value to given array
     int checkWin(std::vector<int>&, std::vector<int>&, int&); //Takes both vectors to finish game/check win
     int cardSum(std::vector<int>) ; //Returns sum of given hand of cards
   private:
     int * deck; //Point at elements of array, dynamic memory for deck
     int deckSize; //Number of cards in given deck

};

#endif
