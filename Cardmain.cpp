//Marya Poterek
//Cardmain.cpp
//Main driver for CardDeck class
//CSE 20312


/*Main driver file for blackjack game, which declares an object of class CardDeck, initates (and continues) game play by calling the play utility function, keeps track of the player's and the dealer's scores, and prompts the user to continue playing or end the game.
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "CardDeck.h"

using namespace std;

int main() {
   int pwincount = 0; //Increments number of player wins
   int dwincount = 0; //Increments number of dealer wins
   int choice; //Player's choice to continue game or not
   bool pwin; //Result of call to play function
   bool cont_play = true; //Continues to play game until user asks to quit
   srand(time(NULL)); //Seed rand randomly 
   CardDeck myDeck(52); //Creates deck object of size 10, which overrides default value of 52
   
   
   while (cont_play) {
     pwin = myDeck.play();
     if (pwin == true) {
       pwincount++;
     }
     else {
       dwincount++;
     }
    
     cout << "The player's score is " << pwincount << " and the dealer's score is " << dwincount << endl;
     cout << "Play again? Press 1 for yes and 2 for no." << endl;
   
     cin >> choice;

     if (choice == 1) {  
       cont_play = true;
     }

     else if (choice == 2) { //End game
       cont_play = false;
       cout << "Thanks for playing!" << endl;
     }

     else { //Invalid input error check
       cout << "Invalid input. Thanks for playing!  " << endl;
       break;
     }
   }
   return 0;
}
