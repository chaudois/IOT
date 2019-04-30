#include "controller.hpp"

class Game {
  public:
    Game(Controller *c, int size_x, int size_y);
    void press(int x, int y);

  private:
    Controller *c;
};
