# 1 "C:\\Users\\HP\\AppData\\Local\\Temp\\tmpvgh1e9t0"
#include <Arduino.h>
# 1 "D:/FIT-HCMUS K24/Year 2/Semester 3/IOT/Project/SENDA-FARM/src/main.ino"
#include "devices.h"
#include "connect.h"
#include "lib.h"

unsigned long lastMsg = 0;
void callback(char *Topic, byte *Payload, unsigned int Length);
void setup();
void loop();
#line 8 "D:/FIT-HCMUS K24/Year 2/Semester 3/IOT/Project/SENDA-FARM/src/main.ino"
void setup() {
   Serial.begin(115200);
   randomSeed(micros());

   if (DEBUGGING_MODE_IS_ON) showAvailableNetworks();

   connectWifi();

   setUpMQTT();
   connectMQTT();

   setUpDHTSensor();
   setUpLED();
   setUpWaterPump();
   setUpLCD();
}

void loop() {
   if (WiFi.status() != wl_status_t::WL_CONNECTED) connectWifi();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[WIFI] GOOD");

   if (client.connected() != true) connectMQTT();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[MQTT] GOOD");

   client.loop();


   TempAndHumidity Data = dhtSensor.getTempAndHumidity();
   String Temperature = String(Data.temperature, 2);
   String Humidity = String(Data.humidity, 2);

   Serial.println("T: " + Temperature);
   Serial.println("H: " + Humidity);

   client.publish("senda-farm/dht/temperature", Temperature.c_str());
   client.publish("senda-farm/dht/humidity", Humidity.c_str());


   displayLCD("T: " + Temperature, "H: " + Humidity);


   digitalWrite(RELAY_PIN, digitalRead(WATER_PUMP_BUTTON_PIN));

   delay(1000);
}