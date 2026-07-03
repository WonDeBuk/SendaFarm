#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Use default ESP32 I2C pins
  // SDA = GPIO21, SCL = GPIO22
  // If you're using different pins, use:
  // Wire.begin(SDA_PIN, SCL_PIN);

  Wire.begin();

  Serial.println("\nI2C Scanner");
}

void loop() {
  Serial.println("Scanning...");

  int devices = 0;

  for (byte address = 8; address < 120; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devices++;
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.print("Found ");
    Serial.print(devices);
    Serial.println(" device(s).");
  }

  Serial.println();
  delay(5000);
}