#pragma once

#include "lib.h"

/* PIN SETUP */
const int DHT_PIN = 23;
const int SMS_PIN = 34;
const int LED_PIN = 18;

// const int LCD_DATA_PIN = 21;
// const int LCD_CLOCK_PIN = 22;

/* 
* DHT -> WEB 
* DHT -> LCD 
*/

DHTesp dhtSensor;
void setUpDHTSensor() {
   dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}


void setUpSoilMoistureSensor() {
   pinMode(SMS_PIN, INPUT);
}

const int PEAK_AIR_VALUE = 4095;
const int PEAK_WET_VALUE = 2000;
int getSoilMoisturePercentage() {
   int rawData = analogRead(SMS_PIN);

   int moisture = map(rawData, PEAK_AIR_VALUE, PEAK_WET_VALUE, 0, 100);
   moisture = constrain(moisture, 0, 100);

   return moisture;
}

/*
* WEB -> LED
*/

void setUpLED() {
   pinMode(LED_PIN, OUTPUT);
}


/*
* DHT -> LCD
* WEB -> CHON CHE DO LCD (KHONG KHI / TRONG DAT)
*/
