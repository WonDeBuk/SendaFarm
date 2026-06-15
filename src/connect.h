#pragma once

#include "lib.h"

/* WIFI: [Nên dung 2.4Ghz, WPA2-Personal] */
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

void connectWifi() {
   if (DEBUGGING_MODE_IS_ON) {
      Serial.print("[WIFI] Connecting to ");
      Serial.println(SSID);      
   }

   WiFi.begin(SSID, PASSWORD);

   while (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] No Signal . . .");
      delay(5000);
      Serial.println("[WIFI] Reconnecting . . .");
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

void connectMQTT() {
   String clientID = "ESP32-" + String(random(0xFFFF), HEX);
   const char *clientUserName = "Senda1";
   const char *clientPassword = "Senda123456";

   while (client.connected() != true) {
      if (client.connect(clientID.c_str(), clientUserName, clientPassword)) {
         Serial.println("[MQTT] Connected");
         client.publish("senda-farm/mqtt", "farm");
         client.subscribe("senda-farm/mqtt");
      }
      else {
         Serial.println("[MQTT] No Signal . . .");
         delay(5000);
         Serial.println("[MQTT] Reconnecting . . .");
      }
   }

   Serial.println("[MQTT] Connected");
}