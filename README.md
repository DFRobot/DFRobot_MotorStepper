# DFRobot_MotorStepper
- [中文版](./README_CN.md)

DFRobot FireBeetle series are low power consumption microcontrollers designed for Internet of Things (IoT) development. FireBeetle Covers-DC Motor & Stepper Driver is a DC motor & Stepper Motor driver designed for FireBeetle Microcontrollers. It can control up to four-channels DC motors / two-phase four-wire stepper motors simultaneously.<br>

The motor driver cover integrates a STM8 as its coprocessor, controlling the motor speed and direction. It communicates with Microcontroller via I2C port, supports up 1000Hz refresh rate. The assisted processor STM8 controls motors and set the main control free. It effectively reduces the dependence on MCU pin resources and MCU occupancy. Independant motor control make the multi-motors projects more affordable. Cooperate with DFRobot Arduino Motor Library, it will reduce your development difficulty.<br>

This stepper motor driver adopts 2x TB6612FNG chips and performs excellent in low power consumption application. The consumption current is only 30mA under static state, and motor driver can provide 1.2A output current at 5V and the peak current is 3.2A@5V. Besides, the motor drive supports 4~12V wide-range power input. FireBeetle Covers-DC Motor & Stepper Driver also provides four independent interfaces to drive servo. So, you can control servo directly. It can be widely applied to intelligent car control and gear control.<br>

![Product Image](./resources/images/DFR0508.jpg)

## Product Link (https://www.dfrobot.com/product-1666.html)
 DFR0508:DC Motor & Stepper Driver - FireBeetle Covers
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

This library is used to control dc motors and stepper motors, including forward/reverse rotation, speed adjustment, and stop control.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder

## Methods

```C++

  /**
   * @fn init
   * @brief Open dc motor and stepper motor drive hardware, read the information.
   */
   void init(void);

  /**
   * @fn shutdown
   * @brief Turn off dc motor and stepper motor drive hardware.
   */
  void shutdown(void);

  /**
   * @fn stop
   * @brief Motor stop rotation.
   */
  void stop(void);

  /**
   * @fn start
   * @brief Sets DC motor direction and starts it.
   * @param dir  Set Orientation.
   * @n   CW: rotate in forward direction.
   * @n   CCW: rotate in reverse direction.
   */
  void start(uint8_t dir);

  /**
   * @fn start
   * @brief Step motor rotation angle, speed, direction control, and starts it.
   * @param angle  Set rotating resolution, the engine maximum resolution is 0.9°,which means the munimum
   * @n             sequence angel is 0.9°. Set to 0.1°, the engine would not rotate; set to 1°, the engine
   * @n             would only rotate 0.9°.
   * @n             Min:0°(If the Angle is equal to 0°, the motor will not stop spinning)
   * @param speed  Set the speed, rotate speed range is 0~1023, set to 0 means 0r/min; set to 1023 means
   * @n            200r/min (the maximum).
   * @n            Min:0  Max:1023
   * @param dir  Set Orientation.
   * @n     CW: rotate in forward direction.
   * @n     CCW: rotate in reverse direction.
   */
  void start(float angle, uint16_t speed, uint8_t dir);

  /**
   * @fn speed
   * @brief Speed control of dc motor and stepper motor
   * @param val  Set the speed.
   * @n      motor:0<=val<=4096   stepper:0<=val<=1023
   */
  void speed(uint16_t val);

  /**
   * @fn getDir
   * @brief Obtain current motor rotation direction.
   */
  void getDir(void);
  
  /**
   * @fn Write_Motor
   * @brief Write data to the sensor register
   * @param addr I2C address
   * @param Reg register address
   * @param buf data buffer address
   * @param Num the number of data
   */
  virtual void Write_Motor(unsigned char addr, unsigned char Reg ,unsigned char *buf, unsigned char Num);
  
  /**
   * @fn Read_Motor
   * @brief Read data from the sensor register
   * @param addr I2C address
   * @param Reg register address
   * @param Num the number of data, can only be 1
   * @return register data
   */
  virtual uint8_t Read_Motor(unsigned char addr, unsigned char Reg ,unsigned char Num );

  /**
   * @fn changeSpeed
   * @brief Control motor speed
   * @param count The motor speed has changed count times, from a small speed to a larger one.
   * @param val1  a small speed
   * @param val2  a larger speed
   */
  void changeSpeed(uint16_t count, uint16_t val1, uint16_t val2);
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


- 2022/3/30 - Version 1.0.0 released.
## Credits

Written by fengli(li.feng@dfrobot.com), 2022.03.30 (Welcome to our [website](https://www.dfrobot.com/))
