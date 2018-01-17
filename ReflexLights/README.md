# Reflex Lights

Sketch of a LED strip light game to test your reflexes.

This sketch was tested and uploaded to a [Let's Start Coding](http://letsstartcoding.com) maker board and components from their Ultimate Kit using their desktop application.

## Components

- Arduino Uno compatible maker board x1
- LED strip (APA102) x1
- Speaker x1
- Button x2

## Default Pins

- A LED strip is connected to two power (+, -) pins and digital pin 13 for data and digital pin 12 for clock/latch.
- A speaker is connected to ground (GND) and analog pin A5.
- A button (**reset**) is connected to ground (GND) and digital pin 2.
- A button (**stop**) is connected to ground (GND) and digital pin 4.

## Game Play

- Start the game using the **reset** button.

- Press the **stop** button to test your reflexes and try to stop thge colored light on the single green LED.

*Don't stop on the red and yellow LEDs!*

- If successful then the lights will blink green and the next challenge will be faster moving lights.
- If unsucessful then the lights will flash once either red or yellow depending on how far off from the mark you were.

- Press the **restart** button at anytime to reset the game back to the easiest speed.

## Code License

BSD 3-Clause License (refer to the LICENSE file in this same directory)