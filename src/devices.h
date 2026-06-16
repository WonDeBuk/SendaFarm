#pragma once

#include "lib.h"
/* 
* DHT -> WEB 
* DHT -> LCD 
*/
const int DHT_PIN = 23;
DHTesp dhtSensor;

void setUpDHTSensor() {
   // Sau nay dung DHT11
   dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

/*
* WEB -> LED
*/
const int LED_PIN = 22;
void setUpLED() {
   pinMode(LED_PIN, OUTPUT);
}


/*
* DHT -> LCD
* WEB -> CHON CHE DO LCD (KHONG KHI / TRONG DAT)
*/
const int LCD_DATA_PIN = 19;
const int LCD_CLOCK_PIN = 18;

// The default I2C address of the LCD1602 module is 0x27, 16x2 (I2C)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setUpLCD() {
   Wire.begin(LCD_DATA_PIN, LCD_CLOCK_PIN);
   lcd.init();
   lcd.backlight();

   lcd.setCursor(0, 0);
   lcd.print("Hello, World!");
   delay(500);
}

// Display Data
String LCD_CACHED = "";
void displayLCD(const String row1, const String row2) {
   if (row1 + row2 == LCD_CACHED) return;
   lcd.clear();
   LCD_CACHED = row1 + row2;

   lcd.setCursor(0, 0);
   lcd.print(row1);

   lcd.setCursor(0, 1);
   lcd.print(row2);
}

/*
* BUTTON -> RELAY -> MAY BOM
* 5VDC (ESP) -> RELAY
* Battery 6V -> RELAY (COM) -> May Bom
*/
const int WATER_PUMP_BUTTON_VCC = 32;
const int WATER_PUMP_BUTTON_PIN = 33;
void setUpPWaterPumpButton() {
   pinMode(WATER_PUMP_BUTTON_VCC, OUTPUT);
   digitalWrite(WATER_PUMP_BUTTON_VCC, HIGH);

   pinMode(WATER_PUMP_BUTTON_PIN, INPUT_PULLDOWN);
}

const int FAKE_RELAY_VCC = 16; // Can 5V
const int FAKE_WATER_PUMP_VCC = 17; // 6 -> 12 VDC
const int RELAY_PIN = 4;
void setUpWaterPumpRelay() {
   pinMode(FAKE_RELAY_VCC, OUTPUT);
   digitalWrite(FAKE_RELAY_VCC, HIGH);

   pinMode(FAKE_WATER_PUMP_VCC, OUTPUT);
   digitalWrite(FAKE_WATER_PUMP_VCC, HIGH);

   pinMode(RELAY_PIN, OUTPUT);
}

void setUpWaterPump() {
   setUpPWaterPumpButton();
   setUpWaterPumpRelay();
}