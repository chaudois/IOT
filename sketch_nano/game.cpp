
#include "game.hpp"
#include <algorithm>


using namespace std;
long boot=millis();

Game::Game(Controller* _c,int x,int y){
    this->c=_c;
    this->ledArray=vector<int>(x*y);
    this->width=x;
    this->height=y;
    int i=0;
    int color=0;
    while(i<x*y){
        if(i%3==0)color++;

        this->ledArray[i]=color-1;
        i++;
    }
   


}

void Game::press(int x,int y){
    if(this->c->blink){
      this->start=millis();
      this->c->blink=false;
      this->WonLED.clear();
      this->TmpLed.clear();
      for(int i=0;i<24;i++){
          this->c->leds[i]={CRGB::Black};

      }
       randomSeed(millis()-boot);

      long randNumber = random(25);
  
      
      for (int i = 0; i < 24; i++)
      {
          int j = random(0, 23);
      
          int t = ledArray[i];
          ledArray[i] = ledArray[j];
          ledArray[j] = t;
  
      }
      for(int i=0;i<24;i++){
          Serial.println(ledArray[i]);
      }
    }
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

        //give a chance to the player to see the cliked led's color
        this->c->activateLED(x,y,this->ledArray[ledCode]);
        delay(500);
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
    if(this->WonLED.size()==this->ledArray.size()){
      this->c->blink=true;
      bestScore.push_back(millis()-this->start);
      sort(bestScore.begin(),bestScore.end());
      
    }

}
