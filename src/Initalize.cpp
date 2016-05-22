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
const int chipSelect = 10;

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
    uint8_t pin = 6;
    pinMode(pin, OUTPUT);

    HeadServoBase.attach(pin);
//    HeadServoBase.write(90);
    Serial.println("Head Servo Initialized");
}

void initalizePWM() {


    pwm.begin();
    pwm.setPWMFreq(60);
//    Serial.println("Testing Servo");
//    while ( servonum != 15) {
//        pwm.setPWM(servonum, 0, servoCenter());
//        delay(10);
//        servonum++;
//        if (servonum > 15) servonum = 6;
//    }
    Serial.println("PWM Initialized");

}

void testMPU() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    val = map(gx, -17000, 17000, 0, 180);
    if(val){
        HeadServoBase.write(val);
        pwm.setPWM(6, 0, servoCenter());
        pwm.setPWM(7, 0, servoCenter());
        pwm.setPWM(8, 0, servoCenter());
        pwm.setPWM(9, 0, servoCenter());
        pwm.setPWM(10, 0, servoCenter());
        pwm.setPWM(11, 0, servoCenter());
        pwm.setPWM(12, 0, servoCenter());
        pwm.setPWM(13, 0, servoCenter());
        pwm.setPWM(14, 0, servoCenter());
        pwm.setPWM(15, 0, servoCenter());
    }

    delay(9);
}

void testStand() {

        pwm.setPWM(6, 0, servoCenter());
        pwm.setPWM(7, 0, servoCenter());
        pwm.setPWM(8, 0, servoCenter());
        pwm.setPWM(9, 0, servoCenter());
        pwm.setPWM(10, 0, servoCenter());
        pwm.setPWM(11, 0, servoCenter());
        pwm.setPWM(12, 0, servoCenter());
        pwm.setPWM(13, 0, servoCenter());
        pwm.setPWM(14, 0, servoCenter());
        pwm.setPWM(15, 0, servoCenter());
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
//
//    pinMode(6, OUTPUT);
//    pinMode(7, INPUT);
//    Serial.print("Initializing ping sensor");
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
    delay(250);

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
    delay(250);

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
    delay(250);

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
    delay(250);
}

void initalizeOLED(){

    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    // init done

    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
//    delay(2000);

    // Clear the buffer.
    display.clearDisplay();
}
void headSweep(){
        HeadServoBase.write(90);
//    delay(100);
    for(int i = 0; i < 180; i++){
        HeadServoBase.write(i);
        delay(50);
    }
    delay(50);
    for(int i = 180; i > 0; i--){
        HeadServoBase.write(i);
        delay(50);
    }

    HeadServoBase.write(90);
//    delay(150);
}

