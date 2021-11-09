// 7-segment display pins
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

// buzzer pin
const int buzzerPin = 10;

// antenna pin
const int antennaPin = A0;

// tone variables
int buzzerTone = 0;
int toneDuration = 10;

// sample set 
const int sampleSize = 500;
float averageVal = 0;
int sample = 0;
unsigned long sampleSum = 0;
const int maxConstraint = 100;

const int segSize = 8;
const int noOfDigits = 10;
int digit = 0;

// array of segment pins
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// matrix for witing digits 0-9 
byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // the 7-segment pins are in OUTPUT mode
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }

  // buzzer pin is in OUTPUT mode
  pinMode(buzzerPin, OUTPUT);

  // antenna pin is in INPUT mode
  pinMode(antennaPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // reading a set of samples from the antenna
  for (int i = 0; i < sampleSize; i++) {
    sample = analogRead(antennaPin);

    // summing the values from the sample set
    sampleSum += sample;
  }

  // calculating average value of the sample set,
  // constraining it to be in the 0-100 interval
  averageVal = sampleSum / sampleSize;
  averageVal = constrain(averageVal, 0, maxConstraint);

  // determining the corresponding digit for the average value
  digit = map(averageVal, 0, maxConstraint, 0, noOfDigits - 1);
  displayNumber(digit);

  // resetting the sum
  sampleSum = 0;
}

// displaying the number to the 7-segment dispaly
void displayNumber(byte digit) {
  // writing the digit
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // emitting a specific tone based on the digit 
  buzzerTone = (digit + 1) * 100;
  tone(buzzerPin, buzzerTone, toneDuration);
}
