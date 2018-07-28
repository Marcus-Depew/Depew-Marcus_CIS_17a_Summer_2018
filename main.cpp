/* 
 * File:   main.cpp
 * Author: Your Name <Marcus Depew @mdepew1@gmail.com>
 *
 * Created on July 23, 2018, 5:38 PM
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
  using namespace std;

//User Libraries
#include "hotel.h"
#include "human.h" /
#include "npc.h"
#include "game.h"

//Global constants
const int SIZE = 40; //board is 40 spaces

//Function Prototypes
unsigned char diceroll(unsigned char, unsigned char); //roll dice
void display(int[], int[], string[], human & , npc & ); //displays the board
void rules(); //outputs the rules of the game
void gameover(); //outputs game over


int complayermove(npc & , int[]); //computer moves on board
int pay(human & , npc & , game & );
int move(human & , int[]);
int chest(human & , npc & , game & , int[], int[]);
int jail(human & , npc & , game & , int[], int[]);
int chance(human & , npc & , game & , int[], int[]);
int win(human & , npc & , game & );

//Execution Begins here
int main(int argc, char ** argv) {
  //Set the random seed
  srand(static_cast < unsigned int > (time(0)));

  //Declare Variables
  human h;
  npc c;
  game g;
  string sym;
  int choice; //choice of the symbol
  char purchasecheck; //check is purchase
  int purchasedone; //answer to purchasecheck
  int play = 0; //game or see rules

  hotel *board = new hotel[SIZE]; //dynamic array purchase and rent of the property
  string property[SIZE] = {
    "Go",
    "Mediterranean Avenue",
    "Community Chest",
    "Baltic Avenue",
    " Income Tax",
    "Reading Railroad",
    "Oriental Avenue",
    "Chance",
    "Vermont Avenue",
    "Connecticut Avenue",
    "In Jail or Just visiting",
    "St. Charles Place",
    "Electric Company",
    "States Avenue",
    " Virginia Avenue",
    "Pennsylvania RailRoad",
    "St. James Place",
    "Community Chest",
    "Tennessee Avenue",
    " New York Avenue",
    "Free Parking",
    "Kentucky Avenue",
    "Chance",
    "Indiana Avenue",
    "Illinois Avenue",
    " B. & O. Railroad",
    "Atlantic Avenue",
    "Ventnor Avenue",
    "Water Works",
    "Marvin Gardens",
    "Go to Jail",
    "Pacific Avenue",
    "North Carolina Avenue",
    "Community Chest",
    "Pennsylvania Avenue",
    "Short Line",
    "Chance",
    "Park Place",
    "Luxury Tax",
    "BoardWalk"
  };
  int purchase[SIZE] = {
    0,
    60,
    0,
    60,
    0,
    200,
    100,
    0,
    100,
    120,
    0,
    140,
    150,
    140,
    160,
    200,
    180,
    0,
    180,
    200,
    0,
    220,
    0,
    220,
    240,
    200,
    260,
    260,
    150,
    280,
    0,
    300,
    300,
    0,
    320,
    200,
    0,
    350,
    0,
    400
  };
  int rent[SIZE] = {
    0,
    20,
    0,
    40,
    0,
    25,
    60,
    0,
    60,
    80,
    0,
    100,
    75,
    100,
    120,
    250,
    140,
    0,
    140,
    160,
    0,
    180,
    0,
    180,
    200,
    250,
    220,
    220,
    75,
    240,
    0,
    260,
    260,
    0,
    280,
    250,
    0,
    350,
    0,
    500
  };
  for (int i = 0; i < SIZE; i++) {
    board[i].setname(property[i]);
    board[i].setbuy(purchase[i]);
    board[i].setrent(rent[i]);
  }

  bool avail[SIZE]; //house available check
  //sets the whole board to available to purchase

  for (int i = 0; i < SIZE; i++) {
    avail[i] = true;
    //Sets the chance,go,income tax to not purchase
    if (i == 0 || i == 2 || i == 4 || i == 7 || i == 10 || i == 17 || i == 20 || i == 22 || i == 30 || i == 33 || i == 36 || i == 38) {
      avail[i] = false;
    }
  }
  int computermove[SIZE]; //computers board
  int playermove[SIZE]; //player's board

  vector < int > p1prop;
  vector < int > c1prop;
  //array set to 0
  for (int i = 0; i < SIZE; i++) {
    playermove[i] = 0;
    computermove[i] = 0;
  }

  do {
    do {
      cout << "The Monopoly game\n";
      cout << "Each competitor starts off with $$1500\n";
      cout << "1. To play the game\n2. To see the rules\n";
      cin >> play;
      cin.ignore();
      if (play < 1 || play > 2) {
        cout << "Invalid Input. 1 or 2\n";
      }
    } while (play < 1 || play > 2);

    switch (play) {
    case 1:
      {
        while (choice != 3) {
          cout << "Change your piece?\n";
          cout << "1. Change piece\n2. Change the Computer's piece\n3. Play\n";
          cin >> choice;
          cin.ignore();
          if (choice == 1) {
            do {
              cout << "Type your character piece ex.(!,@,#,$)\n";
              cout << "piece: ";
              getline(cin, sym);
              sym.size();
              if (sym.size() > 3) {
                cout << "Error: Input must be one and three characters\n";
              }
            } while (sym.size() > 3);
            h.setsym(sym);
          } else if (choice == 2) {
            do {
              cout << "Input the computer's symbol ex.(!,@,#,$)\n";
              cout << "Symbol: ";
              getline(cin, sym);
              sym.size();
              if (sym.size() > 3) {
                cout << "Error: Input must be one and three characters\n";
              }
            } while (sym.size() > 3);
            c.setsym(sym);
          } else if (choice == 3) {
        
          }
        }

        do {
          win(h, c, g);
          if (g.getgame() == false) {
            break;
          }
          if (g.getgame() != false) {
            if (g.getnpcprison() == false) {
              g.setturn(2);
              g.setnpcprison(true);
            } else {
              g.setturn(1);
            }
            for (int i = 1; i <= g.getturn(); i++) {
              g.setuser(true);
              h.setdiceroll(diceroll(6, 2));
              cout << "Banker says you balance is" << h.getmoney() << "\n";
              cout << "Player 1 you rolled dice and got " << h.getdiceroll() << endl;
              cout << "Move ahead " << h.getdiceroll() << " spaces." << endl;
              playermove[h.getlocation()] = 0;
              h.setlocation(h.getlocation() + h.getdiceroll());

              move(h, playermove);

              cout << "PLayer 1 landed on " << property[h.getlocation()] << endl;
              if (h.getlocation() == 4 || h.getlocation() == 38) {
                pay(h, c, g);
              }
              if (h.getlocation() == 7 || h.getlocation() == 22 || h.getlocation() == 36) {
                chance(h, c, g, playermove, computermove);
              }
              if (h.getlocation() == 2 || h.getlocation() == 17 || h.getlocation() == 33) {
                chest(h, c, g, playermove, computermove);
              }
              if (h.getlocation() == 30) {
                g.setprison(false);
                jail(h, c, g, playermove, computermove);
              }
              cout << "player 1's balance is $" << h.getmoney() << endl;
              //print board
              display(playermove, computermove, property, h, c);
              //check landed space owner
              for (int i = 0; i < c1prop.size(); i++) {
                if (h.getlocation() == c1prop[i]) {
                  h.setmoney(h.getmoney() - rent[h.getlocation()]);

                  c.setmoney(c.getmoney() + rent[h.getlocation()]);
                  cout << "Computer owns " << property[h.getlocation()] << " PLayer 1 owes $" << rent[h.getlocation()] << " for rent\n";
                }
              }
              //To determine the winner
              win(h, c, g);
              if (g.getgame() == false) {
                break;
              }
              do {
                do {
                  cout << "1. Buy Property\n2. See your property\n3. End turn\n";
                  cin >> purchasedone;
                  cin.ignore();
                  if (purchasedone < 1 || purchasedone > 3) {
                    cout << "Invalid Input\n";
                  }
                } while (purchasedone < 1 || purchasedone > 3);
                switch (purchasedone) {
                case 1:
                  {
                    if (avail[h.getlocation()] == false) {
                      cout << "You can not purchase this property\n";
                    } else if (avail[h.getlocation()] == true) {
                      cout << "You may purchase this property\n";
                      board[h.getlocation()].print();
                      do {
                        cout << "Press 'Y' if you want to purchase this property, and 'N' if you don't\n";
                        cin >> purchasecheck;
                        cin.ignore();
                        if (purchasecheck != 'Y' && purchasecheck != 'y' && purchasecheck != 'N' && purchasecheck != 'n') {
                          cout << "Invalid Input\n";
                        }
                      } while (purchasecheck != 'Y' && purchasecheck != 'y' && purchasecheck != 'N' && purchasecheck != 'n');

                      if (purchasecheck == 'Y' || purchasecheck == 'y') {
                        if (h.getmoney() < purchase[h.getlocation()]) {
                          cout << "Sorry You can not afford this property\n";
                        } else if (h.getmoney() >= purchase[h.getlocation()]) {
                          cout << "You purchased " << property[h.getlocation()] << endl;
                          h.setmoney(h.getmoney() - purchase[h.getlocation()]); //Subtracts cost from balance
                          avail[h.getlocation()] = false; //longer available
                          p1prop.push_back(h.getlocation()); //stores location of the player property 
                        }
                      }
                    }
                    break;
                  }
                case 2:
                  {
                    if (p1prop.size() == 0) {
                      cout << "PLayer 1 does not own any property\n";
                    } else {
                      //print property the player 1 owns
                      cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n";
                      for (int i = 0; i < p1prop.size(); i++) {
                        cout << "You own " << property[p1prop[i]] << endl;
                      }
                      cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n";
                    }
                    break;
                  }
                case 3:
                  {
                    cout << "Turn ended!\n\n\n";
                    break;
                  }
                default:
                  cout << "Error in statement\n";
                }
              } while (purchasedone != 3);
            }
          }
          win(h, c, g);
          if (g.getgame() == false) {
            break;
          }
          if (g.getgame() != false) {
            if (g.getprison() == false) {
              g.setturn(2);
              g.setprison(true);
            } else {
              g.setturn(1);
            }
            for (int i = 1; i <= g.getturn(); i++) {
              g.setuser(false);
              c.setdiceroll(diceroll(6, 2));
              cout << "computer's turn, balance $" << c.getmoney() << "\n";
              cout << "The computer moved ahead " << c.getdiceroll() << " spaces." << endl;
              computermove[c.getlocation()] = 0;
              c.setlocation(c.getlocation() + c.getdiceroll());
              complayermove(c, computermove);

              cout << "The computer landed on " << property[c.getlocation()] << endl;
              win(h, c, g); //determines the winner
              if (g.getgame() == false) break; //stop computer if player is winner
              //calls the income tax
              if (c.getlocation() == 4 || c.getlocation() == 38) {
                pay(h, c, g);
              }
              //calls the chance function
              if (c.getlocation() == 7 || c.getlocation() == 22 || c.getlocation() == 36) {
                chance(h, c, g, playermove, computermove);
              }
              //calls the chest function
              if (c.getlocation() == 2 || c.getlocation() == 17 || c.getlocation() == 33) {
                chest(h, c, g, playermove, computermove);
              }
              //Calls the jail function
              if (c.getlocation() == 30) {
                g.setnpcprison(false);
                jail(h, c, g, playermove, computermove);
              }

              //Used to check where player 1 lands on a computer owned location
              for (int i = 0; i < p1prop.size(); i++) {
                if (c.getlocation() == p1prop[i]) {
                  c.setmoney(c.getmoney() - rent[c.getlocation()]);

                  h.setmoney(h.getmoney() + rent[c.getlocation()]);
                  cout << "You own " << property[c.getlocation()] << " the computer owes player $" << rent[c.getlocation()] << " for rent\n";
                }
              }
              int Cpurchase = rand() % 3 + 1;
              if (avail[c.getlocation()] == true) {
                if (c.getmoney() > purchase[c.getlocation()]) {
                  if (Cpurchase == 2) {
                    cout << "The computer purchased " << property[c.getlocation()] << endl;
                    c.setmoney(c.getmoney() - purchase[c.getlocation()]); ////Subtracts cost from balance
                    avail[c.getlocation()] = false; //Is no longer available
                    c1prop.push_back(c.getlocation()); //stores location of the player property 
                  }
                }
              }
              display(playermove, computermove, property, h, c);
              cout << "Computer's turn ended, balance $" << c.getmoney() << "\n";
              cout << "\n\n";
            }

          }
        } while (g.getgame());
        break;
      }
    case 2:
      {
        rules();
        break;
      }
    }
  } while (play != 1);
  gameover();
  //Writes to a file player 1 data
  ofstream fout("scores.txt", ios::binary);
  cout << "Saving player 1 balance to file..\n";
  fout << "Player 1 balance: $" << h.getmoney() << endl;
  //print  property player 1 owns
  int counter = 0;
  for (int i = 0; i < p1prop.size(); i++) {
    fout << "You own " << property[p1prop[i]] << ", ";
    counter++;
    if (counter > 3) {
      fout << endl;
      counter = 0;
    }
  }
  fout.close();
  cout << "Thanks playing!!" << endl;
  return 0;
}
int pay(human & h, npc & c, game & g) {
  if (g.getuser() == true) {
    if (h.getlocation() == 4) {
      cout << "PLayer 1 paid $200 to the bank\n";
      h.setmoney(h.getmoney() - 200);
    } else if (h.getlocation() == 38) {
      cout << "PLayer 1 paid $100 to the bank\n";
      h.setmoney(h.getmoney() - 100);
    }
  } else if (g.getuser() == false) {
    if (c.getlocation() == 4) {
      cout << "The computer paid $200 to the bank\n";
      c.setmoney(c.getmoney() - 200);
    } else if (c.getlocation() == 38) {
      cout << "The computer paid $100 to the bank\n";
      c.setmoney(c.getmoney() - 100);
    }
  }
}
int jail(human & h, npc & c, game & g, int playermove[], int computermove[]) {
  if (g.getuser() == true) {
    playermove[h.getlocation()] = 0;
    h.setlocation(10);
    h.setdiceroll(0);
    playermove[h.getlocation()] = 1;
    cout << "sorry You have been sent to Jail\n";
  } else if (g.getuser() == false) {
    computermove[c.getlocation()] = 0;
    c.setlocation(10);
    c.setdiceroll(0);
    computermove[c.getlocation()] = 1;
    cout << "The computer has been sent to jail Jail\n";
  }
}
//Display function
void display(int playermove[], int computermove[], string property[], human & h, npc & c) {
 
  cout << endl;
  for (int i = 0; i < SIZE; i++) {
    cout << "--";
  }
  cout << endl;
  for (int i = 1; i <= SIZE; i++) {
    cout << "| ";
    if (playermove[i] == 1) {
      cout << h.getsym();
    }
    if (computermove[i] == 1) {
      cout << c.getsym();
    }
  }
  cout << endl;
  for (int i = 0; i < SIZE; i++) {
    cout << "--";
  }
  cout << endl;
}
//function to compaire blances
int win(human & h, npc & c, game & g) {
  //player wins when computer runs out of money
  if (h.getmoney() <= 0) {
    cout << "Player 1 has lost\n";
    g.setgame(false);
  } else if (c.getmoney() <= 0) {
    cout << "You win!!\n";
    g.setgame(false);
  }
}
//computer logic
int complayermove(npc & c, int computermove[]) {
  //set board to zero
  for (int i = 0; i < SIZE; i++) {
    computermove[i] = 0;
  }
  for (int i = 0; i <= c.getdiceroll(); i++) {
    if (c.getlocation() > 39) {
      c.setlocation(c.getlocation() - 39);
      cout << "The computer passed 'Go' and collected $200\n";
      c.setmoney(c.getmoney() + 200);
    } else {
      computermove[c.getlocation()] = 1;
    }
  }
}
//player 1 movement logic
int move(human & h, int playermove[]) {
  //set board to zero
  for (int i = 0; i < SIZE; i++) {
    playermove[i] = 0;
  }
  for (int i = 0; i <= h.getdiceroll(); i++) {
    if (h.getlocation() > 39) {
      h.setlocation(h.getlocation() - 39);
      cout << "Player 1 has passed 'Go' you collect $200\n";
      h.setmoney(h.getmoney() + 200);
    } else {
      playermove[h.getlocation()] = 1;
    }
  }
}

void gameover() {
  ifstream fin;
  string temp;
  //Cout the rules    
  fin.open("gameover.txt");
  if (fin.is_open()) {
    while (getline(fin, temp)) {
      cout << temp;
    }
  }
  cout << endl;
  fin.close();
}
//rules
void rules() {
  ifstream fin;
  string temp;
  cout << endl;
  //Cout the rules    
  fin.open("rulesbook.txt");
  if (fin.is_open()) {
    while (getline(fin, temp)) {
      cout << temp << endl;
    }
  }
  cout << endl;
  fin.close();
}
//dice roll function
unsigned char diceroll(unsigned char sides, unsigned char nDie) {
  //sum the die rolls 
  unsigned char sum = 0;
  //Loop die rolls
  for (int thrw = 1; thrw <= nDie; thrw++) {
    sum += (rand() % sides + 1);
  }
  return sum;
}
int chance(human & h, npc & c, game & g, int playermove[], int computermove[]) {
  int random = rand() % 12 + 1;
  if (g.getuser() == true) {
    switch (random) {
    case 1:
      {
        cout << "Chance: Go to Jail–Go directly to Jail–Do not pass Go, do not collect $200\n";
        g.setprison(false);
        jail(h, c, g, playermove, computermove);
        break;
      }
    case 2:
      {
        cout << "Chance: You have been elected Chairman of the Board–Pay each player $500\n";
        h.setmoney(h.getmoney() - 500);
        c.setmoney(c.getmoney() + 500);
        break;
      }
    case 3:
      {
        cout << "Chance: Advance token to reading railroad. If you pass go collect $200\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(5); 
        h.setlocation(5);
        move(h, playermove);
        break;
      }
    case 4:
      {
        cout << "Chance: Pay poor tax of $150\n";
        h.setmoney(h.getmoney() - 150);
        break;
      }
    case 5:
      {
        cout << "Chance: Your building and loan matures—Collect $50\n";
        h.setmoney(h.getmoney() + 50);
        break;
      }
    case 6:
      {
        cout << "Chance: Advance to go collect $200\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(0);
        h.setlocation(0);
        move(h, playermove);
        cout << "You passed 'Go' collect $200\n";
        h.setmoney(h.getmoney() + 200);
        break;
      }
    case 7:
      {
        cout << "Chance: Go Back 3 Spaces.\n";
        playermove[h.getlocation()] = 0;
        h.setlocation(h.getlocation() - 3);
        playermove[h.getlocation()] = 1;
        break;
      }
    case 8:
      {
        cout << "Chance: Take a walk on the Boardwalk–Advance token to Boardwalk. If you pass go collect $200\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(39);
        h.setlocation(39);
        move(h, playermove);
        break;
      }
    case 9:
      {
        cout << "Chance: Bank pays you dividend of $50 $500\n";
        h.setmoney(h.getmoney() + 500);
        break;
      }
    case 10:
      {
        cout << "Chance:Advance to Illinois Ave. If you pass go collect $200\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(24);
        h.setlocation(24);
        move(h, playermove);
        break;
      }
    case 11:
      {
        cout << "Chance: Advance to St. Charles Place. If you pass go collect $200\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(11);
        h.setlocation(11);
        move(h, playermove);
        break;
      }
    case 12:
      {
        cout << "Chance: Get Out of Jail Free. This card may be kept until needed.\n";
        break;
      }
    default:
      cout << "Error statement\n";
    }
  } else if (g.getuser() == false) {
    switch (random) {
    case 1:
      {
        cout << "Chance: Go to Jail–Go directly to Jail–Do not pass Go, do not collect $200\n";
        g.setnpcprison(false);
        jail(h, c, g, playermove, computermove);
        break;
      }
    case 2:
      {
        cout << "Chance: A group of guest wins a class action suit against your hotel pay each player $500\n";
        c.setmoney(c.getmoney() - 500);
        h.setmoney(h.getmoney() + 500);
        break;
      }
    case 3:
      {
        cout << "Chance: Take a trip to Reading Railroad–If you pass Go, collect $200\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(5);
        c.setlocation(5);
        complayermove(c, computermove);
        break;
      }
    case 4:
      {
        cout << "Chance: Pay poor tax of $150\n";
        c.setmoney(c.getmoney() - 150);
        break;
      }
    case 5:
      {
        cout << "Chance: You have won a crossword competition—Collect $50\n";
        c.setmoney(c.getmoney() + 50);
        break;
      }
    case 6:
      {
        cout << "Chance: Advance to go collect $200\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(0);
        c.setlocation(0);
        complayermove(c, computermove);
        cout << "You passed 'Go' collect $200\n";
        c.setmoney(c.getmoney() + 200);
        break;
      }
    case 7:
      {
        cout << "Chance: Go Back 3 Spaces.\n";
        computermove[c.getlocation()] = 0;
        c.setlocation(c.getlocation() - 3);
        computermove[c.getlocation()] = 1;
        break;
      }
    case 8:
      {
        cout << "Chance: Take a walk on the Boardwalk–Advance token to Boardwalk. If you pass go collect $200\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(39);
        c.setlocation(39);
        complayermove(c, computermove);
        break;
      }
    case 9:
      {
        cout << "Chance: Your building and loan matures—Collect of $500\n";
        c.setmoney(c.getmoney() + 500);
        break;
      }
    case 10:
      {
        cout << "Chance: Advance to Illinois Ave—If you pass Go. If you pass go collect $200\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(24);
        c.setlocation(24);
        complayermove(c, computermove);
        break;
      }
    case 11:
      {
        cout << "Chance: Advance to St. Charles Place. If you pass go collect $200\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(11);
        c.setlocation(11);
        complayermove(c, computermove);
        break;
      }
    case 12:
      {
        cout << "Chance: Get Out of Jail Free. This card may be kept until needed.\n";
        break;
      }
    default:
      cout << "Error statement\n";
    }
  }
}
int chest(human & h, npc & c, game & g, int playermove[], int computermove[]) {
  int random = rand() % 15 + 1;
  if (g.getuser() == true) {
    switch (random) {
    case 1:
      {
        cout << "Community Chest: Bank error in your favor. Collect $2000 \n";
        h.setmoney(h.getmoney() + 2000);
        break;
      }
    case 2:
      {
        cout << "Community Chest:Income tax refund. Receive $100 \n";
        h.setmoney(h.getmoney() + 100);
        break;
      }
    case 3:
      {
        cout << "Community Chest: Advance to 'Go'(Collect $200)\n";
        playermove[h.getlocation()] = 0;
        h.setdiceroll(0); 
        h.setlocation(0);
        move(h, playermove);
        cout << "You passed 'Go' collect $200\n";
        h.setmoney(h.getmoney() + 200);
        break;
      }
    case 4:
      {
        cout << "Community Chest: You have won second prize in a beauty contest. Collect $500\n";
        h.setmoney(h.getmoney() + 500);
        break;
      }
    case 5:
      {
        cout << "Community Chest:Pay hospital fees. Pay $500\n";
        h.setmoney(h.getmoney() - 500);
        break;
      }
    case 6:
      {
        cout << "Community Chest: It is your birthday. Collect $100 from each player \n";
        c.setmoney(c.getmoney() - 100);
        h.setmoney(h.getmoney() + 100);
        break;
      }
    case 7:
      {
        cout << "Community Chest: consultancy fees Collect $250 for your services\n";
        h.setmoney(h.getmoney() + 250);
        break;
      }
    case 8:
      {
        cout << "Community Chest: Pay school fees Pay $1000\n";
        h.setmoney(h.getmoney() - 1000);
        break;
      }
    case 9:
      {
        cout << "Community Chest: SYour building and loan matures. Collect $200\n";
        h.setmoney(h.getmoney() + 200);
        break;
      }
    case 10:
      {
        cout << "Community Chest: Win big at the casino. Collect $1000\n";
        h.setmoney(h.getmoney() + 1000);
        break;
      }
    case 11:
      {
        cout << "Community Chest: You owe back taxes. Pay $500 in fines\n";
        h.setmoney(h.getmoney() - 500);
        break;
      }
    case 12:
      {
        cout << "Community Chest: You win the lottery. Collect $1000\n";
        h.setmoney(h.getmoney() + 1000);
        break;
      }
    case 13:
      {
        cout << "Community Chest: INCOME TAX REFUND. Collect $100\n";
        h.setmoney(h.getmoney() + 100);
        break;
      }
    case 14:
      {
        cout << "Community Chest: Go directly to jail – Do not pass Go – Do not collect $200\n";
        g.setprison(false);
        jail(h, c, g, playermove, computermove);
        break;
      }
    case 15:
      {
        cout << "Get Out of Jail Free. This card may be kept until needed.\n";
        break;
      }
    default:
      cout << "Error statement\n";
    }
  } else if (g.getuser() == false) {
    switch (random) {
    case 1:
      {
        cout << "Community Chest: Life insurance matures. Collect $2000 \n";
        c.setmoney(c.getmoney() + 2000);
        break;
      }
    case 2:
      {
        cout << "Community Chest: Income tax refund. Receive $100\n";
        c.setmoney(c.getmoney() + 100);
        break;
      }
    case 3:
      {
        cout << "Community Chest: Advance to 'Go'(Collect $200)\n";
        computermove[c.getlocation()] = 0;
        c.setdiceroll(0);
        c.setlocation(0);
        complayermove(c, playermove);
        cout << "You passed 'Go' collect $200\n";
        c.setmoney(c.getmoney() + 200);
        break;
      }
    case 4:
      {
        cout << "Community Chest: Your trust fund becomes available. Collect $500\n";
        c.setmoney(c.getmoney() + 500);
        break;
      }
    case 5:
      {
        cout << "Community Chest: Take dance lessons. Pay $500\n";
        c.setmoney(c.getmoney() - 500);
        break;
      }
    case 6:
      {
        cout << "Community Chest: You run for governor. Collect $100 from each player to fund your campaign\n";
        h.setmoney(h.getmoney() - 100);
        c.setmoney(c.getmoney() + 100);
        break;
      }
    case 7:
      {
        cout << "Community Chest: You coordinate opening day activities at Grand Opera Night. Collect $250 for your services\n";
        c.setmoney(c.getmoney() + 250);
        break;
      }
    case 8:
      {
        cout << "Community Chest: Pay school fees. Pay $1000\n";
        c.setmoney(c.getmoney() - 1000);
        break;
      }
    case 9:
      {
        cout << "Community Chest: Holiday Xmas Fund matures Collect $200\n";
        c.setmoney(c.getmoney() + 200);
        break;
      }
    case 10:
      {
        cout << "Community Chest: From sale of stock you get $1000\n";
        c.setmoney(c.getmoney() + 1000);
        break;
      }
    case 11:
      {
        cout << "Community Chest: You owe back taxes. Pay $500\n";
        c.setmoney(c.getmoney() - 500);
        break;
      }
    case 12:
      {
        cout << "Community Chest: You win the lottery. Collect $1000\n";
        c.setmoney(c.getmoney() + 1000);
        break;
      }
    case 13:
      {
        cout << "Community Chest: You inherit $100\n";
        c.setmoney(c.getmoney() + 100);
        break;
      }
    case 14:
      {
        cout << "Community Chest: Go to jail. DO NOT PASS 'GO', DO NOT COLLECT $200\n";
        g.setnpcprison(false);
        jail(h, c, g, playermove, computermove);
        break;
      }
    case 15:
      {
        cout << "Get Out of Jail Free. This card may be kept until needed.\n";
        break;
      }
    default:
      cout << "Error statement\n";
    }
  }
}