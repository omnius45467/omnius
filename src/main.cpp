#include "Arduino.h"
#include "Initalize.h"
#include "Timing.h"

void setup() {
    Serial.begin(9600);
    Serial.println("setup function");

    initalizeServos();
    initalizePWM();
    initalizeMPU();
//    initializeSD();
    initalizeOLED();
    Serial.end();

}

void loop(){
    Serial.begin(9600);
    headSweep();
    testMPU();
    testOLED();
//    Time();
    Serial.end();
}

