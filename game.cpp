

#include "game.h"

game::game() {
    user=true;
games=true;    
prison=true;
    npcprison=true;
    
    turn=1;
}
void game::setturn(int t){
    turn = t;
}
void game::setwho(bool w){
    user = w;
}

void game::setcprison(bool c){
    npcprison = c;
}
void game::setgame(bool g){
    games = g;
}
void game::setprison(bool p){
    prison = p;
}



