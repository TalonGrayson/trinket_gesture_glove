# Gesture Glove

This code was written to give me gesture control on cosplay gloves. This sketch includes 2 gestures (palmUp and palmFwd), which each illuminate a NeoPixel Jewel.

The code has been written to run on an Adafruit Trinket

## Minimum Hardware

* Adafruit 3.3v Trinket (Microcontroller)
* Adafruit NewPixel RGBW Jewel (Lights)
* Adafruit LSM303DLHC (Accelerometer - other accelerometers may be compatible with the library used, not sure)

## Libraries Used

* Adafruit_LSM303_U.h (Accelerometer)
* Adafruit_NeoPixel.h (Lights)

## How Accelerometers Work

In very basic terms, accelermeters work by measuring their rotational position relative to gravity. They output X, Y and Z values (each axis) and we monitor those values in our code.

What they're actually measuring is forces. With gravity on Earth being fairly consistent (close enough to absolutely consistent in most use cases) you can expect fairly consistent values to be displayed with the accelerometer at a set rotation (e.g. flat on a table - we'll call this upsideup for now).

However, it is possible to get those same values at a different rotation of you move the accelerometer at the right speed in some direction (e.g. upsidedown and moved towards the floor).

I think (but have not researched or confirmed this thinking) that if the forces applied to the accelerometer are double that of gravity's force on the accelerometer's axes when still, it is the same as the accelerometer being still and facing the opposite direction... maybe...

## How gestures work

A gesture is defined by 6 elements in an array:
* Minimum X value
* Maximum X value
* Minimum Y value
* Maximum Y value
* Minimum Z value
* Maximum Z value

### Example

```C
double palmUp[] = {-99, 99, -99, 99, -99, -7};
```

So, our range of X and Y values are beyond anything you're likely to see on Earth, short of being hit by a truck or hitting the ground at terminal velocity *(these scenarios have not been tested)*.

Our Z range for `palmUp` is anything between -99 and -7.

Using the `gestureIs()` function (which returns a `boolean`), we can check whether the accelerometer's values are within the ranges of a given gesture:

```C
if(gestureIs(palmUp)) {
	// do a thing
}
```

## setup()
In the setup, we initialise the Jewel and the accelerometer.

The Jewel lights up yellow at boot.

If there is a problem with the Jewel, it will not look how it should (maybe off, maybe mixed colours, maybe the wrong colour).

If there is a problem with the accelerometer, the red LED on the Trinket will light up and the `setup()` is never exited.

## loop()

In the loop, we monitor the accelerometer's position using the `gestureIs()` function. If we find that the gesture is one we're waiting for, we first wait for a moment to ensure it's an intentional gesture. If it is, we run one of the action functions (`palmUpAction()` or `palmFwdAction()`).

## Shopping List

* [3V3 Trinket](https://www.rapidonline.com/adafruit-1500-trinket-3v3-attiny85-arduino-compatible-75-0580)

* [NeoPixel Jewel](https://www.rapidonline.com/adafruit-2859-neopixel-jewel-led-module-7-x-5050-rgbw-natural-white-4500k--73-5271)

* [Accelerometer](https://www.rapidonline.com/adafruit-1120-3-axis-accelerometer-and-magnetometer-compass-board-75-0582)

## Wiring Diagram

![alt text](https://github.com/TalonGrayson/trinket_gesture_glove/blob/2bc6f127406a14a3f715ff000fdfd83d05ac5591/Wiring%20Diagram_bb.png "Wiring Diagram created in Fritzing")

[Created using Fritzing](https://fritzing.org/home/)