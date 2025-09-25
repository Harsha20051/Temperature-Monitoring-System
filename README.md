
# Temperature Monitoring System (Arduino + LM35 + LCD + Mobile App)

**Author:** Harshal Sonawane  
  YouTube - https://www.youtube.com/watch?v=iK3NZ1pDUPM

## 🔧 Overview

This project measures temperature using an **LM35** sensor, displays the values on a **16×2 LCD**, and also sends the readings to a **mobile app** via a **HC‑05 Bluetooth module**.

You can monitor **environment / body temperature** in real time, both on the LCD and your smartphone.

---

## 🛠️ Components Required

- Arduino (Uno / Nano / similar)  
- LM35 temperature sensor  
- 16×2 LCD (HD44780)  
- HC‑05 Bluetooth module  
- Wires, breadboard, and possibly a potentiometer (for LCD contrast)  
- Power supply (5 V)  

---

## 📷 Arduino Wiring / Connections

Here’s a summary (your pin numbers may vary):

| Component | Pin on Arduino | Notes |
|---|---|---|
| LM35 output | A0 | LM35 GND → GND, VCC → 5 V |
| LCD RS | 2 | As per your code |
| LCD EN | 3 | — |
| LCD D4 | 4 | — |
| LCD D5 | 5 | — |
| LCD D6 | 6 | — |
| LCD D7 | 7 | — |
| HC‑05 RX | 8 | (Arduino → HC-05 TX) |
| HC‑05 TX | 9 | (Arduino RX) |

Also connect GND lines together, ensure voltage levels are compatible, etc.

---

## 📜 Arduino Sketch

Here’s a simplified version (based on your code, slightly cleaned):

```cpp
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial bluetooth(8, 9);  // HC‑05 RX, TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int tempPin = A0;

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
  float tempC = analogValue * 0.48828125;  // (5V / 1023) * (1/10 mV per °C)
  float tempF = tempC * 1.8 + 32;

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.write(223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempF, 1);
  lcd.write(223);
  lcd.print("F   ");

  // Send over Bluetooth
  bluetooth.print("S;");
  bluetooth.print(tempC, 1);
  bluetooth.print(";");
  bluetooth.print(tempF, 1);
  bluetooth.println(";");

  delay(1000);
}
