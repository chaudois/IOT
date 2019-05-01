#include "game.hpp"

Game::Game(Controller* _c,int x,int y){
    this->c=_c;
}

void Game::press(int x,int y){
    this->c->activate(x,y);
}
