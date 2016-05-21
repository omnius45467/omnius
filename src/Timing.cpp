//
// Created by Jeremy Robles on 5/18/16.
//
#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "Time.h"

int count = 0;
int lastCount;

//// set up variables using the SD utility library functions:
////Sd2Card card;
////SdVolume volume;
////SdFile root;
//
//// change this to match your SD shield or module;
//// Arduino Ethernet shield: pin 4
//// Adafruit SD shields and modules: pin 10
//// Sparkfun SD shield: pin 8
//const int chipSelect = 4;

template<typename T>

inline T const &Cycle(T const &a, T const &b) {

    return a < b ? b : a;
}

int logData() {
    // make a string for assembling the data to log:
    int dataString = Cycle(count, lastCount);

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
//        dataFile.println("Cycle: " + dataString);
        dataFile.println(dataString);
        dataFile.close();
        // print to the serial port too:
        Serial.println(dataString);

    }
        // if the file isn't open, pop up an error:
    else {
        Serial.println("error opening datalog.txt");
    }
}


void Time() {
    lastCount = count;
    ++count;
    // digital clock display of the time
    Serial.print("Cycle: ");
    Serial.print(hour());
    Serial.print(minute());
    Serial.print(second());
    Serial.print(day());
    Serial.print(month());
    Serial.print(year());
    Serial.println();

}
