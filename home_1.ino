#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Define the pins for LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define the pins for relay and Bluetooth
const int relayPin = 6; // Connect relay to pin 6
SoftwareSerial bluetooth(10, 9); // RX, TX

char state; // Variable to store incoming state

void setup() {
  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  // Initialize serial communication with Bluetooth module
  bluetooth.begin(9600);
  // Initialize serial communication with PC for debugging
  Serial.begin(9600);
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
}

void loop() {
  // Check if data is available to read from Bluetooth module
  if (bluetooth.available() > 0) {
    // Read the incoming byte
    state = bluetooth.read();
    // If the received state is '1', turn on the relay (bulb)
    if (state == '1') {
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bulb: ON");
      Serial.println("Bulb turned on.");
    }
    // If the received state is '0', turn off the relay (bulb)
    else if (state == '0') {
      digitalWrite(relayPin, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bulb: OFF");
      Serial.println("Bulb turned off.");
    }
  }
}

