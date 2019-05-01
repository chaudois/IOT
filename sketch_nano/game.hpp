#include "controller.hpp"
#include <vector>
using namespace std;
class Game {
  public:
    Game(Controller *c, int size_x, int size_y);
    void press(int x, int y);
    vector<int> ledArray;
    vector<int> WonLED;
    vector<int> TmpLed;

  private:
    Controller *c;
    int width;
    int height;
};
