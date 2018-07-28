/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.h
 * Author: Your Name <Marcus Depew @mdepew1@gmail.com>
 *
 * Created on July 25, 2018, 6:11 PM
 */

#ifndef GAME_H
#define GAME_H



#endif /* GAME_H */

class game {
protected:
        int turn;
    bool user;//which user has turn
    bool prison;//player jail 
    
    bool games;// till winner continue
    bool npcprison;//computer kail 

public:
    game();
    
        void setprison(bool);
    
    void setnpcprison(bool);
    void setturn(int);
    void setuser(bool);

    
    bool getgame() const { return games; }
    void setgame(bool);
    bool getprison() const { return prison; }
    bool getuser() const { return user; }
    bool getnpcprison() const { return npcprison; }


    
        int getturn() const { return turn; }
};

