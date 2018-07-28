
#include <iostream>
using namespace std;

#include "hotel.h"

string house::getName() const{
     return name;
 }

 void house::setName(string n){
     name=n;
 }
 void house::setBuy(int b){
     buy=b;
 }
 void house::setRent(int r){
     rent=r;
 }
 
 int house::getBuy() const{
     return buy;
 }

 void house::print(){
     cout<<"Cost: "<<buy<<endl;   

  cout<<"Name: "<<name<<endl;

     cout<<"Rent: "<<rent<<endl;
 }

 int house::getRent() const{
     return rent;
 }


