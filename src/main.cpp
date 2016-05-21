#include "Arduino.h"
#include "Initalize.h"
#include "Timing.h"

void setup() {
    Serial.begin(9600);
    Serial.println("setup function");
//    initalizeServos();
//    initalizePWM();
//    initalizeMPU();
//    initializeSD();
    Serial.end();
}

void loop(){
    Serial.begin(9600);
//    testMPU();
    Time();
    Serial.end();
}
void dispatch(){
    /* This is what I will use to call functions that are accessible to run*/
}




