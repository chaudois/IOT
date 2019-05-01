#include "controller.hpp"
#include <FastLED.h>

CRGB leds[24] = {CRGB::Black};
const CRGB colors[] = {CRGB::Pink, CRGB::Red, CRGB::White, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Purple};

Controller::Controller(/*int pinData*/) {
    FastLED.addLeds<WS2812B, 6, GRB>(leds, 24);
    FastLED.setBrightness(15);
    /*for(uint8_t i=0 ; i < 24 ; i++)
        leds[i] = CRGB::Black;*/
    FastLED.show();
}

void Controller::activateLED(int x, int y,int color) {
    leds[x*4 + y] = colors[color];
    FastLED.show();
}

void Controller::disactivateLED(int x, int y) {
    leds[x*4 + y] = CRGB::Black;
    FastLED.show();
}
