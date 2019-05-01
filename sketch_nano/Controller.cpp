#include "controller.hpp"
#include <FastLED.h>




const CRGB colors[] = {CRGB::DeepPink, CRGB::Red, CRGB::White, CRGB::OrangeRed, CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Cyan};
const uint8_t BTN_INPUTS[] = {A0, A1, A2, A3, A4, A5};
const uint8_t BTN_OUTPUT[] = {2, 3, 4, 5};


Controller::Controller(/*int pinData*/) {
    blink=true;
    FastLED.addLeds<WS2812B, 6, GRB>(leds, 24);
    FastLED.setBrightness(15);
    for(uint8_t i=0 ; i < 24 ; i++){
        leds[i] = CRGB::Black;
        ledsCopy[i]={CRGB::Black};
    }
      
    FastLED.show();
}

void Controller::activateLED(int x, int y,int color) {

    leds[x*4 + y] = colors[color];
    ledsCopy[x*4 + y] = colors[color];
    FastLED.show();
}

void Controller::disactivateLED(int x, int y) {
    leds[x*4 + y] = CRGB::Black;
    ledsCopy[x*4 + y] =  CRGB::Black;
    FastLED.show();
}
bool blinkState = false;
long start=millis();

Coord Controller::check_button(){

  if(blink){


    if(millis()-start>200){
       Serial.println("blinking");

       if(blinkState){
        for(int i=0;i<24;i++){
          leds[i]= {CRGB::Black};
        }
       }else{
          for(int i=0;i<24;i++){
             leds[i]=ledsCopy[i];
          }
       }
       FastLED.show();
       
      blinkState=!blinkState;
      start=millis();
    }
  }
  uint8_t i, j;
    for(i=0 ; i < sizeof(BTN_OUTPUT) ; i++) {
        digitalWrite(BTN_OUTPUT[i], HIGH);
        for(j=0 ; j < sizeof(BTN_INPUTS) ; j++) {
            if(digitalRead(BTN_INPUTS[j]) == HIGH) {
                digitalWrite(BTN_OUTPUT[i], LOW);
                return {j, i};
            }
        }
        digitalWrite(BTN_OUTPUT[i], LOW);
    }
    return {UINT8_MAX, UINT8_MAX};
}
