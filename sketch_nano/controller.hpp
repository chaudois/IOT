#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <stdint.h>
#include <FastLED.h>

typedef struct {
    uint8_t x, y;
} Coord;
class Controller {
  public:
    Controller(/*int pinData*/);
    void activateLED(int x, int y, int color);
    void disactivateLED(int x, int y);
    
    Coord check_button();
    bool blink;
    CRGB leds[24] = {CRGB::Black};
    CRGB ledsCopy[24] = {CRGB::Black};
};

#endif //CONTROLLER_HPP
