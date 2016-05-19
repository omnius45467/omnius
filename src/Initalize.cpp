//
// Created by Jeremy Robles on 5/17/16.
//
#include "Arduino.h"
#include "Servo.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "NewPing.h"
#include "SPI.h"
#include "SD.h"

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600

// our servo # counter
uint8_t servonum = 6;

Servo HeadServoBase;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
MPU6050 mpu;

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4;

int val, val_x, val_y, negative_val;
int prevVal;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int servoCenter() {
    int min = SERVOMIN;
    int max = SERVOMAX;
    int center;
    center = (min + max) / 2;
    return center;
}

void initalizeServos() {
    uint8_t pin = 12;
    pinMode(pin, OUTPUT);

    HeadServoBase.attach(pin);
    HeadServoBase.write(90);
    Serial.println("Head Servo Initialized");
}

void initalizePWM() {


    pwm.begin();
    pwm.setPWMFreq(60);
    Serial.println("Testing Servo");
    while ( servonum != 15) {
        pwm.setPWM(servonum, 0, servoCenter());
        delay(10);
        servonum++;
        if (servonum > 15) servonum = 6;
    }
    Serial.println("PWM Initialized");

}

void testMPU() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    val = map(gx, -17000, 17000, 0, 180);
    if(val){
        HeadServoBase.write(val);
        pwm.setPWM(6, 0, servoCenter());
        pwm.setPWM(7, 0, servoCenter());
        pwm.setPWM(8, 0, val);
        pwm.setPWM(9, 0, val);
    }


    delay(9);
}

void initalizeMPU(){

    Wire.begin();
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
    delay(1);
    testMPU();


}
void initializeSD(){

    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
    }
    Serial.println("card initialized.");
}
void initializePing(){

    pinMode(6, OUTPUT);
    pinMode(7, INPUT);
    Serial.print("Initializing ping sensor");
}
