// led pins
// cars semaphore
const int ledGreenPin1 = 2;
const int ledYellowPin1 = 3;
const int ledRedPin1 = 4;

// pedestrians semaphore
const int ledGreenPin2 = 5;
const int ledRedPin2 = 6;

// push button 
const int pushButton = 7;

// led states (green for cars & red for pedestrians)
bool ledRedState1 = LOW;
bool ledYellowState1 = LOW;
bool ledGreenState1 = HIGH;

bool ledRedState2 = HIGH;
bool ledGreenState2 = LOW;

bool buttonState = LOW;

// debounce variables
bool reading = LOW;
bool lastReading = LOW;
unsigned int lastDebounceTime = 0;
const int debounceInterval = 50;

// changing sempahore variables
bool pedestrianSemaphoreOn = false;
unsigned int startChange = 0;
unsigned int elapsedTime = 0;

// all the intervals are relative to the moment of pressing the button
const int greenToYellowInterval = 5000;
const int greenToRedCarsInterval = 10000;
const int carsToPedestriansInterval = 12000;
const int greenToIntermittentInterval = 22000;
const int greenToRedPedestriansInterval = 27000;
const int pedestriansToCarsInterval = 29000;

// intermitten lighting variables
unsigned int lastChanged = 0;
const int intermittenInterval = 500;

void setup() {
  // button pin is in INPUT mode
  pinMode(pushButton, INPUT_PULLUP);
  
  // led pins are in OUTPUT mode
  pinMode(ledRedPin1, OUTPUT);
  pinMode(ledYellowPin1, OUTPUT);
  pinMode(ledGreenPin1, OUTPUT);
  pinMode(ledRedPin2, OUTPUT);
  pinMode(ledGreenPin2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // writing led values
  digitalWrite(ledRedPin1, ledRedState1);
  digitalWrite(ledYellowPin1, ledYellowState1);
  digitalWrite(ledGreenPin1, ledGreenState1);
  digitalWrite(ledRedPin2, ledRedState2);
  digitalWrite(ledGreenPin2, ledGreenState2);

  if (pedestrianSemaphoreOn) {
    pedestrianSemaphore();
  }

  readButton();
}

// reading the state of the button and seeing if there's a chnage in its state
void readButton() {
  reading = digitalRead(pushButton);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  /* trying to eliminate the possible noise by waiting a few miliseconds
  in order to make sure the button was pressed intentionally */
  if (millis() - lastDebounceTime > debounceInterval) {
    if (reading != buttonState) {
      buttonState = reading;
      // changing semaphore to give priority to pedestrians
      if (buttonState == HIGH && !pedestrianSemaphoreOn) {
        pedestrianSemaphoreOn = true;
        startChange = millis();
      }
    }
  }

  lastReading = reading;
}

// flow of the cars and pedestrians semaphores once the button is pressed
void pedestrianSemaphore() {
  elapsedTime = millis();
  
  if (elapsedTime- startChange > pedestriansToCarsInterval) {
    // CARS: green
    // PEDESTRAINS: red
    ledRedState1 = LOW;
    ledGreenState1 = HIGH;
    
    pedestrianSemaphoreOn = false;
  } else if (elapsedTime - startChange > greenToRedPedestriansInterval) {
    // CARS: red
    // PEDESTRIANS: red
    ledGreenState2 = LOW;
    ledRedState2 = HIGH;
  } else if (elapsedTime - startChange > greenToIntermittentInterval) {
    // CARS: red
    // PEDESTRIANS: intermittent green  
    if (elapsedTime - lastChanged > intermittenInterval) {
      ledGreenState2 = !ledGreenState2;
      lastChanged = millis();
    }
  } else if (elapsedTime - startChange > carsToPedestriansInterval) { 
    // CARS: red
    // PEDESTRIANS: green
    ledRedState2 = LOW;
    ledGreenState2 = HIGH;
  } else if (elapsedTime - startChange > greenToRedCarsInterval) {
    // CARS: yellow to red
    // PEDESTRIANS: red
    ledYellowState1 = LOW;
    ledRedState1 = HIGH;
  } else if (elapsedTime - startChange > greenToYellowInterval) {
    // CARS: green to yellow 
    // PEDESTRIANS: red
    ledGreenState1 = LOW;
    ledYellowState1 = HIGH;
  }
}
