#include "game.hpp"
#include <stdint.h>
#include <HardwareSerial.h>
#include <FastLED.h>

Controller *c = nullptr;
Game *g = nullptr;
void setup() {
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(A1, OUTPUT); digitalWrite(A1, LOW);
    pinMode(A2, OUTPUT); digitalWrite(A2, LOW);
    pinMode(A3, OUTPUT); digitalWrite(A3, LOW);
    pinMode(A4, OUTPUT); digitalWrite(A4, LOW);
    Serial.begin(115200);
    //pinMode(8, OUTPUT); //LED
    //pinMode(LED_BUILTIN, OUTPUT);
    while(!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
    c = new Controller(/*6*/);
    g = new Game(c, 4, 6);
}

void loop() {
    static Coord btn, prev_btn = {UINT8_MAX, UINT8_MAX};
    //Check if a button is pressed
    btn = g->c->check_button();
    if(btn.x != prev_btn.x && btn.y != prev_btn.y) {
        if(btn.x == UINT8_MAX)
            Serial.println("No button press");
        else {
            Serial.print("Button press : ");
            Serial.print(btn.x);
            Serial.print(';');
            Serial.println(btn.y);
            g->press(btn.x, btn.y);
        }
        prev_btn = btn;
    }
    delay(100);
}
