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

## Compiling and Uploading

There are a variety of ways you can compile and upload this sketch onto the board.

1. If using the Let's Start Coding software (desktop or web) then you are good to go with just the sketcg code (.INO).

1. If using the [Ardunio IDE](https://www.arduino.cc/en/Main/Software), or Visual Studio Code with the Arduino [extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino), then you'll need to ensure the Arduino IDE has imported the LED strip library from Let's Start Coding. You can download it from [here](http://letsstartcoding.com/libraries). 

## Game Play

- Start the game using the **reset** button.
- Press the **stop** button to test your reflexes and try to stop thge colored light on the single green LED.

*Don't stop on the red and yellow LEDs!*

- If successful then the lights will blink green and the next challenge will be faster moving lights.
- If unsucessful then the lights will flash once either red or yellow depending on how far off from the mark you were.
- Press the **restart** button at anytime to reset the game back to the easiest speed.

## Code License

BSD 3-Clause License (refer to the LICENSE file in this same directory)