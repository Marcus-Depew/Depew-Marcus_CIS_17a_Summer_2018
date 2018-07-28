/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hotel.h
 * Author: Your Name <Marcus Depew @mdepew1@gmail.com>
 *
 * Created on July 26, 2018, 6:09 AM
 */

#ifndef HOTEL_H
#define HOTEL_H



#endif /* HOTEL_H */

using namespace std;

class hotel{
private:
    string name;
    int buy;
    int rent;
public:
        void setbuy(int);
    void setname(string);
    void setbuy(int);
    
    void setrent(int);
       int getrent() const;
    int getbuy() const;
    int getrent() const;
    void print();
    
     string getname() const;
    
};