
#include "human.h"

human::human() : Player(){
    location = 0;  
  balance = 1500;
    location = 0;

    symbol = "P";

    diceroll = 0;
}


void human::setroll(int r){
    diceroll = r;
}
void human::setsym(std::string s){
    symbol = s;
}
void human::setloc(int l){
    location = l;
}

void human::setmoney(int m){
    balance = m;
}
