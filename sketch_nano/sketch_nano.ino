#include "game.hpp"
#include <stdint-gcc.h>
#include <HardwareSerial.h>

Game *g = nullptr;
void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(2, OUTPUT); digitalWrite(2, LOW);
    pinMode(3, OUTPUT); digitalWrite(3, LOW);
    pinMode(4, OUTPUT); digitalWrite(4, LOW);
    pinMode(5, OUTPUT); digitalWrite(5, LOW);
    Serial.begin(115200);
    // put your setup code here, to run once:
    g = new Game(new Controller(/*6*/), 4, 6);
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
