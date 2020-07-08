/****************************************************  
 * ByteDisplayer
 *
 * Displays a byte prepresentation of integer values 
 * from 0 to 255 using 8 LEDs.
 *
 * Copyright (C) 2020 BITJUNGLE Rune Mathisen
 * This code is licensed under a GPLv3 license 
 * See http://www.gnu.org/licenses/gpl-3.0.html 
 * 
 ****************************************************/  

const int LED_PIN[] = {3, 4, 5, 6, 7, 8, 9, 10};
const int UP_BUTTON_PIN = 1;
const int DOWN_BUTTON_PIN = 2;
int upButtonState = HIGH;
int downButtonState = HIGH;
bool waitForButton = true;
int decimalValue = 0;
const int MIN_VAL = 0;
const int MAX_VAL = 255;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Setup starting...");
  for (int i = 0; i < 8; i++) {
    Serial.print("Configure LED ");
    Serial.println(i);
    pinMode(LED_PIN[i], OUTPUT);
    digitalWrite(LED_PIN[i], HIGH);
    delay(100);
    digitalWrite(LED_PIN[i], LOW);
  }
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  waitForButton = true;
  while (waitForButton) { // Listening for a key press
    upButtonState = digitalRead(UP_BUTTON_PIN);
    downButtonState = digitalRead(DOWN_BUTTON_PIN);
    if (upButtonState == LOW) {
      waitForButton = false;
      decimalValue++;
    } else if (downButtonState == LOW) {
      waitForButton = false;
      decimalValue--;
    } else {
      delay(50);
    }
  }

  // We have a key press, act on it
  // First, limit the decimal value to be displayed
  if (decimalValue > MAX_VAL) {
    decimalValue = MAX_VAL;
  } else if (decimalValue < MIN_VAL) {
    decimalValue = MIN_VAL;
  } else {
    //pass
  }
  // Now output the value to console and LED display
  delay(150);
  Serial.print("Value is ");
  Serial.println(decimalValue);
  displayByte(decimalValue);
  delay(150);
}

// An integer value between 0-255 is input.
// Turning LEDs 1-8 on/off is output.
void displayByte(byte byteToLed) {
  for (int i = 0; i < 8; i++) {
    if (bitRead(byteToLed, i) == 1) {
      digitalWrite(LED_PIN[i], HIGH); // turn the LED on
    } else {
      digitalWrite(LED_PIN[i], LOW); // turn the LED off
    }
  }
}
