//#include <cstddef>
//#include <iostream>
#include "game.hpp"
#include <FastLED.h>
#include <stdint-gcc.h>
#include <HardwareSerial.h>

void Controller::activate(int x, int y) {
    //
}

Game *g = nullptr;

typedef struct {
    uint8_t x, y;
} Coord;

Coord check_button();

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
    pinMode(2, OUTPUT); digitalWrite(2, LOW);
    pinMode(3, OUTPUT); digitalWrite(3, LOW);
    pinMode(4, OUTPUT); digitalWrite(4, LOW);
    pinMode(5, OUTPUT); digitalWrite(5, LOW);
    Serial.begin(115200);
    // put your setup code here, to run once:
    g = new Game(new Controller(), 6, 4);
}

void loop() {
    static Coord btn, prev_btn = {UINT8_MAX, UINT8_MAX};
    //
    //g.press(i, j);

    btn = check_button();
    if(btn.x != prev_btn.x && btn.y != prev_btn.y) {
        if(btn.x == UINT8_MAX)
            Serial.println("No button press");
        else {
            Serial.print("Button press : ");
            Serial.print(btn.x);
            Serial.print(';');
            Serial.println(btn.y);
        }
        prev_btn = btn;
    }
    delay(100);
}

const uint8_t BTN_INPUTS[] = {A0, A1, A2, A3, A6, A7};
const uint8_t BTN_OUTPUT[] = {2, 3, 4, 5};
Coord check_button() {
    uint8_t i, j;
    for(i=0 ; i < sizeof(BTN_OUTPUT) ; i++) {
        digitalWrite(BTN_OUTPUT[i], HIGH);
        for(j=0 ; j < sizeof(BTN_INPUTS) ; j++) {
            if(digitalRead(BTN_INPUTS[j]) == HIGH) {
                digitalWrite(BTN_OUTPUT[i], LOW);
                return {i, j};
            }
        }
        digitalWrite(BTN_OUTPUT[i], LOW);
    }
    return {UINT8_MAX, UINT8_MAX};
}
