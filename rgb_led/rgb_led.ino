// led pins
const int ledRedPin = 11;
const int ledGreenPin = 10;
const int ledBluePin = 9;

// potentiometer pins
const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

// potentiometer values
int potRedValue = 0;
int potGreenValue = 0;
int potBlueValue = 0;

// led brightness
int brightnessRed = 0;
int brightnessGreen = 0;
int brightnessBlue = 0;

// max values
const int maxPotValue = 1023;
const int maxLedValue = 255;

void setup() {
  // led pins are in OUTPUT mode
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);

  // potentiometer pins are in INPUT mode
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);
}

void loop() {
  readPotValues();

  calculateBrightness();

  setLedValues();
}

// read value of each potentiometer
void readPotValues() {
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);
}

// calculate brightness of each color
void calculateBrightness() {
  // maping the values from [0..1023] (potentiometer) to [0..255] (led)
  brightnessRed = map(potRedValue,  0,  maxPotValue,  0,  maxLedValue);
  brightnessGreen = map(potGreenValue,  0,  maxPotValue,  0,  maxLedValue);
  brightnessBlue = map(potBlueValue,  0,  maxPotValue,  0,  maxLedValue);
}

// set color of the RGB led
void setLedValues() {
  analogWrite(ledRedPin, brightnessRed);
  analogWrite(ledGreenPin, brightnessGreen);
  analogWrite(ledBluePin, brightnessBlue);
}
