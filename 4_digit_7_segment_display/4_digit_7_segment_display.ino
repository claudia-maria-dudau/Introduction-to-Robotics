#include<EEPROM.h>

// shift register
const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;

// 4-digit 7-segment display
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int displayCount = 4;
int displays[displayCount] = { segD1, segD2, segD3, segD4 };
int currentDisplay = 0;

// joystick
const int pinSW = 2; 
const int pinX = A0; 
const int pinY = A1; 

// digits
const int noDigits = 10;
int digitArray[noDigits] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};
int digitOnDisplay[displayCount] = { 0, 0, 0, 0 };

// memory adresses where the digit on each display is stored on the EEPROM
int displayAddress[displayCount] = { 0, 1, 2, 3 };
int currentDisplayAddress = 4;

// states of the button press
bool changingDigit = false;

// joystick position
int xValue = 0;
int yValue = 0;
bool joyMoved = false;
const int minThreshold = 400;
const int maxThreshold = 600;

// blinking display
unsigned long lastChanged = 0;
const int blinkingInterval = 200;
bool dpState = LOW;

// debounce
const int debounceInterval = 50;

void setup() {
  // shift register pins are in OUTPUT mode
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // display pins are in OUTPUT mode
  for (int i = 0; i < displayCount; i++) {
    pinMode(displays[i], OUTPUT);
  }

  // joystick pins are in INPUT mode
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  
  // activate pull-up resistor + interruptions on the push-button pin 
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), toggle, FALLING);
  
  Serial.begin(9600);
}

void loop() {
  readFromMemory();
  
  showDisplays();

  if (changingDigit) {
    // changing the digit on the current display
    changeDigit(currentDisplay);
  } else {
    // changing between displays
    changeDisplay();
  }

  updateMemory();
}

// toggling between changing the dispaly and the digit on a certain display
void toggle() {
  static unsigned long lastDebounceTime = 0;

  // trying to eliminate the possible noise by waiting a few miliseconds before doing something
  if (millis() - lastDebounceTime > debounceInterval) {
    changingDigit = !changingDigit;
  }

  lastDebounceTime = millis();
}

// showing all digits on the 4 displays
void showDisplays() {
  for (int i = 0; i < displayCount; i++) {
    showDisplay(i);

    if (i == currentDisplay) {
      // decimal point to indicate the current selected display
      showDecimalPoint();
    } else {
      // no decimal point for the other displays
      writeReg(digitArray[digitOnDisplay[i]]);
    }
  }
}

// showing the decimal point on the selected display
void showDecimalPoint() {
  if (changingDigit) {
    // fixed decimal point
    writeReg(digitArray[digitOnDisplay[currentDisplay]] + 1);
  } else {
    // blinking decimal point
    if (millis() - lastChanged > blinkingInterval) {
      dpState = !dpState;
      lastChanged = millis();
    }

    if (dpState == LOW) {
      writeReg(digitArray[digitOnDisplay[currentDisplay]] + 1);
    } else {
      writeReg(digitArray[digitOnDisplay[currentDisplay]]);
    }
  }
}

// displaying the digit on the display
void writeReg(int digit) {
  // STCP to LOW
  digitalWrite(latchPin, LOW);

  // Writing data to shift register
  shiftOut(dataPin, clockPin, MSBFIRST, digit); 

  // Writing data to storage register
  digitalWrite(latchPin, HIGH);
  
}

// activating only one of the 4 displays
void showDisplay(int displayNumber) {
  // writing on the desired display
  digitalWrite(displays[displayNumber], LOW);

  delay(3);

  // shutting off all displays
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displays[i], HIGH);
  }
}

// changing the digit on one of the displays
void changeDigit(int displayNumber) {
   xValue = analogRead(pinX);

  // incrementing digit value 
  if (xValue < minThreshold && !joyMoved) {
    joyMoved = true;
    digitOnDisplay[displayNumber]++;

    if (digitOnDisplay[displayNumber] >= noDigits){
      digitOnDisplay[displayNumber] = 0;
    }
  }

  // decrementing digit value 
  if (xValue > maxThreshold && !joyMoved) {
    joyMoved = true;
    digitOnDisplay[displayNumber]--;

    if (digitOnDisplay[displayNumber] < 0){
      digitOnDisplay[displayNumber] = noDigits - 1;
    }
  }

  if (xValue > minThreshold && xValue < maxThreshold) {
    joyMoved = false;
  }
}

// changing the selected display
void changeDisplay() {
  yValue = analogRead(pinY);

  // moving right 
  if (yValue < minThreshold && !joyMoved) {
    joyMoved = true;
    currentDisplay--;

    if (currentDisplay < 0){
      currentDisplay = displayCount - 1;
    }
  }

  // moving left 
  if (yValue > maxThreshold && !joyMoved) {
    joyMoved = true;
    currentDisplay++;

    if (currentDisplay >= displayCount){
      currentDisplay = 0;
    }
  }

  if (yValue > minThreshold && yValue < maxThreshold) {
    joyMoved = false;
  }
}

// reading data from the EEPROM
void readFromMemory() {
  // reading the displayed digits 
  for (int i = 0 ; i < displayCount; i++) {
    digitOnDisplay[i] = EEPROM.read(displayAddress[i]);
  }

  // reading the position of the decimal point
  currentDisplay = EEPROM.read(currentDisplayAddress);
}

// updating data on the EEPROM
void updateMemory() {
  // updating the displayed digits
  for (int i = 0 ; i < displayCount; i++) {
    EEPROM.update(displayAddress[i], digitOnDisplay[i]);
  }

  // updating the position of the decimal point
  EEPROM.update(currentDisplayAddress, currentDisplay);
}
