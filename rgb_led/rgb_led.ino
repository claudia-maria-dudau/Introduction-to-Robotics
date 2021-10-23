// pin ports
const int ledRedPin = 11;
const int ledGreenPin = 10;
const int ledBluePin = 9;

//potentiator ports
const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

// potentiator values
int potRedValue = 0;
int potGreenValue = 0;
int potBlueValue = 0;

// led brightness
int brightnessRed = 0;
int brightnessGreen = 0;
int brightnessBlue = 0;

// max values
int maxPotValue = 1023;
int maxLedValue = 255;

void setup() {
  // led pins are in OUTPUT mode
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);

  // potentiator pins are in INPUT mode
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);
}

void loop() {
  // reading potentiator values
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  // calculating brightness
  // maping the values from [0..1023] (potentiator) to [0..255] (led)
  brightnessRed = map(potRedValue,  0,  maxPotValue,  0,  maxLedValue);
  brightnessGreen = map(potGreenValue,  0,  maxPotValue,  0,  maxLedValue);
  brightnessBlue = map(potBlueValue,  0,  maxPotValue,  0,  maxLedValue);

  // writing led values
  analogWrite(ledRedPin, brightnessRed);
  analogWrite(ledGreenPin, brightnessGreen);
  analogWrite(ledBluePin, brightnessBlue);
}
