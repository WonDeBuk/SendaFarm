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

   /* DHT -> WEB */
   TempAndHumidity Data = dhtSensor.getTempAndHumidity();
   String Temperature = String(Data.temperature, 2);
   String Humidity = String(Data.humidity, 2);

   Serial.println("T: " + Temperature);
   Serial.println("H: " + Humidity);   

   client.publish("senda-farm/dht/temperature", Temperature.c_str());
   client.publish("senda-farm/dht/humidity", Humidity.c_str());

   /* DHT -> LCD */
   displayLCD("T: " + Temperature, "H: " + Humidity);

   /* BUTTON -> RELAY -> PUMP */
   digitalWrite(RELAY_PIN, digitalRead(WATER_PUMP_BUTTON_PIN));

   delay(1000);
}

