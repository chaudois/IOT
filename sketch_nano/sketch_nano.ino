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
    check_serial();
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

void check_serial() {
    if(Serial.available() > 0) {
        if(Serial.read() == 'd') {
            if(Serial.peek() == '\n') Serial.read();
            Serial.println("Debug mode loop");
            bool _continue = true;
            do {
                while(Serial.available() <= 0) delay(10);
                switch(Serial.peek()) {
                    case 'o':
                        Serial.read();
                        if(Serial.peek() == '\n') Serial.read();
                        while(Serial.available() <= 0) delay(10);
                        if(Serial.peek() == 'n') {
                            fill_solid(c->leds, 24, CRGB::White);
                            FastLED.show();
                        } else if(Serial.peek() == 'f') {
                            FastLED.clear();
                            FastLED.show();
                        } else {
                          Serial.println("Not recognize");
                        }
                        break;
                    case 't':
                        Serial.println("Test mode");
                        c->blink = false;
                        Coord prev = {UINT8_MAX, UINT8_MAX};
                        uint8_t i;
                        do {
                          #define sub(AX, txt) digitalWrite(AX, HIGH); \
                            for(i=2 ; i <= 7 ; i++) { \
                              if(digitalRead(i) == HIGH) { \
                                Serial.print("input "); \
                                Serial.print(txt); \
                                Serial.print(' '); \
                                Serial.println(i); \
                              } \
                            } \
                            digitalWrite(AX, LOW);
                            sub(A1, "A1");
                            sub(A2, "A2");
                            sub(A3, "A3");
                            sub(A4, "A4");
                            /*const Coord pos = c->check_button();
                            if(pos.x == prev.x && pos.y == prev.y) {
                                c->disactivateLED(pos.x, pos.y);
                                prev = pos;
                                if(pos.x != UINT8_MAX) {
                                  Serial.print("btn ");
                                  Serial.print(pos.x);
                                  Serial.print(' ');
                                  Serial.println(pos.y);
                                  c->activateLED(pos.x, pos.y, 1);
                                }
                            }*/
                        } while(Serial.read() != 's');
                        break;
                    case 'q':
                        _continue = false;
                        break;
                    default:
                        Serial.println("Command not recognize");
                }
                Serial.read();
                if(Serial.peek() == '\n') Serial.read();
            } while(_continue);
            Serial.println("Exiting Debug mode");
        } else {
            Serial.println("Bad input");
        }
    }
}
