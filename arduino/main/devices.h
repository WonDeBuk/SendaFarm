#pragma once
#include "lib.h"

/* PIN SETUP */
const int DHT = 23;
const int SMS = 34;
const int LED = 18;
const int BUTTON = 5;
const int RELAY = 25;

/* ESP32 alr declared
const int SDA = 21;
const int SCL = 22;
*/

/* 
* DHT -> WEB 
* DHT -> LCD 
*/

DHTesp dhtSensor;
void setUpDHTSensor() {
   dhtSensor.setup(DHT, DHTesp::DHT11);
}

/*
SMS -> WEB
SMS -> LCD
*/

const int PEAK_AIR_VALUE = 4095; // VALUE IN AIR
const int PEAK_WET_VALUE = 2000; // VALUE IN WATER

int getSoilMoisturePercentage() {
   int rawData = analogRead(SMS);

   int moisture = map(rawData, PEAK_AIR_VALUE, PEAK_WET_VALUE, 0, 100);
   moisture = constrain(moisture, 0, 100);

   return moisture;
}

void setUpSoilMoistureSensor() {
   pinMode(SMS, INPUT);
}

/*
* SENSOR DATA -> LCD
* WEB -> LED MODE
*/

void setUpLED() {
   pinMode(LED, OUTPUT);
}

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C Address = 0x27

const String BLANK = "                ";
String row1_cached, row2_cached;

void displayLCD(const String& row1, const String& row2) {
   if (row1 != row1_cached) {
      lcd.setCursor(0, 0);
      lcd.print(BLANK);

      lcd.setCursor((16 - row1.length()) / 2, 0);
      lcd.print(row1);

      row1_cached = row1;
   }

   if (row2 != row2_cached) {
      lcd.setCursor(0, 1);
      lcd.print(BLANK);

      lcd.setCursor((16 - row2.length()) / 2, 1);
      lcd.print(row2);

      row2_cached = row2;
   }
}

void setUpLCD() {
   Wire.begin(SDA, SCL);
   lcd.begin(16, 2); // 16x2
   lcd.backlight();

   displayLCD("Hello, World!", "ESP32");
   delay(1000);
}

void setUpPumpRelay() {
   pinMode(BUTTON, INPUT_PULLDOWN); // Normally LOW
   digitalWrite(BUTTON, 1);
   pinMode(RELAY, OUTPUT);
}

