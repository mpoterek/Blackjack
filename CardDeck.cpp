//Marya Poterek
//CardDeck.cpp
//Implementation for CardDeck class
//CSE 20312

/* Holds the implementations for the member functions that facilitate blackjack. The play() function is central to game play, and establishes vectors for each hand of cards as well as links to other functions necessary to fulfilling game rules and carrying out its processes
 */

#include <typeinfo>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <numeric> //Facilitates the accumulate function
#include "CardDeck.h"

using namespace std;


CardDeck::CardDeck(int n) { //Non default constructor (has a parameter)//should be int = n?
   deckSize = n; //52 unless another value passed
   deck = new int [deckSize]; //uses dynamic memory allocation
   for (int i = 0; i < deckSize; i++) { //Assigns array values
     deck[i] = (i%13) + 2; //Changes values to 2-11
     if (deck[i] > 11) 
       deck[i] = 10;
   }
}

CardDeck::~CardDeck () { //Deconstructor
   delete []deck; //Deletes whole array, not just first element
}


int CardDeck::getSize() { //Returns size of deck
   return deckSize;
}
 
int CardDeck::getCard(int index) { //Returns card (numeric value) at given place in deck array
   return deck[index];
}

void CardDeck::shuffle() { //"Shuffles" deck by reassigning indices with Knuth's algorithm
   for (int j = deckSize-1; j>0; j--) {
     int k = rand() % deckSize;
     
     int temp = deck[j]; //Set of equivalence statements to avoid repeats
     deck[j]=deck[k]; 
     deck[k] = temp;
   }
}

bool CardDeck::play() {
   int input; //User choice to hit or stand
   bool win; //Returns win as true for player or false for dealer
   bool continueplay = true;
   int w; //Returns value from checkWin function
   int cardnum = 5; //Pass address of this to drawCard
   int sum; //Total of given hand of cards
   shuffle(); //Deck size set to 52, array initialized and re-indexed

   vector<int>playervector {getCard(0), getCard(2) }; //Stores player's cards, first cards dealt
   cout << "Your hand: " << endl;
   showHand(playervector);
   sum = cardSum(playervector);
   if (sum > 21) {
     w = 0;
     continueplay = false;
     cout << "Bust! The dealer wins!" << endl;
   }
   if (sum == 21) {
     w = 1;
     continueplay = false;
     cout << "Blackjack! You win! " << endl;
   }

   vector<int>dealervector {getCard(1), getCard(3) }; //Stores dealer's card
   cout << "The dealer's hand: " << endl;
   showHand(dealervector);
   sum = cardSum(dealervector);
   if (sum > 21) {
     w = 1 ;
     continueplay = false;
     cout << "The dealer busts! The player wins!" << endl;
   }
   
   while (continueplay) {
     cout << "Enter 1 to hit or 2 to stand: ";
     cin >> input;
     if (input ==1) {  //Chooses to hit
       drawCard(playervector, cardnum);
       cout << "Your hand: " << endl;
       showHand(playervector);
       sum = cardSum(playervector);
       if (sum > 21) {
         w = 0;
         continueplay = false;
         cout << "Bust! The dealer wins!" << endl;
       }
       if (sum == 21) {
         w = 1;
         continueplay = false;
         cout << "You hit 21! You win! " << endl;
       }    
     }
     else if (input == 2) { //Chooses to stand
       w = checkWin(playervector, dealervector, cardnum); 
       continueplay = false;
     }

     else { //Invalid input error check
       cout << "Incorrect input. Please try again:  " << endl;
       cin >> input;
     }
   }

   if (w == 1) {
     win = true;
   }
   else {
     win = false;
   }
   return win; //True if player wins, false if dealer does
}

int CardDeck::cardSum (vector<int>hand) { //Returns total sum of given player's cards
   int sum = accumulate(hand.begin(), hand.end(), 0);
   return sum;
}

int CardDeck::checkWin(vector<int>&playervec, vector<int>&dealervec, int& cardnum) {
   
   //Check the player's total
   int playersum = accumulate(playervec.begin(), playervec.end(), 0); //sum of player's cards
   
   //Check the dealer's total and add additional cards if < 17
   int dealsum = accumulate(dealervec.begin(), dealervec.end(), 0); //Sum of dealer's cards

   while (dealsum < 17) {
     drawCard(dealervec, cardnum);
     cout << "Dealer has drawn again." << endl;
     dealsum = accumulate(dealervec.begin(), dealervec.end(), 0);
     cout << "Dealer's new total is: " << dealsum << endl;
   }
   
   if (dealsum > playersum && dealsum <= 21 ) { //If the dealer is closer to 21 and the player 
     cout << "The dealer wins!" << endl;        //does not have blackjack, dealer wins
     return 2;
   } 

   else {
     cout << " The player wins!" << endl;
     return 1;
   }   
}

void CardDeck::drawCard(vector<int>&hand, int& cardnum) { //Adds card to vector by reference, tracks where in deck the card is drawn from
   
   if(cardnum < 36) { //If more than 15 cards remain in deck, add card from current deck
     hand.push_back(getCard(cardnum));
     cardnum++;
   }

   else { //If less than 15 cards, new deck, shuffled, place in deck reset to 0
     shuffle();
     cardnum = 0;
     hand.push_back(getCard(cardnum));
     cardnum++;
   }
}

void CardDeck::showHand(vector<int>hand) { //Prints a given hand
    for (auto it = hand.begin(); it != hand.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
}

