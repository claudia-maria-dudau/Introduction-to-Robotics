# Introduction-to-Robotics (2021 - 2022)
 Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest.
 
Each homework's description includes:
- requirements
- files (naming must respect the standard in the requirement)
- implementation details (if aplicable)
- code
- picture of the setup
- video of the setup (if necessary or desired)

<details>
<summary>## Homework 1 - RGB LED</summary>
### Requirements
Control a RGB led by using separate potentiometers in controlling each of the colors of the led (Red, Green, Blue). The control must be done with digital electronics.

### Implementation details
Since the values read from each potentiometer are in the interval [0..1023], they need to be mapped to the accepted values by each led which are in the interval [0..255].

### Picture of setup
![WhatsApp Image 2021-10-23 at 15 29 25](https://user-images.githubusercontent.com/62221313/138556269-8d553af0-0ee4-4f4f-acb8-1238998de5c3.jpeg)

### Video of the setup
https://youtu.be/SxzImC9lBV8
</details>

<details>
<summary>## Homework 2 - CROSSWALK</summary>
### Requirements
Building the traffic lights for a crosswalk using 2 LEDs to represent the traffic lights for pedestrians (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The pedestrian semaphore is activated by the button, which, once pressed, will start the flow of the system. However, pressing the button in any other state than the default one will cause no effect. There is a pause of one second between the change of semaphores.
 
 The system has the following states:
 - <b>State 1</b> (default) - CARS: green, PEDESTRIANS: red + no sound, DURATION: indefinite
 - <b>State 2</b> (10 seconds after a button press) - CARS: yellow, PEDESTRAINS: red + no sound, DURATION: 3 seconds
 - <b>State 3</b> - CARS: red, PEDESTRAINS: green + sound at a constant interval, DURATION: 10 seconds
 - <b>State 4</b> - CARS: red, PEDESTRIANS: intermittent green + sound at a faster constant interval, DURATION: 5 seconds
 
### Implementation details
The button is using the internal PULLUP resistor of the Atmega chip from the Arduino Uno board.
 
### Picture of setup
![WhatsApp Image 2021-11-01 at 12 30 06](https://user-images.githubusercontent.com/62221313/139659253-b8b25124-ab50-4733-bb05-f3310e908f34.jpeg)

### Video of the setup
https://youtu.be/e4JgBUx1K0E
</details>
