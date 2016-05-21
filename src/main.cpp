#include "Arduino.h"
#include "Initalize.h"
#include "Timing.h"

void setup() {
    Serial.begin(9600);
    Serial.println("setup function");
<<<<<<< HEAD
//    initalizeServos();
//    initalizePWM();
//    initalizeMPU();
//    initializeSD();
    Serial.end();
=======
    initalizeServos();
    initalizePWM();
    initalizeMPU();
    initializePing();
    initializeSD();

>>>>>>> e2611c9c3a22ce3f789f9dfd8c4aaf1d4adc06ec
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




