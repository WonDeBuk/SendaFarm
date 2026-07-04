#include "devices.h"
#include "connect.h"
#include "lib.h"

unsigned long lastMsg = 0;
void callback(char *Topic, byte *Payload, unsigned int Length);

void setup() {
   Serial.begin(115200);

   randomSeed(micros());

   if (DEBUGGING_MODE_IS_ON) showAvailableNetworks();

   connectWifi();
   setUpMQTT();
   connectMQTT();

   setUpLED();
   setUpLCD();
   setUpPumpRelay();
   setUpDHTSensor();
   setUpSoilMoistureSensor();
}

void loop() {
   Serial.println("----------------------------------------------");
   client.loop();

   if (WiFi.status() != wl_status_t::WL_CONNECTED) connectWifi();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[WIFI] GOOD");

   if (client.connected() != true) connectMQTT();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[MQTT] GOOD");

   /* DHT -> WEB */
   TempAndHumidity data = dhtSensor.getTempAndHumidity();
   String temperature = String(data.temperature, 1);
   String humidity = String(data.humidity, 1);

   Serial.println("Temp: " + temperature + " *C");
   Serial.println("Hum : " + humidity + " %");

   client.publish("senda-farm/dht/temperature", temperature.c_str());
   client.publish("senda-farm/dht/humidity", humidity.c_str());

   /* SMS -> WEB */
   String soilMoisture = String(getSoilMoisturePercentage(), 1);
   Serial.println("Moisture: " + soilMoisture + "%");
   client.publish("senda-farm/dht/soil_moisture", soilMoisture.c_str());

   /* LCD */
   if (LCD_DISPLAY_MODE == "DHT")
      displayLCD(
         "Temp: " + temperature + "*C",
         "Hum: " + humidity + "%"
      );
   
   else if (LCD_DISPLAY_MODE == "SMS") 
      displayLCD(
         "Moisture: " + soilMoisture + "%", 
         ""
      );

   /* + -> BUTTON (INPUT PIN) -> RELAY (IN) */
   digitalWrite(RELAY, digitalRead(BUTTON));
   
   delay(1000);
}

