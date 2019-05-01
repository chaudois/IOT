
#include "game.hpp"
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Game::Game(Controller* _c,int x,int y){
    this->c=_c;
    this->ledArray=vector<int>(x*y);
    this->width=x;
    this->height=y;
    int i=0;
    int color=0;
    while(i<x*y){
        if(i%3==0)color++;

        this->ledArray[i]=color;
        i++;
    }


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto rng = std::default_random_engine {seed};
//    std::shuffle(std::begin(ledArray), std::end(ledArray), rng);

}

void Game::press(int x,int y){
    int ledCode=(x*this->width)+y;

    for(int i=0;i<this->WonLED.size();i++){//if the user click on an already won color, nothing happens
        if(ledCode==this->WonLED[i]){
            return;
        }
    }
    for(int i=0;i<this->TmpLed.size();i++){//same thing if he click on an already temporarily lit led
        if(ledCode==this->TmpLed[i]){
            return;
        }
    }
    if(this->TmpLed.size()==0){//if this is the first click
        this->TmpLed.push_back(ledCode);
        this->c->activateLED(x,y,this->ledArray[ledCode]);

    }else if(this->ledArray[this->TmpLed[0]]==this->ledArray[ledCode]){//if the clicked led is the same color as a previously clicked led
        this->TmpLed.push_back(ledCode);
        this->c->activateLED(x,y,this->ledArray[ledCode]);

    }else{//if this is another color

        for(int i=0;i<this->TmpLed.size();i++){//we deactivate all previously temporarily lit led

            int w=this->TmpLed[i]/this->width;
            int h=this->TmpLed[i]-(w*this->width);

            this->c->disactivateLED(w,h);
        }
        this->TmpLed.clear();

    }
    if(this->TmpLed.size()>=3){//if we get in a situation where 3 led of the same color have been lit
        for(int i=0;i<3;i++){
            this->WonLED.push_back(this->TmpLed[i]);
        }
        this->TmpLed.clear();
    }

}
