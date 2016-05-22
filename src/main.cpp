#include "Arduino.h"
#include "Initalize.h"
//#include "Timing.h"
#include "PciListener.h"
#include "SoftTimer.h"


int firstTime = 1;

void callBack1(Task *me) {
    testStand();
}

void callBack2(Task *me) {

    headSweep();
}

void callBack3(Task *me) {

    testOLED();
//    headSweep();


}


Task t1(100, callBack1);
Task t2(500, callBack2);
Task t3(1000, callBack3);


void setup() {

    Serial.begin(9600);
    initalizeServos();
    initalizePWM();
    initalizeMPU();
//    initializeSD();
    initalizeOLED();

    SoftTimer.add(&t1);

//    SoftTimer.add(&t2);

    SoftTimer.add(&t3);

}

//void loop(){
////    Serial.begin(9600);
////    headSweep();
////    testMPU();
//    SoftTimer.add(&t1);
//    SoftTimer.add(&t2);
////    SoftTimer.run();
////    testOLED();
////    Time();
////    Serial.end();
//}

