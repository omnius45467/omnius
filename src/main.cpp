#include "Arduino.h"
#include "Initalize.h"
//#include "Timing.h"
#include "PciListener.h"
//#include "SoftTimer.h"
#include <TimedAction.h>
#include <pt.h>

//
//TimedAction stand = TimedAction(100,testStand);
//TimedAction sweep = TimedAction(50, headSweep);
//TimedAction oled = TimedAction(50,testOLED);
//TimedAction sensor = TimedAction(50, testMPU);


static struct pt pt1, pt2;

static int protothread1(struct pt *pt, int interval) {
    static unsigned long timestamp = 0;
    PT_BEGIN(pt);
//    while(1) { // never stop
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval);
    timestamp = millis(); // take a new timestamp
    testOLED();
//    }
    PT_END(pt);
}

static int protothread2(struct pt *pt, int interval) {
    static unsigned long timestamp = 0;
    PT_BEGIN(pt);
    while (1) { // never stop
        /* each time the function is called the second boolean
        *  argument "millis() - timestamp > interval" is re-evaluated
        *  and if false the function exits after that. */
        PT_WAIT_UNTIL(pt, millis() - timestamp > interval);
        timestamp = millis(); // take a new timestamp
        testStand();
    }
    PT_END(pt);
}


void setup() {

    Serial.begin(9600);
//    initalizeServos();
    initalizePWM();
//    initializeSD();
    initalizeOLED();
    initalizeMPU();
    PT_INIT(&pt1);
    PT_INIT(&pt2);
}

void loop() {


//    sensor.check();
//    stand.check();
//    oled.check();
//    sweep.check();
//    protothread1(&pt1, 100);
    sway();
//    delay(100);
//    protothread2(&pt2, 100);


}

