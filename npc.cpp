

#include "npc.h"

npc::npc() : npc(){
    symbol = "C";
    balance = 1500;
    location = 0;
    diceroll = 0;
}
void npc::setsym(std::string s){
    symbol = s;
}
void npc::setmoney(int m){
    balance = m;
}
void npc::setroll(int r){
    diceroll = r;
}
void npc::setloc(int l){
    location = l;
}


