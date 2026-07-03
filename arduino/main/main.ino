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

   setUpDHTSensor();
   setUpSoilMoistureSensor();
   setUpLED();
   // setUpLCD();
}

void loop() {
   Serial.println();
   client.loop();

   if (WiFi.status() != wl_status_t::WL_CONNECTED) connectWifi();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[WIFI] GOOD");

   if (client.connected() != true) connectMQTT();
   else if (DEBUGGING_MODE_IS_ON) Serial.println("[MQTT] GOOD");

   /* DHT -> WEB */
   TempAndHumidity data = dhtSensor.getTempAndHumidity();
   String temperature = String(data.temperature, 2);
   String humidity = String(data.humidity, 2);

   Serial.println("T: " + temperature);
   Serial.println("H: " + humidity);   

   client.publish("senda-farm/dht/temperature", temperature.c_str());
   client.publish("senda-farm/dht/humidity", humidity.c_str());

   /* SMS -> WEB */
   String soilMoisture = String(getSoilMoisturePercentage());
   Serial.println("SM:" + soilMoisture + "%");
   client.publish("senda-farm/dht/soil_moisture", soilMoisture.c_str());

   /* BUTTON -> RELAY -> PUMP */

   delay(1000);
}

