# FireBeetle Covers-DC Motor&Stepper Driver
<img width="442" height="523" src="https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0508/DFR0508svg1.png"/>

## DFRobot_Motor Library for Arduino
---------------------------------------------------------

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

This library is used to control dc motors and stepper motors.Including positive spin, reverse, speed adjustment, stop control

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder

## Methods

```C++

/*
 * @brief Open dc motor and stepper motor drive hardware, read the information.
 */
void init(void);

/*
 * @brief Turn off dc motor and stepper motor drive hardware.
 */
void shutdown(void);

/*
 * @brief Motor stop rotation.
 */
void stop(void);

/*
 * @brief The dc motor sets the direction and begins to rotate.
 * @param dir  Set Orientation.
 *     CW: rotate in positive direction.
 *     CCW: rotate in reverse.
 */
void start(uint8_t dir);

/*
 * @brief Step motor rotation Angle, speed, direction control, And it starts spinning.
 * @param angle  Set rotating resolution, The engine maximum resolution is 0.9°,which means the munimum
 *               sequence angel is 0.9°. Set to 0.1°, the engine would not rotate; set to 1°, the engine
 *               would only rotate 0.9°.
 *     Min:0°(If the Angle is equal to 0°,The motor will not stop spinning)
 * @param speed  Set the speed,Rotate speed range is 0~1023, set to 0 means 0r/min; set to 1023 means
 *               200r/min (the maximum).
 *     Min:0  Max:1023
 * @param dir  Set Orientation.
 *     CW: rotate in positive direction.
 *     CCW: rotate in reverse.
 */
void start(float angle, uint16_t speed, uint8_t dir);

/*
 * @brief Speed control of dc motor and stepper motor
 * @param val  Set the speed.
 *     motor:0<=val<=4096   stepper:0<=val<=1023
 */
void speed(uint16_t val);

/*
 * @brief Obtain current motor rotation directio.
 */
void getDir(void);

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |      √       |             |            | 
Arduino uno |      √       |             |            | 
Arduino leonardo |      √       |             |            | 

## History

- Sep 28, 2017 - Version 1.0 released.

## Credits

Written by lixin(1035868977@qq.com), 2017. (Welcome to our [website](https://www.dfrobot.com/))