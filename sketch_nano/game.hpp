#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"
//#include <vector>
#include <ArduinoSTL.h>
using namespace std;
class Game {
  public:
    Game(Controller *c, int size_x, int size_y);
    void press(int x, int y);
    vector<int> ledArray;
    vector<int> WonLED;
    vector<int> TmpLed;
    Controller *c;

  private:
    int width;
    int height;
};

#endif //GAME_HPP
