//#include <cstddef>
//#include <iostream>
#include "game.hpp"

void Controller::activate(int x, int y) {
    //
}

Game *g = nullptr;

void setup() {
  // put your setup code here, to run once:
  g = new Game(new Controller(), 6, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  //
  //g.press(i, j);
}
