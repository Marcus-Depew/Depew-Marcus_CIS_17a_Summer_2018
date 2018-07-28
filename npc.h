
/* 
 * File:   npc.h
 * Author: Your Name <Marcus Depew @mdepew1@gmail.com>
 *
 * Created on July 25, 2018, 11:08 AM
 */

#ifndef NPC_H
#define NPC_H



#endif /* NPC_H */

#include "player.h"

class npc : public player{
public:
    npc();
  
        int getdiceroll() { return diceroll; }
    void setsym(std::string);
    void setmoney(int);

    void setdiceroll(int);
    int getmoney() { return balance; }

        void setlocation(int);

    std::string getsym() { return symbol; }
        int getlocation() { return location; }

};
