# Introduction-to-Robotics (2021 - 2022)
 Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest.
 
Each homework's description includes:
- requirements
- files (naming must respect the standard in the requirement)
- implementation details (if aplicable)
- code
- picture of the setup
- video of the setup (if necessary or desired)

## Homework 1 - RGB LED
<details>
 <h3>Requirements</h3>
 Control a RGB led by using separate potentiometers in controlling each of the colors of the led (Red, Green, Blue). The control must be done with digital electronics.

 <h3>Implementation details</h3>
 Since the values read from each potentiometer are in the interval [0..1023], they need to be mapped to the accepted values by each led which are in the interval [0..255].

 <h3>Picture of setup</h3>
 <img src="https://user-images.githubusercontent.com/62221313/138556269-8d553af0-0ee4-4f4f-acb8-1238998de5c3.jpeg"/>

 <h3>Video of the setup</h3>
 https://youtu.be/SxzImC9lBV8
</details>

## Homework 2 - CROSSWALK
<details>
 <h3>Requirements</h3>
 Building the traffic lights for a crosswalk using 2 LEDs to represent the traffic lights for pedestrians (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The pedestrian semaphore is activated by the button, which, once pressed, will start the flow of the system. However, pressing the button in any other state than the default one will cause no effect. There is a pause of one second between the change of semaphores.
 
  The system has the following states:
  - <b>State 1</b> (default) - CARS: green, PEDESTRIANS: red + no sound, DURATION: indefinite
  - <b>State 2</b> (10 seconds after a button press) - CARS: yellow, PEDESTRAINS: red + no sound, DURATION: 3 seconds
  - <b>State 3</b> - CARS: red, PEDESTRAINS: green + sound at a constant interval, DURATION: 10 seconds
  - <b>State 4</b> - CARS: red, PEDESTRIANS: intermittent green + sound at a faster constant interval, DURATION: 5 seconds
 
 <h3>Implementation details</h3>
 The button is using the internal PULLUP resistor of the Atmega chip from the Arduino Uno board.
 
 <h3>Picture of setup</h3>
 <img src="https://user-images.githubusercontent.com/62221313/140087731-f16961db-40dc-4a86-bc8e-b742a7a918bb.jpeg"/>

 <h3>Video of the setup</h3>
 https://youtu.be/EJ2ZocBRfQg
</details>

## Homework 3 - EMF
<details>
 <h3>Requirements</h3>
 An electro-magnetic field dedector which signals the level of the electro-magnetic field with a value in the [0..9] interval on a 7-segment dispaly and a specific sound emitted from a buzzer based on the intensity.
 
 <h3>Implementation details</h3>
 Every time, the antenna reads a sample set of a given size. The average value of each sample set is constrained to be in the [0..100] interval, which will later be mapped to values in the [0..9] interval, representing the digits displayed on the 7-segment dispaly.
 
 <h3>Picture of setup</h3>
 <img src="https://user-images.githubusercontent.com/62221313/140923468-88b12e32-0b09-4903-b21a-c19ebcb529b0.jpeg"/>

 <h3>Video of the setup</h3>

</details>
