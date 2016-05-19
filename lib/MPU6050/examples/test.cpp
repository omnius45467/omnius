// ADXL345 accelerometer 2 servo motor control

#include <Wire.h>

#include <Servo.h>

Servo myservox;

Servo myservoy;

#define DEVICE (0x53)

#define TO_READ (6)

#define TRIGGER 16 byte buff[TO_READ] ;

int i;

void setup() {
    pinMode(TRIGGER,OUTPUT);

    digitalWrite(TRIGGER,HIGH);

    Wire.begin();

    myservox.attach(9);

    myservoy.attach(10);

    myservox.write(90);

    delay(25);

    myservoy.write(90);

    delay(25);

    writeTo(DEVICE, 0x2D, 0);

    writeTo(DEVICE, 0x2D, 16);

    writeTo(DEVICE, 0x2D, 8);
}

void loop() {
    int regAddress = 0x32;

    int x, y, z;
    digitalWrite(TRIGGER,LOW);

    delay(10);
    digitalWrite(TRIGGER,HIGH);

    readFrom(DEVICE, regAddress, TO_READ, buff);

    x = 0;
    y = 0;
    z = 0;

    for (i = 1; i <= 5; i++) {
        x += (((int) buff[1]) << 8) | buff[0];

        y += (((int) buff[3]) << 8) | buff[2];

        z += (((int) buff[5]) << 8) | buff[4];

        delay(10);

    }

    x /= 5;

    y /= 5;

    z /= 5;

    if (x < -255)x = -255;

    else if (x > 255)x = 255;

    if (y < -255)y = -255;

    else if (y > 255)y = 255;

    x = map(x, -255, 255, 0, 180);

    y = map(y, -255, 255, 0, 180);

    myservox.write(x);

    delay(25);

    myservoy.write(180 - y);

    delay(25);

    delay(200);
}

void writeTo(int device, byte address, byte val) {
    Wire.beginTransmission(device);

    Wire.write(address);
    Wire.write(val);

    Wire.endTransmission();
}

void readFrom(int device, byte address, int num, byte buff[]) {
    Wire.beginTransmission(device);

    Wire.write(address);

    Wire.endTransmission();

    Wire.beginTransmission(device);

    Wire.requestFrom(device, num);

    int i = 0;

    while (Wire.available()) {

        buff[i] = Wire.read();
        i++;

    }

    Wire.endTransmission();

}