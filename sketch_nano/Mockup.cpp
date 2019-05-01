//
// Created by d.chaudois on 01/05/2019.
//

#include <iostream>
#include "Mockup.h"
using namespace std;
void debug(int x){
    cout<<x<<endl;
}
void debug(vector<int> x){
    for(int i=0;i<x.size();i++){
        cout<<x[i]<<endl;
    }
}

void Mockup::setup() {

    this->c =new Controller(4,6);
    this->g = new Game(c, 4,6);

    cout << "setup() OK" << endl;

}
void Mockup::loop() {

    this->g->press(0,3);
    this->g->press(1,0);
    this->g->press(1,1);

    this->g->press(2,0);
    this->g->press(2,1);
    this->g->press(2,1);
    this->g->press(2,2);
    this->g->press(2,3);

    this->g->press(2,4);
    this->g->press(2,5);


    debug(this->g->TmpLed);
    cout<<endl;
    debug(this->g->WonLED);
    cout << "loop() OK" << endl;

}