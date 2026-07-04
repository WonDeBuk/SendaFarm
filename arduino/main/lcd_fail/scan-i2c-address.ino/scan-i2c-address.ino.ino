#include <Wire.h>
#define WIRE Wire // Change to Wire1 if using alternate I2C bus
void setup() {
 WIRE.begin();
 Serial.begin(115200);
 while (!Serial);
 Serial.println("\nI2C Scanner");
}
void loop() {
 byte error, address;
 int nDevices = 0;
 Serial.println("Scanning...");
 for (address = 1; address < 127; address++) {
   WIRE.beginTransmission(address);
   error = WIRE.endTransmission();
   if (error == 0) {
     Serial.print("I2C device found at address 0x");
     if (address < 16) Serial.print("0");
     Serial.println(address, HEX);
     nDevices++;
   } else if (error == 4) {
     Serial.print("Unknown error at address 0x");
     if (address < 16) Serial.print("0");
     Serial.println(address, HEX);
   }
 }
 if (nDevices == 0) Serial.println("No I2C devices found\n");
 else Serial.println("done\n");
 delay(5000); // Wait before rescanning
}