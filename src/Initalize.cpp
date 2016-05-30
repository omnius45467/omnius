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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SPI.h"
#include "SD.h"

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
        { B00000000, B11000000,
          B00000001, B11000000,
          B00000001, B11000000,
          B00000011, B11100000,
          B11110011, B11100000,
          B11111110, B11111000,
          B01111110, B11111111,
          B00110011, B10011111,
          B00011111, B11111100,
          B00001101, B01110000,
          B00011011, B10100000,
          B00111111, B11100000,
          B00111111, B11110000,
          B01111100, B11110000,
          B01110000, B01110000,
          B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

uint8_t servonum = 6;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
MPU6050 mpu;

int val,valLeft, valRight;
int prevVal;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void initalizePWM() {


    pwm.begin();
    pwm.setPWMFreq(60);
    Serial.println("Testing Servo");
    while ( servonum != 15) {
        pwm.setPWM(servonum, 0, 150);
        delay(10);
        servonum++;
        if (servonum > 15) servonum = 6;
    }
    Serial.println("PWM Initialized");

}


void initalizeMPU(){

    Wire.begin();
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "MPU Connected" : "MPU Connection failed");
    delay(1);


}

void testOLED() {
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(0, 0, i, display.height()-1, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=0; i<display.height(); i+=4) {
        display.drawLine(0, 0, display.width()-1, i, WHITE);
        display.display();
        delay(1);
    }
    delay(25);

    display.clearDisplay();
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(0, display.height()-1, i, 0, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
        display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
        display.display();
        delay(1);
    }
    delay(25);

    display.clearDisplay();
    for (int16_t i=display.width()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
        display.display();
        delay(1);
    }
    delay(25);

    display.clearDisplay();
    for (int16_t i=0; i<display.height(); i+=4) {
        display.drawLine(display.width()-1, 0, 0, i, WHITE);
        display.display();
        delay(1);
    }
    for (int16_t i=0; i<display.width(); i+=4) {
        display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
        display.display();
        delay(1);
    }
    delay(25);
}

void initalizeOLED(){

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.display();

    display.clearDisplay();
}

int servoCenter(){
    int min = SERVOMIN;
    int max = SERVOMAX;
    int center;
    center = (min + max) / 2;
//    Serial.println(center);
    return center;
}

int fortyfive(){
    int min = SERVOMIN;
    int max = servoCenter();

    int ff;

    ff = (min + max) / 2;

    return ff;
}
int onethirty(){
    int min = servoCenter();
    int max = SERVOMAX;

    int ot;

    ot = (min + max) / 2;

    return ot;
}

void sway() {
    int walkFrames[4][5] = {
            {servoCenter(), servoCenter(), servoCenter(), servoCenter(), servoCenter()},
            {fortyfive(), servoCenter(), servoCenter(), servoCenter(), fortyfive()},
            {servoCenter(), servoCenter(), servoCenter(), servoCenter(), servoCenter()},
            {onethirty(), servoCenter(), servoCenter(), servoCenter(), onethirty()},

    };
    for(int i = 6; i < 15; i++){
        pwm.setPWM(i, 0, servoCenter());

    }
    delay(500);

    for(int i = 6; i < 15; i++){

        if(i == 6 || i == 7){
            pwm.setPWM(i, 0, fortyfive());
        }else if(i == 14 || i == 15){
            pwm.setPWM(i, 0, fortyfive());
        }else{
            pwm.setPWM(i, 0, servoCenter());
        }

    }
    delay(500);
    for(int i = 6; i < 15; i++){
        pwm.setPWM(i, 0, servoCenter());

    }
    delay(500);

    for(int i = 6; i < 15; i++){

        if(i == 6 || i == 7){
            pwm.setPWM(i, 0, onethirty());
        }else if(i == 14 || i == 15){
            pwm.setPWM(i, 0, onethirty());
        }else{
            pwm.setPWM(i, 0, servoCenter());
        }

    }
    delay(500);
    for(int i = 6; i < 15; i++){
        pwm.setPWM(i, 0, servoCenter());

    }
    delay(500);

//    for(int i = 6; i < 8; i++) {
//        for (int j = 0; j < 4; j++) {
//            Serial.print("writing servo ");
//
//            Serial.print(walkFrames[0][j]);
//            Serial.println();
//            pwm.setPWM(6, 0, walkFrames[0][j]);
//            pwm.setPWM(7, 0, walkFrames[1][j]);
//            delay(100);
//        }
//    }

}
void
