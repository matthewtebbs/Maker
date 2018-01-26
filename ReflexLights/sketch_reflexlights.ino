/*
    Reflex Lights
    
    BSD 3-Clause License

    Copyright (c) 2018, MuddyTummy Software LLC
    All rights reserved.

    Refer the LICENSE file in this project's folder.
*/

/*
    We're making use of the LED Strip library provided by Let's Start Coding.

    https://www.letsstartcoding.com/libraries
*/
#include <LEDStrip.h>

/*
    See the README.md file for maker board pin setup.
*/
const int pinResetBtn = 2;  /* Reset button pin to (re-)start game. */
const int pinStopBtn = 4;   /* Stop button pin used to attempt to stop shifting LEDs at the green LED position. */
const int pinAudio = A5;    /* Audio pin. */
const int ledclkPin = 12;   /* LED strip clock/latch pin. */
const int leddataPin = 13;  /* LED strip data pin. */

/*  
  LED color strip object we'll control.
*/
const int numPixels = 15;
const int midPixel = numPixels / 2;

LEDStrip strip = LEDStrip(numPixels, leddataPin, ledclkPin);

/*
    Helpful enumerator of color values for mixing LED colors.
*/
typedef enum {
    Blue = 1,
    Magenta = 50,
    Red = 100,
    Yellow = 150,
    Green = 200,
    Cyan = 250
} LEDColor;

/*
    Only a positive, non-zero value of delay will cause a delay.
*/
void safedelay(int dly)
{
    if (0 < dly)
        delay(dly);
}

/*
    Color of an LED at a specific strip position.
*/
LEDColor ledColorAtPos(int pos)
{
    int offset = abs(pos - midPixel);

    LEDColor color;

    if (0 == offset)
    {
        color = LEDColor::Green;
    }
    else if (2 >= offset)
    {
        color = LEDColor::Yellow;
    }
    else
    {
        color = LEDColor::Red;
    }

    return color;
}

/*
    Flash all LEDs on strip 'count' times with a delay of 'dly' msec.
    Also play tone of frequency 'freq' Hz.
    LEDs are left on at the end.
*/
void flashLEDStripWithSound(LEDColor color, int freq, int count, int dly)
{
    while (true)
    {
        strip.setPixel(strip.All, color);
        strip.draw();
        tone(pinAudio, freq);
        safedelay(dly);
        noTone(pinAudio);

        count--;
        if (0 == count)
        {
            break;
        }

        strip.clear();
        strip.draw();
        safedelay(dly);
    }
}

/*
    Draw LEDs on strip between the 'startpos' and 'endpos' positions.
*/
void drawLEDStrip(int startpos = 0, int endpos = -1)
{
    for (int pos = 0; pos < numPixels; pos++)
    {
        bool inRange = startpos <= pos && pos <= endpos;

        strip.setPixel(pos, ledColorAtPos(pos), inRange ? strip.defaultBright /* on */ : 0 /* off */);
    }

    strip.draw();
}

/*
    Game state.

    Waiting - Game waiting for reset button to be pressed.
    Shifting - LEDs shifting on strip while waiting for stop button to be pressed.
    Stopped - Stop button was pressed.
*/
typedef enum {
    WaitingForStart = 0,
    Shifting,
    Stopped,
} State;

/*
  Initial speed, delay between successive LEDs being lit, is 'initspeed'.
  Each successful stop of the LEDs at the green LED position will increase this speed by 'deltaspeed'.
*/
const int initspeed = 128;
const int deltaspeed = 16;

/*
    Game 'state', LED 'position' of lead LED on strip, the 'direction' it is shifting and 'speed'.
*/
State state;
int position;
int direction;
int speed;

/*
    Reset our game state variables.
*/
void reset()
{
    state = State::WaitingForStart;
    position = -1;
    direction = -1;
    speed = initspeed;
}

/*
    Shift LED position of lead LED in appropriate direction.
*/
void shiftPosition()
{
    if (position == -1 || position == (numPixels - 1))
    {
        direction = -direction;
    }

    position += direction;
}

/*
    Board callback setup of program state.
*/
void setup()
{
    // Pin modes.
    pinMode(pinResetBtn, INPUT_PULLUP);
    pinMode(pinStopBtn, INPUT_PULLUP);
    pinMode(pinAudio, OUTPUT);

    // Initial state.
    reset();
}

/*
    Board callback loop.
*/
void loop()
{
    /*
        Regardless of state, check for push of reset button.
    */
    if (digitalRead(pinResetBtn) == LOW)
    {
        reset();                 /* reset to initial state */
        state = State::Shifting; /* and start shifting */
    }

    /*
        Which game state?
    */
    switch (state)
    {
    case State::Shifting:
    {
        // Shifting, so check for stop button press.
        if (digitalRead(pinStopBtn) == LOW)
        {
            state = State::Stopped; /* stopped */
        }
        else
        {
            shiftPosition();            /* not stopped, so do lead LED position shift */
            drawLEDStrip(0, position);  /* LEDS on from beginning to lead LED position */
            safedelay(speed);           /* delay to next shift, e.g. shift speed */
        }
        break;
    }

    case State::Stopped:
    {
        // Stopped, so check for correct stopped position on green LED.
        bool isWon = position == midPixel;

        // Flash LEDs along with a sound to signal to the user either a win or a loss.
        flashLEDStripWithSound(ledColorAtPos(position), isWon ? 950 : 250, isWon ? 5 : 1, isWon ? 250 : 1250);

        if (isWon)
        {
            speed = max(0, speed -= deltaspeed);    /* won, so increase speed, i.e. decrease lead LED position move delay */
            state = State::Shifting;                /* start LED shifting at this higher speed */
        }
        else
        {
            state = State::WaitingForStart;         /* lost, so waiting for game (re-)start */
        }
        break;
    }

    case State::WaitingForStart:
        // Waiting for start so do nothing...
        break;
    }
}
