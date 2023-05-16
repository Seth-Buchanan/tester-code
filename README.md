# tester-code
Code for running torture tests on products and displaying time remaining

## Usage
To use this code you need to install the DeanIsMe/SevSeg seven segment display
library along with the arduino-libraries/Servo library. After this is installed
you can move to prepping hardware.

## Required Hardware

* Arduino Uno or compatible board
* Four digit, seven segment display
* Servo (Right now the code uses an LED as an analog for a servo)
* Button
* Six 220 Ohm resistors
* Various jumper cables

## Hardware Setup

To set up the Seven segment display use [this blog post](https://www.circuitbasics.com/arduino-7-segment-display-tutorial/).
Leave the fourth pin open as it is used for the decimal points that we don't need on the display and will be used for the output instead.
In the program a button is also added for use in a reset button that resets the timer and output.



**This page is not finished**