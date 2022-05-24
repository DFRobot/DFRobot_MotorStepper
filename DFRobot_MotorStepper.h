/*!
 * @file DFRobot_MotorStepper.h
 * @brief DFRobot's Motor Drive
 * @details This example is for controlling DC motor and stepper motor
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2017-07-31
 * @https://github.com/DFRobot/DFRobot_MotorStepper
*/
 

#ifndef __DFRobot_Motor_H
#define __DFRobot_Motor_H

#include <Arduino.h>
#include <Wire.h>
//Open this macro to see the detailed runn...ing process of the program 

//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define _REG_ADDR_ 0x01  
#define IICADDR 0x30>>1  ///< I2C address
#define M1   1           ///< for the DC motor 1
#define M2   2           ///< for the DC motor 2
#define M3   3           ///< for the DC motor 3
#define M4   4           ///< for the DC motor 4
#define SA   5           ///<SA--->Stepper_Group_A--->[M1A(A+),M1B(A-),M2A(B+),M2B(B-)]
#define SB   6           
#define A0   0x30>>1 ///<Chip Selection Address 1
#define A1   0x38>>1 ///<Chip Selection Address 2
#define A2   0x3C>>1 ///<Chip Selection Address 3
#define A3   0x3E>>1 ///<Chip Selection Address 4
#define CW   0          ///<CW: rotate in forward direction
#define CCW  1          ///CCW: rotate in reverse direction

#define ESP

/**
 * @struct sMotorState_t
 * @brief Describe the current status of the DC motor
 */
typedef struct motorState{
    uint8_t motor1;
    uint8_t motor2;
    uint8_t motor3;
    uint8_t motor4;
    uint8_t stepperA;
    uint8_t stepperB;
}sMotorState_t;
extern sMotorState_t localMotor;


class DFRobot_MotorStepper
{
public:
  /**
   * @fn DFRobot_MotorStepper
   * @brief Constructor
   * @return None
   */
  DFRobot_MotorStepper();
  /**
   * @fn DFRobot_MotorStepper
   * @brief Constructor
   * @param addr The I2C address can be changed by the hardware. Upload the corresponding address here after changing it.
   * @return None
   */
  DFRobot_MotorStepper(uint8_t ddr);
  
  /**
   * @fn ~DFRobot_MotorStepper
   * @brief destructor
   */
  virtual ~DFRobot_MotorStepper();

  /**
   * @fn begin
   * @brief Init function
   * @param addr I2C address
   */
  virtual void begin(unsigned char addr);

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
   * @return Register data
   */
  virtual uint8_t Read_Motor(unsigned char addr, unsigned char Reg ,unsigned char Num );
private:
  uint8_t i2cAddr;
};

class DFRobot_Motor:public DFRobot_MotorStepper
{
public:
  /**
   * @fn DFRobot_Motor
   * @brief Constructor
   * @param ID  device ID
   * @param ADDR  device I2C address
   * @return None
   */
  DFRobot_Motor(uint8_t ID, uint8_t ADDR);
  
  /**
   * @fn ~DFRobot_Motor
   * @brief destructor
   */
  ~DFRobot_Motor();
  
  /**
   * @fn init
   * @brief Open dc motor and stepper motor drive hardware, read the information.
   */
  virtual void init();
  
  /**
   * @fn shutdown
   * @brief Turn off dc motor and stepper motor drive hardware.
   */
  virtual void shutdown();
  /**
   * @fn stop
   * @brief Motor stop rotation.
   */
  virtual void stop();
  /**
   * @fn start
   * @brief Sets DC motor direction and starts it.
   * @param dir  Set Orientation.
   * @n   CW: rotate in forward direction.
   * @n   CCW: rotate in reverse direction.
   */
  void start(uint8_t dir);

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
  uint8_t getDir();
private:
  uint8_t id;
  uint8_t addr;
};

class DFRobot_Stepper:public DFRobot_MotorStepper
{
public:

  /**
   * @fn DFRobot_Stepper
   * @brief Constructor
   * @param ID  device ID
   * @param ADDR  device I2C address
   * @return None
   */
  DFRobot_Stepper(uint8_t ID, uint8_t ADDR);
  
  /**
   * @fn ~DFRobot_Stepper
   * @brief destructor
   */
  ~DFRobot_Stepper();

  /**
   * @fn init
   * @brief Open dc motor and stepper motor drive hardware, read the information.
   */
  virtual void init();

  /**
   * @fn shutdown
   * @brief Turn off dc motor and stepper motor drive hardware.
   */
  virtual void shutdown();

  /**
   * @fn stop
   * @brief Stepper stop rotation.
   */
  virtual void stop();

  /**
   * @fn speed
   * @brief Speed control of dc motor and stepper motor
   * @param val  Set the speed.
   * @n      motor:0<=val<=4096   stepper:0<=val<=1023
   */
  virtual void speed(uint16_t val);

  /**
   * @fn start
   * @brief Stepper motor rotation angle, speed, direction control, and starts it.
   * @param angle  Set rotating resolution, the engine maximum resolution is 0.9°, which means the munimum
   * @n             sequence angel is 0.9°. Set to 0.1°, the engine would not rotate; set to 1°, the engine
   * @n             would only rotate 0.9°.
   * @n             Min:0°(If the Angle is equal to 0°, the motor will not stop spinning)
   * @param speed  Set the speed in the range of 0~1023, set to 0 means 0r/min; set to 1023 means
   * @n            200r/min (the maximum).
   * @n            Min:0  Max:1023
   * @param dir  Set Orientation.
   * @n     CW: rotate in forward direction.
   * @n     CCW: rotate in reverse direction.
   */
  void start(float angle, uint16_t speed, uint8_t dir);

  /**
   * @fn changeSpeed
   * @brief Control motor speed
   * @param count The motor speed has changed count times, from a small speed to a larger one.
   * @param val1  a small speed
   * @param val2  a larger speed
   */
  void changeSpeed(uint16_t count, uint16_t val1, uint16_t val2);
  
  /**
   * @fn getDir
   * @brief Obtain current motor rotation direction.
   */
  uint8_t getDir();
private:
  uint8_t id;
  uint8_t addr;
};



#endif



 
