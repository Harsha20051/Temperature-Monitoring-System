// Temperature Monitoring System using LM35 and HC-05
// Created by Harshal Sonawane

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial bluetooth(8, 9); // RX, TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int tempPin = A0; // LM35 connected to A0

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.begin(16, 2);
  lcd.print(" Temp Monitor ");
  delay(2000);
  lcd.clear();
}

void loop() {
  int analogValue = analogRead(tempPin);
  float millivolts = (analogValue / 1023.0) * 5000;
  float tempC = millivolts * 0.1;
  float tempF = tempC * 1.8 + 32;

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempF, 1);
  lcd.print((char)223);
  lcd.print("F");

  // Send to Bluetooth (MIT App Inventor)
  bluetooth.print("S;");
  bluetooth.print(tempC, 0);
  bluetooth.print(";");
  bluetooth.print(tempF, 0);
  bluetooth.println(";");

  delay(1000); // Wait 1 second
}
