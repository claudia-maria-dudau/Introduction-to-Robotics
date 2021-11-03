// led pins
// car semaphore
const int carGreenLedPin = 3;
const int carYellowLedPin = 4;
const int carRedLedPin = 5;

// pedestrian semaphore
const int peopleGreenLedPin = 6;
const int peopleRedLedPin = 7;

// push button 
const int pushButton = 2;

// passive buzzer
const int buzzerPin = 11;

// led states (DEFAULT: green for cars & red for pedestrians)
bool carRedLedState = LOW;
bool carYellowLedState = LOW;
bool carGreenLedState = HIGH;

bool peopleRedLedState = HIGH;
bool peopleGreenLedState = LOW;

// button state
bool buttonState = LOW;

// debounce interval
const int debounceInterval = 100;

// changing sempahore variables
volatile bool pedestrianSemaphoreOn = false;
volatile unsigned int startChange = 0;
unsigned int elapsedTime = 0;

// system flow intervals
// all the intervals are relative to the moment of pressing the button
const int greenToYellowInterval = 10000;
const int greenToRedCarsInterval = 13000;
const int carsToPedestriansInterval = 14000;
const int greenToIntermittentInterval = 24000;
const int greenToRedPedestriansInterval = 29000;
const int pedestriansToCarsInterval = 30000;

// intermitten lighting variables
unsigned int lastChangedLed = 0;
const int intermittenInterval = 500;

// buzzer variables
int buzzerTone = 5000;
int toneDuration = 10;
unsigned int lastChangedBuzzer = 0;

// sound intervals
const int buzzerDelayGreen = 1000;
const int buzzerDelayIntermittenGreen = 500;

void setup() {
  // button pin is in INPUT mode + accepts interrupts
  pinMode(pushButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButton), toggle, FALLING);
  
  // led pins are in OUTPUT mode
  pinMode(carRedLedPin, OUTPUT);
  pinMode(carYellowLedPin, OUTPUT);
  pinMode(carGreenLedPin, OUTPUT);
  pinMode(peopleRedLedPin, OUTPUT);
  pinMode(peopleGreenLedPin, OUTPUT);

  // buzzer pin is in OUTPUT mode
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  writeLedStates();

  if (pedestrianSemaphoreOn) {
    pedestrianSemaphore();
  }
}

// writing led states
void writeLedStates() {
  digitalWrite(carRedLedPin, carRedLedState);
  digitalWrite(carYellowLedPin, carYellowLedState);
  digitalWrite(carGreenLedPin, carGreenLedState);
  digitalWrite(peopleRedLedPin, peopleRedLedState);
  digitalWrite(peopleGreenLedPin, peopleGreenLedState);
}

// reading the state of the button and seeing if there's a chnage in its state
void toggle() {
  static unsigned int lastDebounceTime = 0;

  // trying to eliminate the possible noise by waiting a few miliseconds
  // in order to make sure the button was pressed intentionally 
  if (millis() - lastDebounceTime > debounceInterval) {
    // if the system is in the middle of its flow nothing will happen on a button press
    if (!pedestrianSemaphoreOn) {
      // starting the flow of the system for the pedestrian sempahore
      pedestrianSemaphoreOn = true;
      startChange = millis();
    }
  }

  lastDebounceTime = millis();
}

// flow of the system's semaphores once the button is pressed
void pedestrianSemaphore() {
  elapsedTime = millis();
  
  if (elapsedTime - startChange > pedestriansToCarsInterval) {
    // CARS: green
    // PEDESTRAINS: red
    carRedLedState = LOW;
    carGreenLedState = HIGH;

    // end of pedestrian semaphore flow
    pedestrianSemaphoreOn = false;
  } else if (elapsedTime - startChange > greenToRedPedestriansInterval) {
    // CARS: red
    // PEDESTRIANS: red
    peopleGreenLedState = LOW;
    peopleRedLedState = HIGH;
  } else if (elapsedTime - startChange > greenToIntermittentInterval) {
    // CARS: red
    // PEDESTRIANS: intermittent green  
    if (elapsedTime - lastChangedLed > intermittenInterval) {
      peopleGreenLedState = !peopleGreenLedState;
      lastChangedLed = millis();
    }

    // making the buzzer emit a sound at a given interval (faster this time)
    if (elapsedTime - lastChangedBuzzer > buzzerDelayIntermittenGreen) {
      tone(buzzerPin, buzzerTone, toneDuration);
      lastChangedBuzzer = millis();
    }
  } else if (elapsedTime - startChange > carsToPedestriansInterval) { 
    // CARS: red
    // PEDESTRIANS: green
    peopleRedLedState = LOW;
    peopleGreenLedState = HIGH;

    // making the buzzer emit a sound at a given interval
    if (elapsedTime - lastChangedBuzzer > buzzerDelayGreen) {
      tone(buzzerPin, buzzerTone, toneDuration);
      lastChangedBuzzer = millis();
    }
  } else if (elapsedTime - startChange > greenToRedCarsInterval) {
    // CARS: red
    // PEDESTRIANS: red
    carYellowLedState = LOW;
    carRedLedState = HIGH;
  } else if (elapsedTime - startChange > greenToYellowInterval) {
    // CARS: yellow 
    // PEDESTRIANS: red
    carGreenLedState = LOW;
    carYellowLedState = HIGH;
  }
}
