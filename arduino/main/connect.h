#pragma once

#include "lib.h"

/* WIFI: [Nên dung 2.4Ghz, WPA2-Personal] */
const char *SSID = "esp32";
const char *PASSWORD = "12345678";

void connectWifi() {
   if (DEBUGGING_MODE_IS_ON) {
      Serial.print("[WIFI] Connecting to ");
      Serial.println(SSID);      
   }

   WiFi.begin(SSID, PASSWORD);
   delay(1000);

   while (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] No Signal . . .");
      Serial.println("[WIFI] Reconnecting . . .");         

      delay(500);
   }

   Serial.println("[WIFI] Connected");

   if (DEBUGGING_MODE_IS_ON) {
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());      
   }
}

void showAvailableNetworks() {
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(1000);

   int n = WiFi.scanNetworks();

   Serial.printf("[Wifi] Found %d networks\n", n);

   for (int i = 0; i < n; i++) {
      Serial.println(WiFi.SSID(i));
   }
}

/* MQTT */
const char *MQTT_SERVER = "a591126d24c94f1b923816f6c31b9baa.s1.eu.hivemq.cloud";
const int PORT = 8883;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void callback(char *, byte *, unsigned int);

void setUpMQTT() {
   espClient.setInsecure();
   client.setCallback(callback);
   client.setServer(MQTT_SERVER, PORT);   
}

void connectMQTT() {
   String clientID = "ESP32-" + String(random(0xFFFF), HEX);
   const char *clientUserName = "Senda1";
   const char *clientPassword = "Senda123456";

   while (client.connected() != true) {
      if (client.connect(clientID.c_str(), clientUserName, clientPassword)) {
         client.subscribe("senda-farm/output/led");
         client.subscribe("senda-farm/output/lcd");
      }
      else {
         Serial.println("[MQTT] No Signal . . .");
         Serial.println("[MQTT] Reconnecting . . .");
         delay(500);
      }
   }

   Serial.println("[MQTT] Connected");
}

String LCD_DISPLAY_MODE = "DHT"; // "DHT" or "SMS" 

void callback(char *Topic, byte *Payload, unsigned int Length) {
   String msg = "";
   for (int i = 0; i < Length; i++) msg += (char)Payload[i];

   Serial.println("Topic  : " + String(Topic));
   Serial.println("Message: " + String(msg));

   if (String(Topic) == "senda-farm/output/led" and msg == "true") digitalWrite(LED, 1);
   else if (msg == "false") digitalWrite(LED, 0);

   if (String(Topic) == "senda-farm/output/lcd") LCD_DISPLAY_MODE = msg;
}