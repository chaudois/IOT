#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <stdint-gcc.h>
#include <FastLED.h>

typedef struct {
    uint8_t x, y;
} Coord;
class Controller {
  public:
    Controller(/*int pinData*/);

    void activateLED(int i, int i1,int color);

    void disactivateLED(int i, int i1);
    
    Coord check_button();
    bool blink;
    CRGB leds[24] = {CRGB::Black};
    CRGB ledsCopy[24] = {CRGB::Black};
};

#endif //CONTROLLER_HPP
