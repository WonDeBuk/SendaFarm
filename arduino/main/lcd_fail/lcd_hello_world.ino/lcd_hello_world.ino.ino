#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);   // SDA, SCL (change if your wiring is different)

	lcd.begin(16, 2);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello");
}

void loop() {
	Serial.println("RUNNINGQWIFU)!FN");
	lcd.print("Hello");
	lcd.backlight();
	delay(1000);
	lcd.noBacklight();
	delay(1000);
}