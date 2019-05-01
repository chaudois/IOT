//
// Created by d.chaudois on 01/05/2019.
//

#include <vector>
#include <iostream>
#include "controller.hpp"
using namespace std;


Controller::Controller(int width, int height) {

}

void Controller::activateLED(int x, int y,int color) {

    cout<<"activating ("<<x<<","<<y<<") with color "<<color<<endl;

}

void Controller::disactivateLED(int x, int y) {
    cout<<"deactivating ("<<x<<","<<y<<")"<<endl;

}
