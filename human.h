/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   human.h
 * Author: Your Name <Marcus Depew @mdepew1@gmail.com>
 *
 * Created on July 23, 2018, 6:06 PM
 */

#ifndef HUMAN_H
#define HUMAN_H



#endif /* HUMAN_H */

#include <string>
#include "player.h"

class human : public player {
public:
    human();
    void setsym(std::string );
    void setdiceroll(int);
    void setmoney(int);
    void setlocation(int);
        int getmoney() { return balance; }

    int getlocation() { return location; }

    int getdiceroll() { return diceroll; }
    std::string getsym() { return symbol; }

};