#pragma once

#include <string>
#include "DHTesp.h"
// #include <LiquidCrystal_I2C.h>

#include <WiFi.h> // https://docs.arduino.cc/libraries/wifi/
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/api#setServer
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const bool DEBUGGING_MODE_IS_ON = false; // -> False = Less logs